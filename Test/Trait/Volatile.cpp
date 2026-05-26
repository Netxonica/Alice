// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Volatile.hpp"

using Alice::Trait::Volatile;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Positive cases ---

    // Plain volatile-qualified types

    static_assert(Volatile<volatile int>);
    static_assert(Volatile<volatile float>);
    static_assert(Volatile<volatile double>);
    static_assert(Volatile<volatile char>);
    static_assert(Volatile<volatile bool>);
    static_assert(Volatile<volatile long>);
    static_assert(Volatile<volatile unsigned int>);

    // Volatile array

    static_assert(Volatile<volatile int[4]>);

    // Volatile pointer (the pointer itself is volatile, not the pointee)

    static_assert(Volatile<int* volatile>);
    static_assert(Volatile<const int* volatile>);

    // Volatile reference is not a thing in C++, but volatile-qualified structs are

    struct Foo{};

    static_assert(Volatile<volatile Foo>);

    // Volatile + const (cv-qualified): volatile is still present

    static_assert(Volatile<volatile const int>);
    static_assert(Volatile<const volatile int>);
    static_assert(Volatile<volatile const Foo>);

    // --- Negative cases ---

    // Plain unqualified types

    static_assert(not Volatile<int>);
    static_assert(not Volatile<float>);
    static_assert(not Volatile<double>);
    static_assert(not Volatile<char>);
    static_assert(not Volatile<bool>);
    static_assert(not Volatile<long>);
    static_assert(not Volatile<unsigned int>);
    static_assert(not Volatile<Foo>);

    // Const-only (no volatile)

    static_assert(not Volatile<const int>);
    static_assert(not Volatile<const float>);
    static_assert(not Volatile<const Foo>);

    // Pointers to volatile (the pointer itself is not volatile)

    static_assert(not Volatile<volatile int*>);
    static_assert(not Volatile<volatile int* const>);

    // References are never cv-qualified

    static_assert(not Volatile<volatile int&>);
    static_assert(not Volatile<volatile int&&>);

    // Void

    static_assert(not Volatile<void>);
    static_assert(Volatile<volatile void>);
    static_assert(Volatile<const volatile void>);
    static_assert(not Volatile<const void>);

    // Pointer and function types

    static_assert(not Volatile<int*>);
    static_assert(not Volatile<int(*)()>);

    struct Incomplete;
    return not Volatile<Incomplete>;
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