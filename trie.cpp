#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
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

template<int N>
struct FixedString
{
 constexpr FixedString(const char (&str)[N])
 {
  std::copy_n(str, N, val);
 }

 constexpr auto Empty() const -> const bool {
  return Size == 0;
 }

 constexpr auto Head() const -> const char
 {
  return val[0];
 }

 constexpr auto Tail() const -> FixedString<(N-1)>=0?N-1:0>
 {
  char newVal[(N-1)>=0?N-1:0];
  std::copy_n(&val[1], (N-1)>=0?N-1:0, newVal);
  return FixedString<(N-1)>=0?N-1:0>(newVal);
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
   ? (ret = func.template operator()<Is>()), 0
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

 // An entry.
 template<std::size_t Index, FixedString<1>>
 auto transitionAdd(nil = nil()) -> Transition<-1, int_c<Index>>
 { 
  return {}; 
 }

 template <std::size_t Index, FixedString String1>
 auto transitionAdd(nil = nil()) -> Transition<String1.Head(), TrieNode<decltype(transitionAdd<Index, String1.Tail()>(nil()))>>
 { 
  return {};
 }

 // Casse for reaching the end of the string and 
 // there is no transition at the current position.
 template <
  unsigned int Index,
  FixedString String1,
  typename... Prefixes,
  typename... Transitions,
  typename = detail::Specialize<(String1.Empty() || sizeof...(Transitions) == 0)> 
>
constexpr auto insertSorted(nil, TrieNode<Prefixes...>, Transitions...)
-> TrieNode<Prefixes...,decltype(transitionAdd<Index, String1>(nil())),Transitions...>
{ 
  return {};
}

template<std::size_t Index, FixedString String1, typename... Prefixes, int Ch, typename Next, typename... Transitions, typename = detail::Specialize<(Ch > String1.Head())>>
constexpr auto insertSorted(nil, TrieNode<Prefixes...>, Transition<Ch, Next>, Transitions...)
-> TrieNode<Prefixes..., decltype(transitionAdd<Index, String1>(nil())), Transition<Ch, Next>, Transitions...>
{
  return {};
}

template<std::size_t Index, FixedString String, typename... Transitions>
constexpr auto trieAdd(TrieNode<Transitions...>)
-> decltype(insertSorted<Index, String>(nil(), TrieNode<>(), Transitions()...))
{
  return {};
}

template<std::size_t Index, FixedString String, typename... Prefixes, int Ch, typename Next, typename... Transitions, typename = detail::Specialize<(Ch==String.Head())>>
constexpr auto insertSorted(nil, TrieNode<Prefixes...>, Transition<Ch, Next>, Transitions...)
-> TrieNode<Prefixes..., Transition<Ch, decltype(trieAdd<Index, String.Back()>(Next()))>, Transitions...>
{
 return {};
}

template<std::size_t Index, FixedString String, typename... Prefixes, int Ch, typename Next, typename... Transitions, typename = detail::Specialize<(Ch<String.Head())>>
constexpr auto insertSorted(nil, TrieNode<Prefixes...>, Transition<Ch, Next>, Transitions...)
-> decltype(insertSorted<Index, String>(nil(), TrieNode<Prefixes..., Transition<Ch, Next>>(), Transitions()...))
{
 return {};
}

// // Case where the character already exists at the index.
// // We go one layer deeper and insert the rest of the letters.
// template<
//  unsigned int Index,
//  FixedString String1,
//  typename... Prefixes,
//  int Ch, typename Next,
//  typename... Transitions,
//  typename = detail::Specialize<(String1.Head() == Ch)>
// >
// constexpr auto insertSorted(
//   nil,
//   TrieNode<Prefixes...>,
//   Transition<Ch, Next>,
//   Transitions...
// )
//   -> TrieNode<
//    Prefixes...,
//    Transition<Ch,
//     decltype(trieAdd<Index, String1.Tail()>(Next{}))>,
//     Transitions...
//   >
//  {
//    // std::cout << "Head already exits: " << static_cast<char>(Ch) << " - " << String1.Head() << '\n';
  
//    // // static_cast<void>(trieAdd<Index, String1.Tail()>(Next()));

//    // return TrieNode<
//    //  Prefixes...,
//    //  Transition<Ch,
//    //   decltype(trieAdd<Index, String1.Tail()>(Next()))>,
//    //   Transitions...
//    // >();
//   return {};
//  }

//   // The case where we add a new entry.
//  // The character does not match.
//  template<
//   unsigned int Index,
//   FixedString String1,
//   typename... Prefixes,
//   int Ch, 
//   typename Next,
//   typename... Transitions,
//   typename = detail::Specialize<(static_cast<int>(String1.Head()) != Ch)>
//  >
// constexpr auto insertSorted(
//    nil,
//    TrieNode<Prefixes...>,
//    Transition<Ch, Next>,
//    Transitions...
// )
// {
//   std::cout << "NO MATCH: Index: " << Index << ", Character: " << static_cast<char>(Ch) << '\n';

//   return insertSorted<Index, String1>(
//    nil(),
//    TrieNode<Prefixes..., Transition<Ch, Next()>>(),
//    Transitions()...
//   );
// }




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


// Making the trie.
template<std::size_t I>
constexpr TrieNode<> makeTrie(nil=nil()) 
{ 
  std::cout << "End: " << I << '\n';
  return {}; 
}

template <std::size_t I, FixedString String0, FixedString...  Strings>
constexpr auto makeTrie(nil=nil()) 
{
  // std::cout << "[START] Index: " << I << " " << String0.val << '\n';
  // std::cout << "[MAKETRIE] Index: " << I << " " << String0.val << '\n';
  auto trie = makeTrie<I+1, Strings...>();
  // std::cout << "[TRIEADD] Index: " << I << " " << String0.val << '\n';
  auto what = trieAdd<I, String0>(trie);
  // std::cout << "[END] Index: " << I << " " << String0.val << '\n';
  return what;
}

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

template <FixedString... Strings>
constexpr auto makeTrie() 
{
 return cpp20trie::makeTrie<0, Strings...>();
}

auto main() -> int
{
 auto v = cpp20trie::Switch(
  'y', 
  "ang",
  // cpp20trie::TrieNode<
  //  decltype(cpp20trie::transitionAdd<0, "hello">()),
  //  decltype(cpp20trie::transitionAdd<1, "that is so awesome">()),
  //  decltype(cpp20trie::transitionAdd<2, "alex so awesome">())
  // >{},
  makeTrie<"lol", "yang">(),
  []{ return "not found"; },
  []{ return "why"; },
  []{ return "yang"; }
 );

 std::cout << "Result: " << v << '\n';

}