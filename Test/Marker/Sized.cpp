// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Marker/Sized.hpp"

using Alice::Marker::Sized;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Types that MUST satisfy Sized ---

    // Fundamental scalar types

    static_assert(Sized<int>);
    static_assert(Sized<unsigned int>);
    static_assert(Sized<long long>);
    static_assert(Sized<float>);
    static_assert(Sized<double>);
    static_assert(Sized<char>);
    static_assert(Sized<bool>);

    // cv-qualified scalars — qualifiers must not affect the result

    static_assert(Sized<const int>);
    static_assert(Sized<volatile int>);
    static_assert(Sized<const volatile double>);

    // Pointers are always complete, including pointers-to-incomplete and pointers-to-void

    static_assert(Sized<int*>);
    static_assert(Sized<void*>);
    static_assert(Sized<const void*>);
    static_assert(Sized<int**>);

    // Pointers to functions are sized (the pointer object itself has a size)

    static_assert(Sized<int(*)()>);
    static_assert(Sized<void(*)(int, double)>);

    // References forward sizeof to the referred-to type

    static_assert(Sized<int&>);
    static_assert(Sized<const int&>);
    static_assert(Sized<int&&>);

    // Bounded arrays: RemoveExtents reduces them to their element type, which is complete

    static_assert(Sized<int[8]>);
    static_assert(Sized<int[1][2][3]>);
    static_assert(Sized<const char[32]>);

    // A complete user-defined struct

    struct Pod
    {
        int x;
        
        float y;
    };

    static_assert(Sized<Pod>);
    static_assert(Sized<Pod*>);
    static_assert(Sized<const Pod&>);

    // --- Types that MUST NOT satisfy Sized ---

    // void itself has no sizeof

    static_assert(not Sized<void>);

    // Unbounded (incomplete) array types

    static_assert(not Sized<int[]>);
    static_assert(not Sized<const double[]>);
    static_assert(not Sized<int[][4]>);       // outermost extent is missing
    static_assert(not Sized<Pod[]>);

    // Plain function types (not pointer-to-function)

    static_assert(not Sized<int()>);
    static_assert(not Sized<void()>);
    static_assert(not Sized<int(int, float)>);
    static_assert(not Sized<void(int, ...)>);

    // An incomplete class type has no size

    struct Incomplete;

    static_assert(not Sized<Incomplete[]>);
    static_assert(not Sized<Incomplete[42]>);

    return not Sized<Incomplete>;
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