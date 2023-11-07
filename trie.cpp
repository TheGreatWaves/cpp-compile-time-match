#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

// https://ctrpeach.io/posts/cpp20-string-literal-template-parameters/

template <int N>
struct FixedString
{
    constexpr FixedString(const char (&str)[N]) { std::copy_n(str, N, val); }
    constexpr auto Empty() const -> const bool { return Size() == 0; }
    constexpr auto Head() const -> const char { return val[0]; }
    static constexpr std::size_t Size() { return N; };

    constexpr auto Tail() const -> FixedString<((N - 1) >= 0 ? N - 1 : 1)>
    {
        char newVal[(N - 1) >= 0 ? N - 1 : 0];
        std::copy_n(&val[1], (N - 1) >= 0 ? N - 1 : 0, newVal);
        return FixedString < (N - 1) >= 0 ? N - 1 : 0 > (newVal);
    }

    char val[N];
};

template <FixedString String>
struct string_t
{
    static constexpr int Size() { return String.Size(); }
    static const char* Data() { return String.val; }
    static constexpr char Head() { return String.Head(); }
    static constexpr bool Empty() { return String.Empty(); }
    using Tail = string_t<String.Tail()>;
};

namespace detail
{
template <unsigned int>
struct int_c {};

template <bool B>
using Specialize = typename std::enable_if<B>::type;
struct empty_string {};
} // namespace detail

