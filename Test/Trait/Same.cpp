// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"

using Alice::Trait::Same;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Identical types ---
    
    static_assert(Same<int, int>);
    static_assert(Same<float, float>);
    static_assert(Same<double, double>);
    static_assert(Same<bool, bool>);
    static_assert(Same<char, char>);
    static_assert(Same<void, void>);

    // --- Pointer types ---
    
    static_assert(Same<int*, int*>);
    static_assert(Same<const int*, const int*>);
    static_assert(Same<int**, int**>);
    static_assert(Same<void*, void*>);

    // --- Reference types ---
    
    static_assert(Same<int&, int&>);
    static_assert(Same<int&&, int&&>);
    static_assert(Same<const int&, const int&>);

    // --- CV-qualified types ---
    
    static_assert(Same<const int, const int>);
    static_assert(Same<volatile int, volatile int>);
    static_assert(Same<const volatile int, const volatile int>);

    // --- User-defined types ---
    
    struct Foo{};
    
    struct Bar{};
    
    static_assert(Same<Foo, Foo>);
    static_assert(Same<Bar, Bar>);

    // --- Different base types ---
    
    static_assert(not Same<int, float>);
    static_assert(not Same<int, double>);
    static_assert(not Same<int, char>);
    static_assert(not Same<int, bool>);
    static_assert(not Same<float, double>);
    static_assert(not Same<Foo, Bar>);

    // --- CV qualifiers must match exactly ---
    
    static_assert(not Same<int, const int>);
    static_assert(not Same<int, volatile int>);
    static_assert(not Same<int, const volatile int>);
    static_assert(not Same<const int, volatile int>);
    static_assert(not Same<const int, const volatile int>);
    static_assert(not Same<volatile int, const volatile int>);

    // --- Value vs pointer ---
    
    static_assert(not Same<int, int*>);
    static_assert(not Same<int, int**>);
    static_assert(not Same<int*, int**>);

    // --- Value vs reference ---

    static_assert(not Same<int, int&>);
    static_assert(not Same<int, int&&>);
    static_assert(not Same<int&, int&&>);
    static_assert(not Same<const int, const int&>);

    // --- Pointer cv-qualifiers must match exactly ---

    static_assert(not Same<int*, const int*>);
    static_assert(not Same<int*, volatile int*>);
    static_assert(not Same<const int*, const volatile int*>);
    static_assert(not Same<int* const, int*>);

    // --- Symmetry: Same<A, B> iff Same<B, A> ---
    
    static_assert(not Same<int, float>);
    static_assert(not Same<float, int>);
    static_assert(not Same<int, const int>);
    static_assert(not Same<const int, int>);

    // --- Array types ---

    static_assert(Same<int[4], int[4]>);
    static_assert(not Same<int[4], int[5]>);
    static_assert(not Same<int[4], int*>);
    static_assert(not Same<int[], int[1]>);

    // --- Function types ---
    
    static_assert(Same<void(), void()>);
    static_assert(not Same<void(), void(int)>);
    static_assert(not Same<int(), void()>);

    struct Incomplete;
    return Same<Incomplete, Incomplete>;
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