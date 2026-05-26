// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemoveVolatile.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemoveVolatile;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Non-volatile types are passed through unchanged ---

    static_assert(Same<RemoveVolatile<int>, int>);
    static_assert(Same<RemoveVolatile<float>, float>);
    static_assert(Same<RemoveVolatile<double>, double>);
    static_assert(Same<RemoveVolatile<char>, char>);
    static_assert(Same<RemoveVolatile<bool>, bool>);
    static_assert(Same<RemoveVolatile<void>, void>);
    static_assert(Same<RemoveVolatile<int*>, int*>);
    static_assert(Same<RemoveVolatile<int&>, int&>);
    static_assert(Same<RemoveVolatile<int&&>, int&&>);
    static_assert(Same<RemoveVolatile<const int>, const int>);
    static_assert(Same<RemoveVolatile<const int*>, const int*>);
    static_assert(Same<RemoveVolatile<volatile int*>, volatile int*>); // pointer itself is not volatile
    static_assert(Same<RemoveVolatile<int* volatile*>, int* volatile*>); // only top level stripped later

    // --- Top-level volatile is stripped ---

    static_assert(Same<RemoveVolatile<volatile int>, int>);
    static_assert(Same<RemoveVolatile<volatile float>, float>);
    static_assert(Same<RemoveVolatile<volatile double>, double>);
    static_assert(Same<RemoveVolatile<volatile char>, char>);
    static_assert(Same<RemoveVolatile<volatile bool>, bool>);
    static_assert(Same<RemoveVolatile<volatile void>, void>);

    // --- const is never touched ---

    static_assert(Same<RemoveVolatile<const volatile int>, const int>);
    static_assert(Same<RemoveVolatile<volatile const int>, const int>); // same type, order irrelevant
    static_assert(Same<RemoveVolatile<const int>, const int>);

    // --- Pointers: only the top-level cv-qualifier of the type is affected ---

    static_assert(Same<RemoveVolatile<int* volatile>, int*>);        // volatile pointer → plain pointer
    static_assert(Same<RemoveVolatile<int* const volatile>, int* const>);  // volatile dropped, const kept
    static_assert(Same<RemoveVolatile<volatile int*>, volatile int*>); // pointee volatile untouched

    // --- References: volatile on a reference type is not a thing the standard allows;
    //     references bind to the type as-is and are passed through unchanged ---

    static_assert(Same<RemoveVolatile<volatile int&>, volatile int&>);
    static_assert(Same<RemoveVolatile<volatile int&&>, volatile int&&>);

    // --- User-defined types ---

    struct Foo{};

    static_assert(Same<RemoveVolatile<Foo>, Foo>);
    static_assert(Same<RemoveVolatile<volatile Foo>, Foo>);
    static_assert(Same<RemoveVolatile<const volatile Foo>, const Foo>);

    // --- Arrays ---

    static_assert(Same<RemoveVolatile<volatile int[4]>, int[4]>);
    static_assert(Same<RemoveVolatile<volatile int[]>, int[]>);
    static_assert(Same<RemoveVolatile<int[4]>, int[4]>);
    static_assert(Same<RemoveVolatile<const volatile int[4]>, const int[4]>);

    // --- Idempotence: applying twice gives the same result as applying once ---

    static_assert(Same<RemoveVolatile<RemoveVolatile<volatile int>>, RemoveVolatile<volatile int>>)
    ;
    
    struct Incomplete;
    return Same<Incomplete, RemoveVolatile<volatile Incomplete>>;
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