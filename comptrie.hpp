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

#include <algorithm>
#include <string_view>
#include <tuple>

namespace cpp20trie
{
    namespace detail
    {
        template <int N>
        struct FixedStringImpl
        {
            constexpr FixedStringImpl(const char (&str)[N]) noexcept { std::copy_n(str, N, val); }
            constexpr auto empty() const noexcept -> const bool { return size() == 0; }
            constexpr auto head() const noexcept -> const char { return val[0]; }
            static constexpr auto size() noexcept -> std::size_t{ return N; };
            constexpr auto tail() const noexcept -> FixedStringImpl<((N != 1) ? N - 1 : 1)>
            {
                char newVal[((N != 1) ? N - 1 : 1)];
                std::copy_n(&val[(N==1?0:1)], ((N != 1) ? N - 1 : 1), newVal);
                return FixedStringImpl<((N != 1) ? N - 1 : 1)>(newVal);
            }

            char val[N];
        };

    } // namespace detail

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
    template <detail::FixedStringImpl String>
    struct FixedString
    {
        using _type = decltype(String);
        static constexpr auto size() noexcept -> int { return String.size(); }
        static constexpr auto data() noexcept -> const char* { return String.val; }
        static constexpr auto head() noexcept -> char { return String.head(); }
        static constexpr auto empty() noexcept -> bool { return String.empty(); }
        using tail = FixedString<String.tail()>;
    };

    namespace detail
    {
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

        constexpr auto check_trie(TrieNode<> trie, std::string_view str, auto&& fne, auto&&... fns) 
        noexcept -> decltype(fne())
        {
            return fne();
        }

        // This case is only true when we have exactly one transition.
        template <int Char, typename Next, typename = Specialize<(Char >= 0)>>
        constexpr auto check_trie(TrieNode<Transition<Char, Next>> trie, std::string_view str, auto&& fne, auto&&... fns) 
        noexcept -> decltype(fne())
        {
            return (!str.empty() && (str[0] == Char))
                 ? check_trie(Next(), str.substr(1), std::move(fne), std::forward<decltype(fns)>(fns)...)
                 : fne();
        }

        template <typename... Transitions>
        constexpr auto check_trie(TrieNode<Transitions...> trie, std::string_view str, auto&& fne, auto&&... fns) 
        noexcept -> decltype(fne())
        {
            return (!str.empty())
                 ? string_switch(str[0], str.substr(1), trie, std::move(fne), std::forward<decltype(fns)>(fns)...)
                 : fne();
        }

