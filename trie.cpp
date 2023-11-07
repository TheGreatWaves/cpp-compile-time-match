#include <iostream>
#include <tuple>

// https://ctrpeach.io/posts/cpp20-string-literal-template-parameters/

template <int N>
struct FixedString
{
    constexpr FixedString(const char (&str)[N]) noexcept { std::copy_n(str, N, val); }
    constexpr auto Empty() const noexcept -> const bool { return Size() == 0; }
    constexpr auto Head() const noexcept -> const char { return val[0]; }
    static constexpr auto Size() noexcept -> std::size_t{ return N; };
    constexpr auto Tail() const noexcept -> FixedString<((N != 1) ? N - 1 : 1)>
    {
        char newVal[((N != 1) ? N - 1 : 1)];
        std::copy_n(&val[(N==1?0:1)], ((N != 1) ? N - 1 : 1), newVal);
        return FixedString<((N != 1) ? N - 1 : 1)>(newVal);
    }

    char val[N];
};

template <FixedString String>
struct string_t
{
    static constexpr auto Size() noexcept -> int { return String.Size(); }
    static constexpr auto Data() noexcept -> char* { return String.val; }
    static constexpr auto Head() noexcept -> char { return String.Head(); }
    static constexpr auto Empty() noexcept -> bool { return String.Empty(); }
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
constexpr auto checkTrie(TrieNode<> trie, std::string_view str, FnE&& fne, Fns&&... fns) noexcept
    -> decltype(fne())
{
    return fne();
}

// This case is only true when we have exactly one transition.
template <int Char, typename Next, typename FnE, typename... Fns,
          typename = detail::Specialize<(Char >= 0)>>
constexpr auto checkTrie(TrieNode<Transition<Char, Next>> trie, std::string_view str, FnE&& fne,
                         Fns&&... fns) noexcept -> decltype(fne())
{
    return (!str.empty() && (str[0] == Char))
               ? checkTrie(Next(), str.substr(1), std::move(fne), std::forward<Fns>(fns)...)
               : fne();
}

template <typename... Transitions, typename FnE, typename... Fns>
constexpr auto checkTrie(TrieNode<Transitions...> trie, std::string_view str, FnE&& fne,
                         Fns&&... fns) noexcept -> decltype(fne())
{
    return (!str.empty())
               ? Switch(str[0], str.substr(1), trie, std::move(fne), std::forward<Fns>(fns)...)
               : fne();
}

template <unsigned int Index, typename... Transitions, typename FnE, typename... Fns>
constexpr auto checkTrie(TrieNode<Transition<-1, int_c<Index>>, Transitions...>,
                         std::string_view str, FnE&& fne, Fns&&... fns) noexcept -> decltype(fne())
{
    return (str.empty() ? std::get<Index>(std::make_tuple(std::forward<Fns>(fns)...))()
                        : checkTrie(TrieNode<Transitions...>(), std::move(str), std::move(fne),
                                    std::forward<Fns>(fns)...));
}

namespace help
{
template <int Char0, typename Next0>
constexpr auto help_char(TrieNode<Transition<Char0, Next0>>) noexcept
{
    return std::make_tuple(Char0);
}

template <int Char0, typename Next0, int Char1, typename Next1, typename... Transitions>
constexpr auto
    help_char(TrieNode<Transition<Char0, Next0>, Transition<Char1, Next1>, Transitions...>) noexcept
{
    return std::tuple_cat(
        help_char<Char0, Next0>(TrieNode<Transition<Char0, Next0>>()),
        help_char<Char1, Next1>(TrieNode<Transition<Char1, Next1>, Transitions...>()));
}

template <typename... Transitions>
constexpr auto help_me_char(TrieNode<Transitions...> t) noexcept
{
    return help_char(t);
}

template <int Char0, typename Next0>
constexpr auto help_next(TrieNode<Transition<Char0, Next0>>) noexcept
{
    return std::make_tuple(Next0());
}

template <int Char0, typename Next0, int Char1, typename Next1, typename... Transitions>
constexpr auto
    help_next(TrieNode<Transition<Char0, Next0>, Transition<Char1, Next1>, Transitions...>) noexcept
{
    return std::tuple_cat(
        help_next<Char0, Next0>(TrieNode<Transition<Char0, Next0>>()),
        help_next<Char1, Next1>(TrieNode<Transition<Char1, Next1>, Transitions...>()));
}

template <typename... Transitions>
constexpr auto help_me_next(TrieNode<Transitions...> t) noexcept
{
    return help_next(t);
}
}; // namespace help

template <std::size_t... Is, typename Characters, typename Function, typename DefaultFunction>
constexpr auto compileSwitch(std::size_t index, 
                             Characters&& chars, 
                             std::index_sequence<Is...>,
                             Function&&        func,
                             DefaultFunction&& def)
    noexcept -> decltype(def())
{
    using returnType = decltype(def());
    returnType ret   = def();
    std::initializer_list<std::size_t>({
     static_cast<unsigned long>(
        (index == std::get<Is>(std::move(chars))
         ? (ret = func.template operator()<Is>()),
         0 : 0))...}
    );
    return ret;
}

template <typename TransitionTuple, 
          typename CharacterTuple, 
          std::size_t... Cs, 
          typename FnE,
          typename... Fns>
constexpr auto
    switch_impl(std::size_t                index, // The current character we are on.
                TransitionTuple&&          t,     // Tuple containing all transitions from current node.
                CharacterTuple&&           is,    // Tuple containing all characters we can choose.
                std::index_sequence<Cs...> cs,    // Index for each character.
                std::string_view           str, 
                FnE&&                      fne, 
                Fns&&...                   fns) 
    noexcept -> decltype(fne())
{

    auto f = [&]<std::size_t I>() -> auto
    {
        return checkTrie(std::get<I>(std::move(t)), std::move(str), std::move(fne),
                         std::forward<Fns>(fns)...);
    };

    return compileSwitch(index, std::move(is), std::move(cs), std::move(f), fne);
}

template <std::size_t Index, class String, typename = detail::Specialize<(String::Size() == 1)>>
constexpr auto transitionAdd(nil, String str) 
    noexcept -> Transition<-1, int_c<Index>>
{
    return {};
}

template <std::size_t Index, class String, typename = detail::Specialize<(String::Size() > 1)>>
auto transitionAdd(nil, String str)
    noexcept -> Transition<String::Head(),
                  TrieNode<decltype(transitionAdd<Index>(nil(), typename String::Tail()))>>
{
    return {};
}

// Casse for reaching the end of the string and
// there is no transition at the current position.
template <unsigned int Index, class String, typename... Prefixes, typename... Transitions,
          typename = detail::Specialize<(String::Empty() || sizeof...(Transitions) == 0)>>
constexpr auto insertSorted(nil, String&& str, TrieNode<Prefixes...>, Transitions...)
    noexcept -> TrieNode<Prefixes..., decltype(transitionAdd<Index>(nil(), std::move(str))), Transitions...>
{
    return {};
}

template <std::size_t Index, class String, typename... Prefixes, int Ch, typename Next,
          typename... Transitions, typename = detail::Specialize<(Ch > String::Head())>>
constexpr auto insertSorted(nil, String&& str, TrieNode<Prefixes...>, Transition<Ch, Next>,
                            Transitions...)
    noexcept -> TrieNode<Prefixes..., decltype(transitionAdd<Index>(nil(), std::move(str))),
                Transition<Ch, Next>, Transitions...>
{
    return {};
}

template <std::size_t Index, typename String, typename... Transitions>
constexpr auto trieAdd(TrieNode<Transitions...>, String&& str)
    noexcept -> decltype(insertSorted<Index>(nil(), std::move(str), TrieNode<>(), Transitions()...))
{
    return {};
}

template <std::size_t Index, class String, typename... Prefixes, int Ch, typename Next,
          typename... Transitions, typename = detail::Specialize<(Ch == String::Head())>>
constexpr auto insertSorted(nil, String&&, TrieNode<Prefixes...>, Transition<Ch, Next>,
                            Transitions...)
    noexcept -> TrieNode<Prefixes...,
                Transition<Ch, decltype(trieAdd<Index>(Next(), typename String::Tail()))>,
                Transitions...>
{
    return {};
}

template <std::size_t Index, class String, typename... Prefixes, int Ch, typename Next,
          typename... Transitions, typename = detail::Specialize<(Ch < String::Head())>>
constexpr auto insertSorted(nil, String&& str, TrieNode<Prefixes...>, Transition<Ch, Next>,
                            Transitions...)
    noexcept -> decltype(insertSorted<Index, String>(nil(), std::move(str),
                                            TrieNode<Prefixes..., Transition<Ch, Next>>(),
                                            Transitions()...))
{
    return {};
}

template <typename... Transitions, typename FnE, typename... Fns>
constexpr auto Switch(unsigned char ch, std::string_view str, TrieNode<Transitions...> t, FnE&& fne,
                      Fns&&... fns) noexcept -> decltype(fne())
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
constexpr auto makeTrie(nil = nil()) noexcept -> TrieNode<>
{
    return {};
}

template <std::size_t I, class String, typename... Strings>
constexpr auto makeTrie(nil, String&& str, Strings&&... strs)
    noexcept -> decltype(trieAdd<I>(makeTrie<I + 1>(nil(), std::forward<Strings>(strs)...), std::move(str)))
{
    return {};
}

} // namespace cpp20trie

