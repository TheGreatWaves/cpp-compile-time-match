#include <algorithm>
#include <cstddef>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>
#include <string_view>

namespace detail {
 template <unsigned int>
 struct int_c{};
 template <bool B> using Specialize=typename std::enable_if<B>::type;
} // namespace detail

// https://ctrpeach.io/posts/cpp20-string-literal-template-parameters/

template<std::size_t N>
struct FixedString
{
 constexpr FixedString(const char (&str)[N])
 {
  std::copy_n(str, N, val);
 }

 constexpr auto Head() const -> const char
 {
  return val[0];
 }

 constexpr auto Tail() const -> FixedString<N-1>
 {
  char newVal[N-1];
  std::copy_n(&val[1], N-1, newVal);
  return FixedString<N-1>(newVal);
 }

 static constexpr std::size_t Size = N;
 char val[N];
};


namespace cpp20trie 
{
 using detail::int_c;

 struct nil{};

 template<int Char, typename Next>
 struct Transition {
 };

 template <typename... Transitions>
  struct TrieNode : Transitions... 
  {
  };

 template<
  unsigned int Index,
  typename...  Transitions,
  typename     FnE,
  typename...  Fns
 >
 constexpr auto checkTrie(
   TrieNode<Transition<-1, int_c<Index>>, Transitions...>,
   std::string_view str, 
   FnE&&            fne,
   Fns&&...         fns
  )
 -> decltype(fne())
 {
  if (str.empty())
  {
   return std::get<Index>(std::make_tuple(std::forward<Fns>(fns)...))();
  }
  else
  {
   return checkTrie(
     TrieNode<Transitions...>(),
     str,
     std::move(fne),
     std::forward<Fns>(fns)...
    );
  }
  return fne();
 }

 // CHECK.
 template <typename FnE, typename... Fns>
 constexpr auto checkTrie(
   TrieNode<> trie, 
   std::string_view str,
   FnE&& fne,
   Fns&&... fns)
 -> decltype(fne())
 {
  return fne();
 }

 template<
  typename... Transitions,
  typename    FnE,
  typename... Fns
 >
 constexpr auto checkTrie(
   TrieNode<Transitions...> trie,
   std::string_view         str,
   FnE&&                    fne,
   Fns&&...                 fns
  ) -> decltype(fne())
 {
  return (!str.empty())
       ? Switch(str[0], str.substr(1), trie, std::move(fne), std::forward<Fns>(fns)...)
       : fne();
 }


 // This case is only true when we have exactly one transition.
 template <
  int         Char, // The current character.
  typename    Next, // The next node.
  typename    FnE,  // The current function.
  typename... Fns,  // Other functions...
  typename = detail::Specialize<(Char>=0)>
 >
 constexpr auto checkTrie(
   TrieNode<Transition<Char, Next>> trie,
   std::string_view                 str,
   FnE&&                            fne,
   Fns&&...                         fns
  )
 -> decltype(fne())
 {
  return (!str.empty() && (str[0]==Char))
       ? checkTrie(Next(), str.substr(1), std::move(fne), std::forward<Fns>(fns)...) // Keep traversing.
       : fne(); // If the string empty, reached the end.
 }

 namespace help
 {
  template <int Char0, typename Next0>
  constexpr auto help_char(TrieNode<Transition<Char0, Next0>>)
  {
   return std::make_tuple(Char0);
  }

  template <int Char0, typename Next0, int Char1, typename Next1, typename... Transitions>
  constexpr auto help_char(TrieNode<Transition<Char0, Next0>, Transition<Char1, Next1>, Transitions...>)
  {
   return std::tuple_cat(
    help_char<Char0, Next0>(TrieNode<Transition<Char0, Next0>>()),
    help_char<Char1, Next1>(TrieNode<Transition<Char1, Next1>, Transitions...>())
   );
  }

  template < typename... Transitions >
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
  constexpr auto help_next(TrieNode<Transition<Char0, Next0>, Transition<Char1, Next1>, Transitions...>)
  {
   return std::tuple_cat(
    help_next<Char0, Next0>(TrieNode<Transition<Char0, Next0>>()),
    help_next<Char1, Next1>(TrieNode<Transition<Char1, Next1>, Transitions...>())
   );
  }

  template < typename... Transitions >
  constexpr auto help_me_next(TrieNode<Transitions...> t)
  {
    return help_next(t);
  }
 };

 template <std::size_t... Is, typename Characters, typename Function, typename DefaultFunction>
 constexpr auto compileSwitch(
   std::size_t                index, 
   Characters&&               chars,
   std::index_sequence<Is...>,
   Function                   func,
   DefaultFunction            def
 )
 -> decltype(def()) // We don't really care about the type.
 {
  using returnType = decltype(def());
  returnType ret = def();
  std::initializer_list<std::size_t> ({
   // Note: std::get<Is>(std::move(chars) -> the character we are interested in.
   static_cast<unsigned long>((index == std::get<Is>(std::move(chars)) 
   ? (ret = func.template operator()<Is>()  ), 0
   : 0))...
  });
  
  return ret;
 }

