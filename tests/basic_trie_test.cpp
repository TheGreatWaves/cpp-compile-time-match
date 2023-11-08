#include <iostream>

#include "../comptrie.hpp"

#define FAIL(str) CASE(str) return "Fail";
#define PASS(str, next) CASE(str) return next;

auto main() -> int
{
    constexpr auto v = 
    TRIE("Start") 
        return "Fail"; 
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
        std::cout << "Test 1 passed!\n";
    }
    else
    {
        std::cout << "Test failed\n";
    }

    auto success_message = "";
    TRIE("Test") { success_message = "Test 2 failed, something went wrong."; }
    CASE("Test") { success_message = "Test 2 passed!"; }
    ENDTRIE;

    std::cout << success_message << '\n';

    return 0;
}