namespace detail
{

template <unsigned long... Is, typename ArgE, typename... Args>
constexpr auto doTrie(std::index_sequence<Is...>, std::string_view str, ArgE&& argE, Args&&... args)
    noexcept -> decltype(argE())
{
    return cpp20trie::checkTrie(
        cpp20trie::makeTrie<0>(cpp20trie::nil(),std::get<(2 * Is)>(std::make_tuple(std::forward<Args>(args)...))...),
        std::move(str), std::move(argE),
        std::get<(Is * 2 + 1)>(std::make_tuple(std::forward<Args>(args)...))...);
}

} // namespace detail

template <typename ArgE, typename... Args>
constexpr auto doTrie(std::string_view str, ArgE&& argE, Args&&... args) noexcept -> decltype(argE())
{
    return detail::doTrie(std::make_index_sequence<sizeof...(args) / 2>(), 
                          std::move(str),
                          std::move(argE),            // Default case (error)
                          std::forward<Args>(args)... // Branches.
    );
}

#define TRIE(str) doTrie(str, [&]
#define CASE(str) , string_t<str>(), [&]
#define ENDTRIE );

#define FAIL(str) CASE(str) { return "Fail"; }
#define PASS(str, next) CASE(str) { return next; }

auto main() -> int
{
    constexpr auto v = 
    TRIE("Start") { return "Fail"; }
    FAIL("Foo")
    FAIL("Bar")
    FAIL("John")
    PASS("Start", "123k")
    ENDTRIE;

    constexpr auto v2 = 
    TRIE(v) { return "Fail"; }
    FAIL("Foo")
    FAIL("Bar")
    FAIL("John")
    PASS("123k", "...")
    ENDTRIE;

    constexpr auto v3 = 
    TRIE(v2) { return "Fail"; }
    FAIL("Foo")
    FAIL("Bar")
    FAIL("John")
    PASS("...", "kj234n231jbsjkvjkh sd")
    ENDTRIE;

    constexpr auto v4 = 
    TRIE(v3) { return "Fail"; }
    FAIL("Foo")
    FAIL("Bar")
    FAIL("John")
    PASS("kj234n231jbsjkvjkh sd", "Test passed.")
    ENDTRIE;

    if constexpr (std::string_view("Test passed.") == v4)
    {
        std::cout << "Test passed!\n";
    }
    else
    {
        std::cout << "Test failed\n";
    }

    return 0;
}