namespace cpp20trie
{
using detail::int_c;

struct nil {};

template <int Char, typename Next>
struct Transition {};

template <typename... Transitions>
struct TrieNode : Transitions... {};

// CHECK.
template <typename FnE, typename... Fns>
constexpr auto checkTrie(TrieNode<> trie, std::string_view str, FnE&& fne, Fns&&... fns)
    -> decltype(fne())
{
    return fne();
}

// This case is only true when we have exactly one transition.
template <int Char, typename Next, typename FnE, typename... Fns,
          typename = detail::Specialize<(Char >= 0)>>
constexpr auto checkTrie(TrieNode<Transition<Char, Next>> trie, std::string_view str, FnE&& fne,
                         Fns&&... fns) -> decltype(fne())
{
    return (!str.empty() && (str[0] == Char))
               ? checkTrie(Next(), str.substr(1), std::move(fne), std::forward<Fns>(fns)...)
               : fne();
}

template <typename... Transitions, typename FnE, typename... Fns>
constexpr auto checkTrie(TrieNode<Transitions...> trie, std::string_view str, FnE&& fne,
                         Fns&&... fns) -> decltype(fne())
{
    return (!str.empty())
               ? Switch(str[0], str.substr(1), trie, std::move(fne), std::forward<Fns>(fns)...)
               : fne();
}

template <unsigned int Index, typename... Transitions, typename FnE, typename... Fns>
constexpr auto checkTrie(TrieNode<Transition<-1, int_c<Index>>, Transitions...>,
                         std::string_view str, FnE&& fne, Fns&&... fns) -> decltype(fne())
{
    return (str.empty() ? std::get<Index>(std::make_tuple(std::forward<Fns>(fns)...))()
                        : checkTrie(TrieNode<Transitions...>(), std::move(str), std::move(fne),
                                    std::forward<Fns>(fns)...));
}

namespace help
{
template <int Char0, typename Next0>
constexpr auto help_char(TrieNode<Transition<Char0, Next0>>)
{
    return std::make_tuple(Char0);
}

template <int Char0, typename Next0, int Char1, typename Next1, typename... Transitions>
constexpr auto
    help_char(TrieNode<Transition<Char0, Next0>, Transition<Char1, Next1>, Transitions...>)
{
    return std::tuple_cat(
        help_char<Char0, Next0>(TrieNode<Transition<Char0, Next0>>()),
        help_char<Char1, Next1>(TrieNode<Transition<Char1, Next1>, Transitions...>()));
}

template <typename... Transitions>
constexpr auto help_me_char(TrieNode<Transitions...> t)
{
    return help_char(t);
}

template <int Char0, typename Next0>
constexpr auto help_next(TrieNode<Transition<Char0, Next0>>)
{
    return std::make_tuple(Next0());
}

template <int Char0, typename Next0, int Char1, typename Next1, typename... Transitions>
constexpr auto
    help_next(TrieNode<Transition<Char0, Next0>, Transition<Char1, Next1>, Transitions...>)
{
    return std::tuple_cat(
        help_next<Char0, Next0>(TrieNode<Transition<Char0, Next0>>()),
        help_next<Char1, Next1>(TrieNode<Transition<Char1, Next1>, Transitions...>()));
}

template <typename... Transitions>
constexpr auto help_me_next(TrieNode<Transitions...> t)
{
    return help_next(t);
}
}; // namespace help

template <std::size_t... Is, typename Characters, typename Function, typename DefaultFunction>
constexpr auto compileSwitch(std::size_t index, Characters&& chars, std::index_sequence<Is...>,
                             Function&&        func,
                             DefaultFunction&& def)
    -> decltype(def())
{
    using returnType = decltype(def());
    returnType ret   = def();
    std::initializer_list<std::size_t>(
        {// Note: std::get<Is>(std::move(chars) -> the character we are interested
         // in.
         static_cast<unsigned long>((index == std::get<Is>(std::move(chars))
                                     ? (ret = func.template operator()<Is>()),
                                     0 : 0))...});

    return ret;
}

template <typename TransitionTuple, typename CharacterTuple, std::size_t... Cs, typename FnE,
          typename... Fns>
constexpr auto
    switch_impl(std::size_t                index, // The current character we are on.
                TransitionTuple&&          t,     // Tuple containing all transitions from current node.
                CharacterTuple&&           is,    // Tuple containing all characters we can choose.
                std::index_sequence<Cs...> cs,    // Index for each character.
                std::string_view           str, 
                FnE&&                      fne, 
                Fns&&...                   fns
    ) -> decltype(fne())
{

    auto f = [&]<std::size_t I>() -> auto
    {
        return checkTrie(std::get<I>(std::move(t)), std::move(str), std::move(fne),
                         std::forward<Fns>(fns)...);
    };

    return compileSwitch(index, std::move(is), std::move(cs), std::move(f), fne);
}

template <std::size_t Index, class String, typename = detail::Specialize<(String::Size() == 1)>>
constexpr auto transitionAdd(nil, String str) -> Transition<-1, int_c<Index>>
{
    return {};
}

template <std::size_t Index, class String, typename = detail::Specialize<(String::Size() > 1)>>
auto transitionAdd(nil, String str)
    -> Transition<String::Head(),
                  TrieNode<decltype(transitionAdd<Index>(nil(), typename String::Tail()))>>
{
    return {};
}

// Casse for reaching the end of the string and
// there is no transition at the current position.
template <unsigned int Index, class String, typename... Prefixes, typename... Transitions,
          typename = detail::Specialize<(String::Empty() || sizeof...(Transitions) == 0)>>
constexpr auto insertSorted(nil, String&& str, TrieNode<Prefixes...>, Transitions...)
    -> TrieNode<Prefixes..., decltype(transitionAdd<Index>(nil(), std::move(str))), Transitions...>
{
    return {};
}

template <std::size_t Index, class String, typename... Prefixes, int Ch, typename Next,
          typename... Transitions, typename = detail::Specialize<(Ch > String::Head())>>
constexpr auto insertSorted(nil, String&& str, TrieNode<Prefixes...>, Transition<Ch, Next>,
                            Transitions...)
    -> TrieNode<Prefixes..., decltype(transitionAdd<Index>(nil(), std::move(str))),
                Transition<Ch, Next>, Transitions...>
{
    return {};
}

template <std::size_t Index, typename String, typename... Transitions>
constexpr auto trieAdd(TrieNode<Transitions...>, String&& str)
    -> decltype(insertSorted<Index>(nil(), std::move(str), TrieNode<>(), Transitions()...))
{
    return {};
}

template <std::size_t Index, class String, typename... Prefixes, int Ch, typename Next,
          typename... Transitions, typename = detail::Specialize<(Ch == String::Head())>>
constexpr auto insertSorted(nil, String&&, TrieNode<Prefixes...>, Transition<Ch, Next>,
                            Transitions...)
    -> TrieNode<Prefixes...,
                Transition<Ch, decltype(trieAdd<Index>(Next(), typename String::Tail()))>,
                Transitions...>
{
    return {};
}

template <std::size_t Index, class String, typename... Prefixes, int Ch, typename Next,
          typename... Transitions, typename = detail::Specialize<(Ch < String::Head())>>
constexpr auto insertSorted(nil, String&& str, TrieNode<Prefixes...>, Transition<Ch, Next>,
                            Transitions...)
    -> decltype(insertSorted<Index, String>(nil(), std::move(str),
                                            TrieNode<Prefixes..., Transition<Ch, Next>>(),
                                            Transitions()...))
{
    return {};
}

template <typename... Transitions, typename FnE, typename... Fns>
constexpr auto Switch(unsigned char ch, std::string_view str, TrieNode<Transitions...> t, FnE&& fne,
                      Fns&&... fns) -> decltype(fne())
{
    return switch_impl(static_cast<std::size_t>(ch), // The current character.
                       help::help_me_next(t),
                       help::help_me_char(t), // The transitions from current node.
                       std::make_index_sequence<sizeof...(Transitions)>{}, // Index for each
                                                                           // character.
                       str, std::move(fne), std::forward<Fns>(fns)...);
}

// Making the trie.
template <std::size_t I>
constexpr TrieNode<> makeTrie(nil = nil())
{
    return {};
}

template <std::size_t I, class String, typename... Strings>
constexpr auto makeTrie(nil, String&& str, Strings&&... strs)
    -> decltype(trieAdd<I>(makeTrie<I + 1>(nil(), std::forward<Strings>(strs)...), std::move(str)))
{
    return {};
}

} // namespace cpp20trie

