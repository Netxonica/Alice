// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemoveConstant.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemoveConstant;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Sanity: non-const types are passed through unchanged ---
    
    static_assert(Same<RemoveConstant<int>, int>);
    static_assert(Same<RemoveConstant<float>, float>);
    static_assert(Same<RemoveConstant<double>, double>);
    static_assert(Same<RemoveConstant<unsigned long long>, unsigned long long>);
    static_assert(Same<RemoveConstant<void>, void>);

    // --- Core: top-level const is stripped ---

    static_assert(Same<RemoveConstant<const int>, int>);
    static_assert(Same<RemoveConstant<const float>, float>);
    static_assert(Same<RemoveConstant<const double>, double>);
    static_assert(Same<RemoveConstant<const void>, void>);

    // --- Pointers: top-level const on the pointer itself is stripped ---

    static_assert(Same<RemoveConstant<int* const>, int*>);
    static_assert(Same<RemoveConstant<const int* const>, const int*>);

    // --- Pointers: const-on-pointee is NOT top-level; must be preserved ---

    static_assert(Same<RemoveConstant<const int*>, const int*>);
    static_assert(Same<RemoveConstant<int*>, int*>);

    // --- References: const embedded in a reference type is never top-level ---

    static_assert(Same<RemoveConstant<const int&>, const int&>);
    static_assert(Same<RemoveConstant<int&>, int&>);
    static_assert(Same<RemoveConstant<const int&&>, const int&&>);
    static_assert(Same<RemoveConstant<int&&>, int&&>);

    // --- Volatile: volatile alone is untouched ---

    static_assert(Same<RemoveConstant<volatile int>, volatile int>);

    // --- CV-qualified: only const is stripped, volatile survives ---

    static_assert(Same<RemoveConstant<const volatile int>, volatile int>);

    // --- Arrays: top-level const on array type is stripped ---

    static_assert(Same<RemoveConstant<const int[4]>, int[4]>);
    static_assert(Same<RemoveConstant<int[4]>, int[4]>);

    // --- Idempotence: applying twice equals applying once ---

    static_assert(Same<RemoveConstant<RemoveConstant<const int>>, RemoveConstant<const int>>);

    // --- Pointer-to-pointer: only outermost const removed ---

    static_assert(Same<RemoveConstant<int** const>, int**>);
    static_assert(Same<RemoveConstant<const int**>, const int**>);

    struct Incomplete;
    return not Same<Incomplete, RemoveConstant<const Incomplete>>;
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