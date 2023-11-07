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
 struct empty_string{};
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
  return Size() == 0;
 }

 constexpr auto Head() const -> const char
 {
  return val[0];
 }

 // constexpr auto Tail() const -> typename std::conditional<(N>1), FixedString<(N-1)>=0?N-1:1>, detail::empty_string>::type
 constexpr auto Tail() const -> FixedString<(N-1)>=0?N-1:1>
 {
   char newVal[(N-1)>=0?N-1:0];
   std::copy_n(&val[1], (N-1)>=0?N-1:0, newVal);
   return FixedString<(N-1)>=0?N-1:0>(newVal);
 }


 static constexpr std::size_t Size() { return N; };
 char val[N];
};

// template <FixedString String>
// struct string_t;


template <FixedString String>
struct string_t
{
static constexpr int Size() { return String.Size(); }
static const char*  Data() { return String.val; } 
static constexpr char Head() { return String.Head(); }
static constexpr bool Empty() { return String.Empty(); }

using Tail = string_t<String.Tail()>;
};

// using EmptyString = decltype(string_t_impl<FixedString<1>("")>());

// template <FixedString String>
// struct string_t;

// template <FixedString String, typename T2=void>
// struct string_tail_t
// {
//  using Type = string_t<String.Tail()>;
// };


// template <FixedString String>
// struct string_tail_t<String, detail::Specialize<(String.Size()==1)>>
// {
//  using Type = EmptyString;
// };

// template <FixedString String>
// struct string_t : string_t_impl<String> 
// {
//  using Tail = typename string_tail_t<String>::Type;
// };


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
  return (str.empty()
       ? std::get<Index>(std::make_tuple(std::forward<Fns>(fns)...))()
       : checkTrie(
          TrieNode<Transitions...>(),
          std::move(str),
          std::move(fne),
          std::forward<Fns>(fns)...
         ));
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
 template<std::size_t Index, class String, typename = detail::Specialize<(String::Size()==1)>>
 constexpr auto transitionAdd(nil, String str) -> Transition<-1, int_c<Index>>
 { 
  return {}; 
 }

 template <std::size_t Index, class String, typename = detail::Specialize<(String::Size()>1)>>
 auto transitionAdd(nil, String str) 
 // -> Transition<String::Head(), TrieNode<decltype(transitionAdd<Index>(nil(), String::Tail()))>>
-> Transition<String::Head(), TrieNode<decltype(transitionAdd<Index>(nil(), typename String::Tail()))>>
 { 
  // transitionAdd<Index>(nil(), typename String::Tail());
  // return Transition<String::Head(), TrieNode<decltype(transitionAdd<Index>(nil(), typename String::Tail()))>>{};
  return {};
 }

 // Casse for reaching the end of the string and 
 // there is no transition at the current position.
 template <
  unsigned int Index,
  class String,
  typename... Prefixes,
  typename... Transitions,
  typename = detail::Specialize<(String::Empty() || sizeof...(Transitions) == 0)> 
>
constexpr auto insertSorted(nil, String&& str, TrieNode<Prefixes...>, Transitions...)
-> TrieNode<Prefixes...,decltype(transitionAdd<Index>(nil(), std::move(str))),Transitions...>
{ 
  // std::cout << "insertSorted(1), Index: " << Index << ", Adding new transition... STRING: " << String::Data() << "\n";
  // transitionAdd<Index>(nil(), std::move(str));
  // transitionAdd<Index>(nil(), std::move(str));
  // return TrieNode<Prefixes...,decltype(transitionAdd<Index>(nil(), std::move(str))),Transitions...>();
  return {};
}

template<std::size_t Index, class String, typename... Prefixes, int Ch, typename Next, typename... Transitions, typename = detail::Specialize<(Ch > String::Head())>>
constexpr auto insertSorted(nil, String&& str, TrieNode<Prefixes...>, Transition<Ch, Next>, Transitions...)
// -> TrieNode<Prefixes..., decltype(transitionAdd<Index, String>(nil())), Transition<Ch, Next>, Transitions...>
-> TrieNode<Prefixes..., decltype(transitionAdd<Index>(nil(), std::move(str))), Transition<Ch, Next>, Transitions...>
{
  // std::cout << "insertSorted(2), Index: " << Index << ", Ch: " << Ch << ", Head: " << String::Head() << '\n';
  // transitionAdd<Index>(nil(), std::move(str));
  // return TrieNode<Prefixes..., decltype(transitionAdd<Index>(nil(), std::move(str))), Transition<Ch, Next>, Transitions...>{};
  return {};
}

template<std::size_t Index, typename String, typename... Transitions>
constexpr auto trieAdd(TrieNode<Transitions...>, String&& str)
-> decltype(insertSorted<Index>(nil(), std::move(str), TrieNode<>(), Transitions()...))
{
  // std::cout << "trieAdd: Index: " << Index << ", String: " << String::Data() << '\n';
  // return insertSorted<Index>(nil(), std::move(str), TrieNode<>(), Transitions()...);
  return {};
}

template<std::size_t Index, class String, typename... Prefixes, int Ch, typename Next, typename... Transitions, typename = detail::Specialize<(Ch==String::Head())>>
constexpr auto insertSorted(nil, String&&, TrieNode<Prefixes...>, Transition<Ch, Next>, Transitions...)
-> TrieNode<Prefixes..., Transition<Ch, decltype(trieAdd<Index>(Next(), typename String::Tail()))>, Transitions...>
{
  // std::cout << "Inserting(3) " << static_cast<const char>(Ch) << ", Index: " << Index << '\n';
  // trieAdd<Index>(Next(), typename String::Tail());
  return {};
}

