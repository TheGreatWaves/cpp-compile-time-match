#include <iostream>

#include "../comptrie.hpp"

#define FAIL(str) CASE(str) return "Fail";
#define PASS(str, next) CASE(str) return next;

auto main() -> int
{
    constexpr auto v = 
    MATCH("Start") 
        return "Fail"; 
    FAIL("Foo")
    FAIL("Bar")
    FAIL("John")
    PASS("Start", "123k")
    ENDMATCH;

    constexpr auto v2 = 
    MATCH(v) { return "Fail"; }
    FAIL("Foo")
    FAIL("Bar")
    FAIL("John")
    PASS("123k", "...")
    ENDMATCH;

    constexpr auto v3 = 
    MATCH(v2) { return "Fail"; }
    FAIL("Foo")
    FAIL("Flew")
    FAIL("Bar")
    FAIL("By")
    FAIL("John")
    PASS("...", "kj234n231jbsjkvjkh sd")
    ENDMATCH;

    constexpr auto v4 = 
    MATCH(v3) { return "Fail"; }
    FAIL("Foo")
    FAIL("Few")
    FAIL("Bar")
    FAIL("Bore")
    FAIL("John")
    FAIL("James")
    PASS("kj234n231jbsjkvjkh sd", "Test passed.")
    ENDMATCH;

    if constexpr (std::string_view("Test passed.") == v4)
    {
        std::cout << "Test 1 passed!\n";
    }
    else
    {
        std::cout << "Test failed\n";
    }

    auto success_message = "";
    MATCH("Test") { success_message = "Test 2 failed, something went wrong."; }
    CASE("Test") { success_message = "Test 2 passed!"; }
    ENDMATCH;

    std::cout << success_message << '\n';

    return 0;
}
