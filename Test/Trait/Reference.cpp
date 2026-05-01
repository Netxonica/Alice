// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Reference.hpp"

using Alice::Trait::Reference;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Positive cases
    static_assert(Reference<int&>, "int& must satisfy Reference");
    static_assert(Reference<int&&>, "int&& must satisfy Reference");
    static_assert(Reference<const int&>, "const int& must satisfy Reference");
    static_assert(Reference<const int&&>, "const int&& must satisfy Reference");
    static_assert(Reference<volatile int&>, "volatile int& must satisfy Reference");
    static_assert(Reference<volatile int&&>, "volatile int&& must satisfy Reference");
    static_assert(Reference<int*&>, "int*& must satisfy Reference");
    static_assert(Reference<int*&&>, "int*&& must satisfy Reference");
    static_assert(Reference<void(&)()>, "function lvalue reference must satisfy Reference");
    static_assert(Reference<void(&&)()>, "function rvalue reference must satisfy Reference");

    // Negative cases
    static_assert(not Reference<int>, "int must not satisfy Reference");
    static_assert(not Reference<const int>, "const int must not satisfy Reference");
    static_assert(not Reference<int*>, "int* must not satisfy Reference");
    static_assert(not Reference<void>, "void must not satisfy Reference");
    static_assert(not Reference<void()>, "function type must not satisfy Reference");

    struct Incomplete;
    return not Reference<Incomplete>;
}

#ifdef alice_windows
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
#else
int main()
#endif
{
    return not alice_test();
}

#endif