        template <unsigned int Index, typename... Transitions>
        constexpr auto check_trie(TrieNode<Transition<-1, int_c<Index>>, Transitions...>, std::string_view str, auto&& fne, auto&&... fns) 
        noexcept -> decltype(fne())
        {
            return str.empty()
                 ? std::get<Index>(std::make_tuple(std::forward<decltype(fns)>(fns)...))()
                 : check_trie(TrieNode<Transitions...>(), str, std::move(fne), std::forward<decltype(fns)>(fns)...); 
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

        template <std::size_t... Is>
        constexpr auto compile_switch(std::size_t index, auto&& chars, std::index_sequence<Is...>, auto&& func, auto&& default_function)
        noexcept -> decltype(default_function())
        {
            if constexpr (!std::is_same_v<decltype(default_function()), void>)
            {
                auto ret = default_function();
                std::initializer_list<int>({ (index == std::get<Is>(std::move(chars)) ? (ret = func.template operator()<Is>()), 0 : 0)...} );
                return ret;
            }
            else
            {
                auto found = false;
                std::initializer_list<int>({ (index == std::get<Is>(std::move(chars)) ? found=true, (func.template operator()<Is>()), 0 : 0)...} );
                if (!found) default_function();
            }
        }

        template <std::size_t... Cs>
        constexpr auto switch_impl(std::size_t index, auto&& t, auto&& is, std::index_sequence<Cs...> cs, std::string_view str, auto&& fne, auto&&... fns) 
        noexcept -> decltype(fne())
        {
            auto f = [&]<std::size_t I>() -> auto
            {
                return check_trie(std::get<I>(std::move(t)), str, std::move(fne), std::forward<decltype(fns)>(fns)...);
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

        template <std::size_t Index, typename... Transitions>
        constexpr auto trie_add(TrieNode<Transitions...>, auto&& str)
        noexcept -> decltype(insert_sorted<Index>(nil(), std::move(str), TrieNode<>(), Transitions()...))
        {
            return {};
        }

        template <std::size_t Index, class String, typename... Prefixes, int Ch, typename Next, typename = Specialize<(Ch == String::head())>>
        constexpr auto insert_sorted(nil, String&&, TrieNode<Prefixes...>, Transition<Ch, Next>, auto&&... transitions)
        noexcept -> TrieNode<Prefixes..., Transition<Ch, decltype(trie_add<Index>(Next(), typename String::tail()))>, decltype(transitions)...>
        {
            return {};
        }

        template <typename... Transitions>
        constexpr auto string_switch(unsigned char ch, std::string_view str, TrieNode<Transitions...> t, auto&& fne, auto&&... fns) 
        noexcept -> decltype(fne())
        {
            auto transition_children = detail::get_transition_children(t);
            auto transition_characters = detail::get_transition_characters(t);
            auto character = static_cast<std::size_t>(ch);
            auto index_sequence = std::make_index_sequence<sizeof...(Transitions)>{};

            return detail::switch_impl(character, 
                std::move(transition_children),
                std::move(transition_characters),
                std::move(index_sequence), 
                str, 
                std::move(fne), 
                std::forward<decltype(fns)>(fns)...);
        }

        // Making the trie.
        template <std::size_t I>
        constexpr auto make_trie(nil = nil()) noexcept -> TrieNode<>
        {
            return {};
        }

        template <std::size_t I>
        constexpr auto make_trie(nil, auto&& str, auto&&... strs)
        noexcept -> decltype(trie_add<I>(make_trie<I + 1>(nil(), std::forward<decltype(strs)>(strs)...), std::move(str)))
        {
            return {};
        }

        /**
         * Concept to make sure that all types in a variadic arg is the same.
         */
        template<typename Arg, typename... Args>
        concept args_have_same_type = (std::same_as<std::remove_cvref_t<Arg>, Args> && ...);
        
        /**
         * Catch error.
         */
        template<typename FnE, typename... Fns>
        constexpr auto check_do_trie(auto&& trie, std::string_view str, auto&& fne, auto&&... fns) 
        noexcept -> FnE
        {
            static_assert(args_have_same_type<FnE, Fns...>, "MATCH Error - Return type mismatch.");
            return check_trie( std::move(trie), str, std::move(fne), std::forward<decltype(fns)>(fns)...);
        }

        template <unsigned long... Is, typename Arg, typename... Args>
        constexpr auto do_trie(std::index_sequence<Is...>, std::string_view str, Arg&& argE, Args&&... args)
        noexcept -> decltype(argE())
        {
            return check_do_trie<
                decltype(argE()),
                decltype((std::get<(Is * 2 + 1)>(std::make_tuple(std::forward<Args>(args)...)))())...
            >(
                make_trie<0>(nil(),std::get<(2 * Is)>(std::make_tuple(std::forward<Args>(args)...))...),
                std::move(str), std::move(argE),
                std::get<(Is * 2 + 1)>(std::make_tuple(std::forward<Args>(args)...))...);
        }

    }; // namespace detail

    constexpr auto do_trie(std::string_view str, auto&& argE, auto&&... args) 
    noexcept -> decltype(argE())
    {
        return detail::do_trie(std::make_index_sequence<sizeof...(args) / 2>(), 
                              std::move(str),
                              std::move(argE),            
                              std::forward<decltype(args)>(args)...
        );
    }

    #define MATCH(str) do_trie(str, [&] {
    #define CASE(str) }, cpp20trie::FixedString<str>(), [&] {
    #define ENDMATCH });

} // namespace cpp20trie

#endif // COMPILE_TIME_TRIE_H