template<std::size_t Index, class String, typename... Prefixes, int Ch, typename Next, typename... Transitions, typename = detail::Specialize<(Ch<String::Head())>>
constexpr auto insertSorted(nil, String&& str, TrieNode<Prefixes...>, Transition<Ch, Next>, Transitions...)
-> decltype(insertSorted<Index, String>(nil(), std::move(str), TrieNode<Prefixes..., Transition<Ch, Next>>(), Transitions()...))
{
  // std::cout << "Inserting(4) " << static_cast<const char>(Ch) << ", Index: " << Index << '\n';
  // insertSorted<Index, String>(nil(), std::move(str), TrieNode<Prefixes..., Transition<Ch, Next>>(), Transitions()...); 
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
  // std::cout << "End: " << I << '\n';
  return {}; 
}

template <std::size_t I, class String, typename... Strings>
constexpr auto makeTrie(nil, String&& str, Strings&&... strs) 
-> decltype(trieAdd<I>(makeTrie<I+1>(nil(), std::forward<Strings>(strs)...), std::move(str)))
{
  // std::cout << "Making trie... STRING: " << String::Data() << "\n";
 // return trieAdd<I>(makeTrie<I+1>(nil(), std::forward<Strings>(strs)...), std::move(str));
 return {};
}

// template <std::size_t I, typename String0, typename... Strings>
// constexpr auto makeTrie(nil=nil()) 
// -> decltype(trieAdd<I, String0&&>(makeTrie<I+1, Strings&&...>()))
// {
//   return {};
// }

} // namespace cpp20trie


namespace pack_tools {

namespace detail {
  template <unsigned int> struct int_c {};

  template <unsigned int I>
  constexpr void get_index_impl(int_c<I>) // invalid index
  {
  }

  template <typename T0,typename... Ts>
  constexpr T0&& get_index_impl(int_c<0>,T0&& t0,Ts&&... ts)
  {
    return (T0&&)t0;
  }

  template <unsigned int I,typename T0,typename... Ts>
  constexpr auto get_index_impl(int_c<I>,T0&& t0,Ts&&... ts)
    -> decltype(get_index_impl(int_c<I-1>(),(Ts&&)ts...))
  {
    return get_index_impl(int_c<I-1>(),(Ts&&)ts...);
  }
} // namespace detail

template <unsigned int I,typename... Ts>
constexpr auto get_index(Ts&&... ts)
  -> decltype(detail::get_index_impl(detail::int_c<I>(),(Ts&&)ts...))
{
  static_assert((I<sizeof...(Ts)),"Invalid Index");
  return detail::get_index_impl(detail::int_c<I>(),(Ts&&)ts...);
}

} // namespace pack_tools


namespace detail 
{

 // template<typename... Strings>
 // constexpr auto makeTrieFromStrings(Strings&&... strings)
 // {
 //  return cpp20trie::makeTrie<0>(cpp20trie::nil(), strings...);
 //  // return {};
 // }

  template<unsigned long... Is,
           typename ArgE,
           typename... Args>
  constexpr auto doTrie(std::index_sequence<Is...>,
                        std::string_view str,
                        ArgE&&           argE,
                        Args&&...        args
  ) -> decltype(argE())
 {
  return cpp20trie::checkTrie(
   cpp20trie::makeTrie<0>(cpp20trie::nil(), pack_tools::get_index<(2*Is)>(std::forward<Args>(args)...)...), 
   std::move(str), 
   std::move(argE),
   pack_tools::get_index<Is*2+1>(std::forward<Args>(args)...)...
  );
 }

 //  template<unsigned long... Is,
 //           typename ArgE,
 //           typename... Args>
 //  auto doTrieHelper(std::index_sequence<Is...>,
 //                        std::string_view str,
 //                        ArgE&&           argE,
 //                        Args&&...        args
 //  ) -> decltype(argE())
 // {
 //  lol(pack_tools::get_index<(2*Is)>(std::forward<Args>(args)...)...);

 //  return argE();
 // }
} // namespace detail

template<typename ArgE, typename... Args>
constexpr auto doTrie(std::string_view str, ArgE&& argE, Args&&... args)
-> decltype(argE())
{
 return detail::doTrie(
  std::make_index_sequence<sizeof...(args)/2>(),
  std::move(str),
  std::move(argE),            // Default case (error)
  std::forward<Args>(args)... // Branches.
 );
}

// template <class... Strings>
// auto makeTrie(Strings&&... strings) 
// {
//  return cpp20trie::makeTrie<0>(cpp20trie::nil(), std::forward<Strings>(strings)...);
// }

auto main() -> int
{
 // auto v = cpp20trie::Switch(
 //  'y', 
 //  "ang",
 //  // cpp20trie::TrieNode<
 //  //  decltype(cpp20trie::transitionAdd<0, "hello">()),
 //  //  decltype(cpp20trie::transitionAdd<1, "that is so awesome">()),
 //  //  decltype(cpp20trie::transitionAdd<2, "alex so awesome">())
 //  // >{},
 //  makeTrie<"lol", "yang">(),
 //  []{ return "not found"; },
 //  []{ return "why"; },
 //  []{ return "yang"; }
 // );

 // std::cout << "Result: " << v << '\n';

 // doTrie("hello", [&]{ return 0; }, 
 //  FixedString("hello"), [&]{ return 1;},
 //  FixedString("lol"), [&]{ return 2;} 
 //  );

 // auto what = make_string_t<FixedString("Hello"), FixedString("Hello").Size()>::type();
 // std::cout << string_t<"Hello">::tail::da << '\n';
 // makeTrie(string_t<"Hello">());

 #define TRIE(str) doTrie(str, [&]
 #define CASE(str) ,string_t<str>(), [&]
 #define ENDTRIE );

 #define TEST(str) CASE(str) { return str; }


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

 // std::cout << "Result: " << res << '\n';
}
