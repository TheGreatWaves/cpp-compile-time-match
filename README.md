# MATCH - Compile Time Trie (C++20)

> [!NOTE]  
> This work is derived from Tobias Hoffmann's work which can be found [here](https://github.com/smilingthax/cttrie).
> 
> Notable Differences:
> - Usage of FixedString instead of CSTR.
> - A more flexible switch implementation.

> [!IMPORTANT]  
> Requires C++20.

# Motivation
String matching is a fundamental technique used in virtually all software development. In C++, the absence of a [switch-case](https://www.programiz.com/c-programming/c-switch-case-statement) construct for strings often leads developers to resort to alternatives such as if-else chains or mapping strings using data structures like maps or hash tables. However, these band-aid solutions come with their own set of problems: introducing long if-else chains can be error-prone, terrible for performance, and it hurts readability and maintainability, while using a map can introduce new complexities and unnecessary overhead for the programmer.

# Usage

> [!WARNING]
> There is no free lunch. Costs which you do not need to pay for during run-time still needs to be paid for during compile-time.
> Beware of adding too many entries. Code size and compile time may be greatly affected.

```cpp
// The only header you need.
#include "comptrie.hpp"
```

A MATCH statement can return a value.
```cpp
auto get_user_role(std::string_view name) -> std::string_view
{
    return MATCH(name)
        return "Unknown";
    CASE("Mai")
        return "Admin";
    CASE("Dan")
        return "User";
    ENDMATCH;
}
```

A MATCH statement can also be void.
```cpp
auto find_user_role(string::string_view name) -> void
{
    auto role = get_user_role(name);

    // Does not return any value.
    MATCH(role)
        std::cout << "Unknown Role!\n";
    CASE("Admin")
        std::cout << "Found Admin!\n";
    CASE("User")
        std::cout << "Found User!\n";
    ENDMATCH;
}
```

A MATCH statement allows mutation of external variables.
```cpp
auto is_admin(string::string_view name) -> bool
{
    auto role = get_user_role(name);
    auto found_admin = false;

    // Does not return any value.
    MATCH(role)
        found_admin = false;
    CASE("Admin")
        found_admin = true;
    ENDMATCH;

    return found_admin;
}
```

A MATCH statement can be called in a constexpr context.
```cpp
#define MODE "DEBUG"

auto main() -> int
{
    constexpr auto v = MATCH(MODE)
        return 1;
    CASE("DEBUG")
        return 2;
    CASE("RELEASE")
        return 3;
    ENDMATCH;

    return v;
}
```

Resulting in the following (compiler explorer, x86-64 gcc 13.2)
```assembly
main:
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 2
        mov     eax, 2
        pop     rbp
        ret
```

# Benchmarks

Some of the tests below also show the benchmark for string matching using a nested switch.

Here is an example of how `switch` cases can be nested to match `aaa`.
```cpp
std::string str = "aaa";

switch(str[0])
{
    case 'a': switch(str[1]) 
    { 
    	case 'a': switch(str[2]) 
        {
            case 'a': // Do something... 
        } 
    } 
}
```
As you can see, it is not scalable and quite error-prone. As we add more entries, the complexity increases. Adding a new entry is not trivial.

## 26 Letters

Matching `z` with all the letters in the alphabet. (26 characters)

|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|               10.70 |       93,431,144.88 |    2.3% |          110.00 |           44.59 |  2.467 |          40.00 |    0.0% |      0.11 | `MATCH`
|               91.61 |       10,915,590.83 |    1.0% |          909.00 |          382.45 |  2.377 |         237.00 |    0.0% |      0.11 | `If`
|                1.77 |      565,269,671.54 |    1.0% |           25.00 |            7.26 |  3.445 |           5.00 |    0.0% |      0.11 | `Switch`

## 52 Letters
|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|               40.37 |       24,770,999.79 |    1.2% |          498.00 |          166.23 |  2.996 |          73.00 |    0.0% |      0.11 | `MATCH`
|              274.44 |        3,643,834.52 |    1.8% |        2,608.00 |        1,128.70 |  2.311 |         668.00 |    0.1% |      0.30 | `If`
|                5.37 |      186,178,593.28 |    1.6% |           68.00 |           22.18 |  3.066 |          15.00 |    0.0% |      0.11 | `Switch`

When dealing with a single character, the switch case will always be your best bet.


## 26 words, length 2

|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|               16.02 |       62,429,074.50 |    1.1% |          209.00 |           66.07 |  3.163 |          56.00 |    0.0% |      0.11 | `MATCH`
|              144.79 |        6,906,656.77 |    0.6% |        1,734.00 |          602.61 |  2.877 |         413.00 |    0.0% |      0.16 | `If`
|                7.45 |      134,148,319.67 |    0.4% |           92.00 |           31.03 |  2.965 |          25.00 |    0.0% |      0.11 | `Switch`

## 26 words, length 3
|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|               16.89 |       59,215,053.17 |    1.4% |          225.00 |           70.08 |  3.210 |          61.00 |    0.0% |      0.11 | `MATCH`
|              145.54 |        6,870,775.00 |    0.7% |        1,734.00 |          604.65 |  2.868 |         413.00 |    0.0% |      0.16 | `If`
|                7.71 |      129,764,969.99 |    1.4% |           94.00 |           32.03 |  2.935 |          26.00 |    0.0% |      0.11 | `Switch`


## 26 words, length 4

|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|               18.56 |       53,890,274.41 |    2.3% |          239.00 |           77.49 |  3.084 |          64.00 |    0.0% |      0.11 | `MATCH`
|              142.20 |        7,032,584.02 |    1.1% |        1,693.00 |          592.55 |  2.857 |         406.00 |    0.0% |      0.16 | `If`
|                7.61 |      131,376,393.17 |    0.8% |           93.00 |           32.03 |  2.903 |          25.00 |    0.0% |      0.11 | `Switch`

## 26 words, length 5
|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|               19.91 |       50,219,080.47 |    1.3% |          254.00 |           82.77 |  3.069 |          69.00 |    0.0% |      0.11 | `MATCH`
|              141.27 |        7,078,707.84 |    0.4% |        1,820.00 |          586.67 |  3.102 |         460.00 |    0.0% |      0.16 | `If`
|                7.52 |      132,914,559.14 |    1.4% |           95.00 |           31.22 |  3.043 |          26.00 |    0.0% |      0.11 | `Switch`


## 56 words, length 5
|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|               31.11 |       32,139,337.14 |    1.2% |          551.00 |          127.34 |  4.327 |          98.00 |    0.0% |      0.11 | `MATCH`
|              310.49 |        3,220,666.89 |    1.8% |        3,328.00 |        1,274.42 |  2.611 |         781.00 |    0.1% |      0.35 | `If`
|                7.62 |      131,232,920.30 |    1.1% |           95.00 |           31.04 |  3.061 |          26.00 |    0.0% |      0.11 | `Switch`


## 100 words, length 5
|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|               73.54 |       13,598,611.92 |    1.2% |        1,132.00 |          302.27 |  3.745 |         161.00 |    0.0% |      0.11 | `MATCH`
|              593.67 |        1,684,448.13 |    3.2% |        6,732.00 |        2,438.49 |  2.761 |       1,582.00 |    0.0% |      0.67 | `If`

# License
[MIT](https://github.com/TheGreatWaves/cpp-compile-time-trie/blob/main/LICENSE)