 template<
  typename       TransitionTuple,
  typename       CharacterTuple,
  std::size_t... Cs,    // Index sequence.
  typename       FnE,
  typename...    Fns
 >
 constexpr auto switch_impl(
  std::size_t                index, // The current character we are on.
  TransitionTuple&&          t,     // Tuple containing all transitions from current node.
  CharacterTuple&&           is,    // Tuple containing all characters we can choose.
  std::index_sequence<Cs...> cs,    // Index for each character.
  std::string_view           str, 
  FnE&&                      fne,
  Fns&&...                   fns
 )
 -> decltype(fne())
 {

  auto f = [&]<std::size_t I>() -> auto {
     return checkTrie(
     std::get<I>(std::move(t)), 
     str, 
     fne, 
     std::forward<Fns>(fns)...);
  };

  return compileSwitch(
    index,
    std::move(is),
    std::move(cs),
    std::move(f),
    fne
  );
 }

 template<
  typename... Transitions,
  typename    FnE,
  typename... Fns
 >
 constexpr auto Switch(
  unsigned char ch, 
  std::string_view str, 
  TrieNode<Transitions...> t,
  FnE&& fne,
  Fns&&... fns
 )
 -> decltype(fne())
 {
  return switch_impl(
   static_cast<std::size_t>(ch),                          // The current character.
   help::help_me_next(t),
   help::help_me_char(t), // The transitions from current node.
   std::make_index_sequence<sizeof...(Transitions)>{},    // Index for each character.
   str,
   std::move(fne),
   std::forward<Fns>(fns)...   
  );
 }

template<std::size_t Index, FixedString String, typename... Transitions>
constexpr auto trieAdd(TrieNode<Transitions...>)
-> decltype(insertSorted<Index>(nil(), String, TrieNode<>(), Transitions()...))
{
 return {}; 
}

// Making the trie.
template<std::size_t I>
constexpr TrieNode<> makeTrie(nil) { return {}; }

template <std::size_t I, FixedString String0, FixedString... Strings>
constexpr auto makeTrie(nil, FixedString<sizeof(String0.val)> str) 
 -> decltype(trieAdd<I, String0>(makeTrie<I+1>(nil(), Strings...)
 ))
{
  return {};
}

 // An entry.
 template<std::size_t Index>
 constexpr auto transitionAdd(nil, FixedString<0>) -> Transition<-1, int_c<Index>>
 { return {}; }

 // template <std::size_t Index, unsigned char Ch0, unsigned char... Chars>
 // constexpr Transition<Ch0, TrieNode<decltype(
 //  transitionAdd<Index>(nil(), FixedString<>())
 // )>>
 // transitionAdd(nil, )
 // {}


} // namespace cpp20trie



namespace detail 
{
  template<unsigned int... Is,
           typename ArgE,
           typename... Args>
  constexpr auto doTrie(std::index_sequence<Is...>,
                        std::string_view str,
                        ArgE&&           argE,
                        Args&&...        args
  ) -> decltype(argE())
 {
 }
} // namespace detail

template<typename ArgE, typename... Args>
constexpr auto doTrie(std::string_view str, ArgE&& argE, Args&&... args)
-> decltype(argE())
{
 return detail::doTrie(
  std::make_index_sequence<sizeof...(args)/2>(),
  str,
  std::move(argE),            // Default case (error)
  std::forward<Args>(args)... // Branches.
 );
}

template<FixedString Str>
void Print() {
    // The size of the string is available as a constant expression.
    constexpr auto size = sizeof(Str.val);

    // and so is the string's content.
    constexpr auto contents = Str.val;

    std::cout << "head: " << Str.Head() << '\n';
    std::cout << "head: " << Str.Tail().Head() << '\n';
    std::cout << "head: " << Str.Tail().Tail().Head() << '\n';

    std::cout << "Size: " << size << ", Contents: " << contents << std::endl;
}

auto main() -> int
{
 // constexpr auto v = cpp20trie::Switch(
 //  'h', 
 //  "",
 //  cpp20trie::TrieNode<
 //   cpp20trie::Transition<'e', cpp20trie::TrieNode<cpp20trie::Transition<-1, cpp20trie::int_c<0>>>>,
 //   cpp20trie::Transition<'h', cpp20trie::TrieNode<cpp20trie::Transition<-1, cpp20trie::int_c<1>>>>,
 //   cpp20trie::Transition<'x', cpp20trie::TrieNode<cpp20trie::Transition<-1, cpp20trie::int_c<2>>>>
 //  >{},
 //  []{ return "not found"; },
 //  []{ return "matched e"; },
 //  []{ return "matched h"; },
 //  []{ return "matched x"; }
 // );
 // std::cout << "Result: " << v << '\n';
 Print<"H">();
}