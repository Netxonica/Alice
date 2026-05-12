// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemoveLvalueReference.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemoveLvalueReference;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Non-reference types (type must pass through unchanged) ---------------

    static_assert(Same<RemoveLvalueReference<int>, int>);
    static_assert(Same<RemoveLvalueReference<const int>, const int>);
    static_assert(Same<RemoveLvalueReference<volatile int>, volatile int>);
    static_assert(Same<RemoveLvalueReference<const volatile int>, const volatile int>);
    static_assert(Same<RemoveLvalueReference<int*>, int*>);
    static_assert(Same<RemoveLvalueReference<const int*>, const int*>);
    static_assert(Same<RemoveLvalueReference<int* const>, int* const>);
    static_assert(Same<RemoveLvalueReference<void>, void>);
    static_assert(Same<RemoveLvalueReference<void*>, void*>);

    // --- Lvalue references (must be stripped) ---------------------------------

    static_assert(Same<RemoveLvalueReference<int&>, int>);
    static_assert(Same<RemoveLvalueReference<const int&>, const int>);
    static_assert(Same<RemoveLvalueReference<volatile int&>, volatile int>);
    static_assert(Same<RemoveLvalueReference<const volatile int&>, const volatile int>);
    static_assert(Same<RemoveLvalueReference<int*&>, int*>);
    static_assert(Same<RemoveLvalueReference<const int*&>, const int*>);
    static_assert(Same<RemoveLvalueReference<void*&>, void*>);

    // --- Rvalue references (must NOT be stripped) -----------------------------

    static_assert(Same<RemoveLvalueReference<int&&>, int&&>);
    static_assert(Same<RemoveLvalueReference<const int&&>, const int&&>);
    static_assert(Same<RemoveLvalueReference<volatile int&&>, volatile int&&>);
    static_assert(Same<RemoveLvalueReference<const volatile int&&>, const volatile int&&>);
    static_assert(Same<RemoveLvalueReference<int*&&>, int*&&>);
    static_assert(Same<RemoveLvalueReference<void*&&>, void*&&>);

    // --- Array types ----------------------------------------------------------

    static_assert(Same<RemoveLvalueReference<int[4]>, int[4]>);
    static_assert(Same<RemoveLvalueReference<int(&)[4]>, int[4]>);
    static_assert(Same<RemoveLvalueReference<int(&&)[4]>, int(&&)[4]>);

    // --- Function types -------------------------------------------------------

    static_assert(Same<RemoveLvalueReference<int(int)>, int(int)>);
    static_assert(Same<RemoveLvalueReference<int(&)(int)>, int(int)>);
    static_assert(Same<RemoveLvalueReference<int(&&)(int)>, int(&&)(int)>);

    struct Incomplete;
    return Same<RemoveLvalueReference<Incomplete&>, Incomplete>;
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