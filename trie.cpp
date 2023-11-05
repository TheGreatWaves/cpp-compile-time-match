#include <cstddef>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>
#include <string_view>

namespace detail {
 template <unsigned int>
 struct int_c{};
 
} // namespace detail

namespace ctrie 
{
 using detail::int_c;

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
  // else
  // {
  //  return checkTrie(
  //    TrieNode<Transitions...>(),
  //    str,
  //    std::move(fne),
  //    std::forward<Fns>(fns)...
  //   );
  // }
  return fne();
 }

 // CHECK.
 // template <typename FnE, typename... Fns>
 // constexpr auto checkTrie(
 //   TrieNode<> trie, 
 //   std::string_view str,
 //   FnE&& fne,
 //   Fns&&... fns)
 // -> decltype(fne())
 // {
 //  return fne();
 // }

 // template<
 //  typename... Transitions,
 //  typename    FnE,
 //  typename... Fns
 // >
 // constexpr auto checkTrie(
 //   TrieNode<Transitions...> trie,
 //   std::string_view         str,
 //   FnE&&                    fne,
 //   Fns&&...                 fns
 //  ) -> decltype(fne())
 // {
 //  return (!str.empty())
 //       ? Switch(str[0], str.substr(1), trie, std::move(fne), std::forward<Fns>(fns)...)
 //       : fne();
 // }


 // This case is only true when we have exactly one transition.
 // template <
 //  int         Char, // The current character.
 //  typename    Next, // The next node.
 //  typename    FnE,  // The current function.
 //  typename... Fns   // Other functions...
 // >
 // constexpr auto checkTrie(
 //   TrieNode<Transition<Char, Next>> trie,
 //   std::string_view                 str,
 //   FnE&&                            fne,
 //   Fns&&...                         fns
 //  )
 // -> decltype(fne())
 // {
 //  return (!str.empty() && (str[0]==Char))
 //       ? checkTrie(Next(), str.substr(1), std::move(fne), std::forward<Fns>(fns)...) // Keep traversing.
 //       : fne(); // If the string empty, reached the end.
 // }


 namespace help
 {
  template <int Char0, typename Next0, typename... Transitions>
  constexpr auto help_char(TrieNode<Transition<Char0, Next0>, Transitions...>)
  {
   return Char0;
  }

  template <int Char0, typename Next0, typename... Transitions>
  constexpr auto help_me_char(TrieNode<Transition<Char0, Next0>, Transitions...>) -> auto
  {
   if constexpr (sizeof...(Transitions) > 0)
   {
    return std::make_tuple(Char0, help_char(TrieNode<Transitions...>{}));
   }
   return std::make_tuple(Char0);
  }

  template <int Char0, typename Next0, typename... Transitions>
  constexpr auto help_next(TrieNode<Transition<Char0, Next0>, Transitions...>)
  {
   return Next0();
  }


  template <
   int C,
   typename N,
   template<int, typename> class Transition, 
   typename... Transitions
  >
  constexpr auto help_me_next(TrieNode<Transition<C, N>, Transitions...> t) -> auto
  {
   if constexpr (sizeof...(Transitions) > 0)
   {
    return std::make_tuple(N(), help_char(TrieNode<Transitions...>{}));
   }
   return std::make_tuple(N());
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
 -> auto // We don't really care about the type.
 {
  using returnType = std::common_type_t<decltype(Is)...>;
  auto numCases = std::make_index_sequence<sizeof...(Is)>{};
  bool found = false;

  returnType ret;
  std::initializer_list<std::size_t> ({
   // Note: std::get<Is>(std::move(chars) -> the character we are interested in.
   static_cast<unsigned long>((index == std::get<Is>(std::move(chars)) 
   ? (ret = func(Is)), found=true, 0
   : 0))...
  });

  if (!found) ret = static_cast<returnType>(def());
  
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
 -> auto
 {
  return compileSwitch(
    index,
    std::move(is),
    std::move(cs),
    [&] (auto i) -> auto {
     return checkTrie(
     std::get<0>(std::move(t)), 
     str, 
     fne, 
     std::forward<Fns>(fns)...);
    },
    fne
  );
 }

 template<
  typename... Transitions,
  typename    FnE,
  typename... Fns
 >
 auto Switch(
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


} // namespace detail



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

auto main() -> int
{
 auto v = ctrie::Switch(
  'h', 
  "",
  ctrie::TrieNode<
   ctrie::Transition<'h', ctrie::TrieNode<ctrie::Transition<-1, ctrie::int_c<0>>>>,
   ctrie::Transition<'e', ctrie::TrieNode<ctrie::Transition<-1, ctrie::int_c<0>>>>
  >{},
  []{ return -1; },
  []{ return 2; }
 );

 std::cout << "v: " << v << '\n';

 // std::cout << "What: " << ctrie::help::help((what)) << '\n';
 // constexpr auto v = ctrie::help::help_me(what);

 // std::cout << std::get<0>(v) << '\n';
 // std::cout << std::get<1>(v) << '\n';
}