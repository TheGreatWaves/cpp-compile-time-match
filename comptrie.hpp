 /**  * MIT License
 * 
 * Copyright (c) 2016 Tobias Hoffmann
 *
 * Copyright (c) 2023 Ochawin A.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#ifndef COMPILE_TIME_TRIE_H
#define COMPILE_TIME_TRIE_H

#include <iostream>
#include <algorithm>
#include <tuple>

namespace cpp20trie
{
    namespace detail
    {
        template <int N>
        struct FixedString
        {
            constexpr FixedString(const char (&str)[N]) noexcept { std::copy_n(str, N, val); }
            constexpr auto empty() const noexcept -> const bool { return size() == 0; }
            constexpr auto head() const noexcept -> const char { return val[0]; }
            static constexpr auto size() noexcept -> std::size_t{ return N; };
            constexpr auto tail() const noexcept -> FixedString<((N != 1) ? N - 1 : 1)>
            {
                char newVal[((N != 1) ? N - 1 : 1)];
                std::copy_n(&val[(N==1?0:1)], ((N != 1) ? N - 1 : 1), newVal);
                return FixedString<((N != 1) ? N - 1 : 1)>(newVal);
            }

            char val[N];
        };

        template <unsigned int> 
        struct int_c {};

        /**
         * For SFINAE specialization.
         */
        template <bool B>
        using Specialize = typename std::enable_if<B>::type;

        /**
         * For forcing ADL.
         */
        struct nil {};

        template <int Char, typename Next>
        struct Transition {};

        template <typename... Transitions>
        struct TrieNode : Transitions... {};

        template <typename FnE, typename... Fns>
        constexpr auto check_trie(TrieNode<> trie, std::string_view str, FnE&& fne, Fns&&... fns) noexcept
        -> decltype(fne())
        {
            return fne();
        }

        // This case is only true when we have exactly one transition.
        template <int Char, typename Next, typename FnE, typename... Fns, typename = Specialize<(Char >= 0)>>
        constexpr auto check_trie(TrieNode<Transition<Char, Next>> trie, std::string_view str, FnE&& fne, Fns&&... fns) 
        noexcept -> decltype(fne())
        {
            return (!str.empty() && (str[0] == Char))
                 ? check_trie(Next(), str.substr(1), std::move(fne), std::forward<Fns>(fns)...)
                 : fne();
        }

        template <typename... Transitions, typename FnE, typename... Fns>
        constexpr auto check_trie(TrieNode<Transitions...> trie, std::string_view str, FnE&& fne, Fns&&... fns) 
        noexcept -> decltype(fne())
        {
            return (!str.empty())
                 ? string_switch(str[0], str.substr(1), trie, std::move(fne), std::forward<Fns>(fns)...)
                 : fne();
        }

        template <unsigned int Index, typename... Transitions, typename FnE, typename... Fns>
        constexpr auto check_trie(TrieNode<Transition<-1, int_c<Index>>, Transitions...>, std::string_view str, FnE&& fne, Fns&&... fns) 
        noexcept -> decltype(fne())
        {
            return str.empty()
                 ? std::get<Index>(std::make_tuple(std::forward<Fns>(fns)...))()
                 : check_trie(TrieNode<Transitions...>(), std::move(str), std::move(fne), std::forward<Fns>(fns)...);
        }

        template <int Char0, typename Next0>
        constexpr auto make_character_tuple_helper(TrieNode<Transition<Char0, Next0>>) noexcept
        {
            return std::make_tuple(Char0);
        }

        template <int Char0, typename Next0, int Char1, typename Next1, typename... Transitions>
        constexpr auto make_character_tuple_helper(TrieNode<Transition<Char0, Next0>, Transition<Char1, Next1>, Transitions...>) noexcept
        {
            return std::tuple_cat(
                make_character_tuple_helper<Char0, Next0>(TrieNode<Transition<Char0, Next0>>()),
                make_character_tuple_helper<Char1, Next1>(TrieNode<Transition<Char1, Next1>, Transitions...>()));
        }

        template <typename... Transitions>
        constexpr auto get_transition_characters(TrieNode<Transitions...> t) noexcept
        {
            return make_character_tuple_helper(t);
        }

        template <int Char0, typename Next0>
        constexpr auto make_transition_children_tuple(TrieNode<Transition<Char0, Next0>>) noexcept
        {
            return std::make_tuple(Next0());
        }

        template <int Char0, typename Next0, int Char1, typename Next1, typename... Transitions>
        constexpr auto make_transition_children_tuple(TrieNode<Transition<Char0, Next0>, Transition<Char1, Next1>, Transitions...>) noexcept
        {
            return std::tuple_cat(
                make_transition_children_tuple<Char0, Next0>(TrieNode<Transition<Char0, Next0>>()),
                make_transition_children_tuple<Char1, Next1>(TrieNode<Transition<Char1, Next1>, Transitions...>()));
        }

        template <typename... Transitions>
        constexpr auto get_transition_children(TrieNode<Transitions...> t) noexcept
        {
            return make_transition_children_tuple(t);
        }

        template <std::size_t... Is, typename Characters, typename Function, typename DefaultFunction>
        constexpr auto compile_switch(std::size_t index, Characters&& chars, std::index_sequence<Is...>, Function&& func, DefaultFunction&& def)
        noexcept -> decltype(def())
        {
            if constexpr (!std::is_same_v<decltype(def()), void>)
            {
                auto ret = def();
                std::initializer_list<int>({ (index == std::get<Is>(std::move(chars)) ? (ret = func.template operator()<Is>()), 0 : 0)...} );
                return ret;
            }
            else
            {
                std::initializer_list<int>({ (index == std::get<Is>(std::move(chars)) ? (func.template operator()<Is>()), 0 : 0)...} );
            }
        }

        template <typename TransitionTuple, typename CharacterTuple, std::size_t... Cs, typename FnE, typename... Fns>
        constexpr auto switch_impl(std::size_t                index, // The current character we are on.
                        TransitionTuple&&                     t,     // Tuple containing all transitions from current node.
                        CharacterTuple&&                      is,    // Tuple containing all characters we can choose.
                        std::index_sequence<Cs...>            cs,    // Index for each character.
                        std::string_view                      str,   // The string we're matching.
                        FnE&&                                 fne,   // Default function. (No match)
                        Fns&&...                              fns)   // Different functions for each match.
        noexcept -> decltype(fne())
        {
            auto f = [&]<std::size_t I>() -> auto
            {
                return check_trie(std::get<I>(std::move(t)), std::move(str), std::move(fne), std::forward<Fns>(fns)...);
            };
            return compile_switch(index, std::move(is), std::move(cs), std::move(f), fne);
        }

        template <std::size_t Index, class String, typename = Specialize<(String::size() == 1)>>
        constexpr auto transition_add(nil, String str) 
        noexcept -> Transition<-1, int_c<Index>>
        {
            return {};
        }

        template <std::size_t Index, class String, typename = Specialize<(String::size() > 1)>>
        constexpr auto transition_add(nil, String str)
        noexcept -> Transition<String::head(), TrieNode<decltype(transition_add<Index>(nil(), typename String::tail()))>>
        {
            return {};
        }

        // Casse for reaching the end of the string and
        // there is no transition at the current position.
        template <unsigned int Index, class String, typename... Prefixes, typename... Transitions, typename = Specialize<(String::empty() || sizeof...(Transitions) == 0)>>
        constexpr auto insert_sorted(nil, String&& str, TrieNode<Prefixes...>, Transitions...)
        noexcept -> TrieNode<Prefixes..., decltype(transition_add<Index>(nil(), std::move(str))), Transitions...>
        {
            return {};
        }

        template <std::size_t Index, class String, typename... Prefixes, int Ch, typename Next, typename... Transitions, typename = Specialize<(Ch != String::head())>>
        constexpr auto insert_sorted(nil, String&& str, TrieNode<Prefixes...>, Transition<Ch, Next>, Transitions...)
        noexcept -> TrieNode<Prefixes..., decltype(transition_add<Index>(nil(), std::move(str))), Transition<Ch, Next>, Transitions...>
        {
            return {};
        }

        template <std::size_t Index, typename String, typename... Transitions>
        constexpr auto trie_add(TrieNode<Transitions...>, String&& str)
        noexcept -> decltype(insert_sorted<Index>(nil(), std::move(str), TrieNode<>(), Transitions()...))
        {
            return {};
        }

        template <std::size_t Index, class String, typename... Prefixes, int Ch, typename Next, typename... Transitions, typename = Specialize<(Ch == String::head())>>
        constexpr auto insert_sorted(nil, String&&, TrieNode<Prefixes...>, Transition<Ch, Next>, Transitions...)
        noexcept -> TrieNode<Prefixes..., Transition<Ch, decltype(trie_add<Index>(Next(), typename String::tail()))>, Transitions...>
        {
            return {};
        }

        template <typename... Transitions, typename FnE, typename... Fns>
        constexpr auto string_switch(unsigned char ch, std::string_view str, TrieNode<Transitions...> t, FnE&& fne, Fns&&... fns) 
        noexcept -> decltype(fne())
        {
             return detail::switch_impl(static_cast<std::size_t>(ch), 
                detail::get_transition_children(t), 
                detail::get_transition_characters(t), 
                std::make_index_sequence<sizeof...(Transitions)>{}, 
                str, 
                std::move(fne), 
                std::forward<Fns>(fns)...);
        }

        // Making the trie.
        template <std::size_t I>
        constexpr auto make_trie(nil = nil()) noexcept -> TrieNode<>
        {
            return {};
        }

        template <std::size_t I, class String, typename... Strings>
        constexpr auto make_trie(nil, String&& str, Strings&&... strs)
        noexcept -> decltype(trie_add<I>(make_trie<I + 1>(nil(), std::forward<Strings>(strs)...), std::move(str)))
        {
            return {};
        }

        template <unsigned long... Is, typename ArgE, typename... Args>
        constexpr auto do_trie(std::index_sequence<Is...>, std::string_view str, ArgE&& argE, Args&&... args)
        noexcept -> decltype(argE())
        {
            return check_trie(
                make_trie<0>(nil(),std::get<(2 * Is)>(std::make_tuple(std::forward<Args>(args)...))...),
                std::move(str), std::move(argE),
                std::get<(Is * 2 + 1)>(std::make_tuple(std::forward<Args>(args)...))...);
        }

    }; // namespace detail

    /**
     * A 'FixedString' is a stirng which can be instantiated constexpr.
     * 
     * Example:
     * 
     *  using HelloString = cpp20trie::FixedString<"Hello">;
     *  - HelloString::data()       -> "Hello"
     *  - HelloString::head()       -> 'H'
     *  - HelloString::tail::data() -> "ello"
     * 
     * template <class String>
     * constexpr auto print_string(String&& str) -> void
     * {
     *     std::cout << String::data() << '\n';
     * }
     */
    template <detail::FixedString String>
    struct FixedString
    {
        static constexpr auto size() noexcept -> int { return String.size(); }
        static constexpr auto data() noexcept -> const char* { return String.val; }
        static constexpr auto head() noexcept -> char { return String.head(); }
        static constexpr auto empty() noexcept -> bool { return String.empty(); }
        using tail = FixedString<String.tail()>;
    };

    template <typename ArgE, typename... Args>
    constexpr auto do_trie(std::string_view str, ArgE&& argE, Args&&... args) noexcept -> decltype(argE())
    {
        return detail::do_trie(std::make_index_sequence<sizeof...(args) / 2>(), 
                              std::move(str),
                              std::move(argE),            // Default case (error)
                              std::forward<Args>(args)... // Branches.
        );
    }

    #define TRIE(str) do_trie(str, [&] {
    #define CASE(str) }, cpp20trie::FixedString<str>(), [&] {
    #define ENDTRIE });

} // namespace cpp20trie

#endif // COMPILE_TIME_TRIE_H