namespace detail
{

template <unsigned long... Is, typename ArgE, typename... Args>
constexpr auto doTrie(std::index_sequence<Is...>, std::string_view str, ArgE&& argE, Args&&... args)
    -> decltype(argE())
{
    return cpp20trie::checkTrie(
        cpp20trie::makeTrie<0>(cpp20trie::nil(),
                               std::get<(2 * Is)>(std::make_tuple(std::forward<Args>(args)...))...),
        std::move(str), std::move(argE),
        std::get<(Is * 2 + 1)>(std::make_tuple(std::forward<Args>(args)...))...);
}

} // namespace detail

template <typename ArgE, typename... Args>
constexpr auto doTrie(std::string_view str, ArgE&& argE, Args&&... args) -> decltype(argE())
{
    return detail::doTrie(std::make_index_sequence<sizeof...(args) / 2>(), std::move(str),
                          std::move(argE),            // Default case (error)
                          std::forward<Args>(args)... // Branches.
    );
}

auto main() -> int
{

#define TRIE(str) doTrie(str, [&]
#define CASE(str) , string_t<str>(), [&]
#define ENDTRIE );

#define TEST(str)   \
    CASE(str)       \
    {               \
        return str; \
    }

 auto v = doTrie ( "WOW" , [ & ] {
        return "Nothing found.";
 }
 TEST("WOW")
 TEST("Hello")
 TEST("what")
 ENDTRIE;

 std::cout << "Expect WOW: found: " << v << '\n';

 auto v2 = doTrie ( "Hello" , [ & ] {
        return "Nothing found.";
 }
 TEST("WOW")
 TEST("Hello")
 TEST("what")
 ENDTRIE;

 std::cout << "Expect Hello: found: " << v2 << '\n';

 auto v3 = doTrie ( "what" , [ & ] {
        return "Nothing found.";
 }
 TEST("WOW")
 TEST("Hello")
 TEST("what")
 ENDTRIE;

 std::cout << "Expect what: found: " << v3 << '\n';

 auto v4 = doTrie ( "NOT FOUND" , [ & ] {
        return "Nothing found.";
 }
 TEST("WOW")
 TEST("Hello")
 TEST("what")
 ENDTRIE;

 std::cout << "Expect Nothing found: found: " << v4 << '\n';

 return 0;
}
