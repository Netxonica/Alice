// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/RvalueReference.hpp"

using Alice::Trait::RvalueReference;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Positive cases: types that satisfy RvalueReference ---

    struct Foo{};

    static_assert(RvalueReference<int&&>, "int&& must satisfy RvalueReference");
    static_assert(RvalueReference<const int&&>, "const int&& must satisfy RvalueReference");
    static_assert(RvalueReference<volatile int&&>, "volatile int&& must satisfy RvalueReference");
    static_assert(RvalueReference<const volatile int&&>,
    "const volatile int&& must satisfy RvalueReference");
    static_assert(RvalueReference<Foo&&>, "Foo&& must satisfy RvalueReference");
    static_assert(RvalueReference<const Foo&&>, "const Foo&& must satisfy RvalueReference");
    static_assert(RvalueReference<int*&&>, "int*&& must satisfy RvalueReference");
    static_assert(RvalueReference<int(&&)[]>, "int(&&)[] must satisfy RvalueReference");

    // --- Negative cases: types that do not satisfy RvalueReference ---

    static_assert(not RvalueReference<int>, "int must not satisfy RvalueReference");
    static_assert(not RvalueReference<const int>, "const int must not satisfy RvalueReference");
    static_assert(not RvalueReference<int*>, "int* must not satisfy RvalueReference");
    static_assert(not RvalueReference<int&>, "int& must not satisfy RvalueReference");
    static_assert(not RvalueReference<const int&>, "const int& must not satisfy RvalueReference");
    static_assert(not RvalueReference<Foo>, "Foo must not satisfy RvalueReference");
    static_assert(not RvalueReference<Foo&>, "Foo& must not satisfy RvalueReference");
    static_assert(not RvalueReference<void>, "void must not satisfy RvalueReference");
    static_assert(not RvalueReference<void*>, "void* must not satisfy RvalueReference");

    struct Incomplete;
    return not RvalueReference<Incomplete>;
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