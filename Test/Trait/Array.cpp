// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Array.hpp"

using Alice::Trait::Array;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Types that must satisfy Array via BoundedArray ---
    
    static_assert(Array<int[1]>, "A single-element int array must satisfy Array.");
    static_assert(Array<int[42]>, "A multi-element int array must satisfy Array.");
    static_assert(Array<const int[8]>, "A const-qualified bounded array must satisfy Array.");
    static_assert(Array<volatile float[3]>,
    "A volatile-qualified bounded array must satisfy Array.");
    static_assert(Array<const volatile char[16]>,
    "A cv-qualified bounded array must satisfy Array.");
    static_assert(Array<int[1][2]>, "A 2D bounded array must satisfy Array.");

    // --- Types that must satisfy Array via UnboundedArray ---
    
    static_assert(Array<int[]>, "An unbounded int array must satisfy Array.");
    static_assert(Array<const float[]>, "A const-qualified unbounded array must satisfy Array.");
    static_assert(Array<volatile char[]>,
    "A volatile-qualified unbounded array must satisfy Array.");
    static_assert(Array<const volatile double[]>,
    "A cv-qualified unbounded array must satisfy Array.");

    // --- Types that must NOT satisfy Array ---

    static_assert(not Array<int>, "A plain int must not satisfy Array.");
    static_assert(not Array<int*>, "A raw pointer must not satisfy Array.");
    static_assert(not Array<int&>, "An lvalue reference to int must not satisfy Array.");
    static_assert(not Array<int&&>, "An rvalue reference to int must not satisfy Array.");
    static_assert(not Array<void>, "void must not satisfy Array.");
    static_assert(not Array<decltype(nullptr)>, "nullptr_t must not satisfy Array.");

    // Struct with no array semantics

    struct Plain
    {
        int x;
    };

    static_assert(not Array<Plain>, "A plain struct must not satisfy Array.");
    static_assert(not Array<int(*)[5]>, "A pointer-to-array must not satisfy Array.");
    static_assert(not Array<int(&)[5]>,
    "An lvalue reference to a bounded array must not satisfy Array.");

    struct Incomplete;
    return not Array<Incomplete>;
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