# MATCH - Compile Time Trie (C++20)

This work is derived from Tobias Hoffmann's work which can be found [here](https://github.com/smilingthax/cttrie).

Notable Differences:
- Usage of FixedString instead of CSTR.
- A more flexible switch implementation.

# Usage
> Requires C++20.

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

# License
[MIT](https://github.com/TheGreatWaves/cpp-compile-time-trie/blob/main/LICENSE)

