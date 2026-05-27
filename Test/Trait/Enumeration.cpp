// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Enumeration.hpp"

using Alice::Trait::Enumeration;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Positive cases
    enum UnscopedEnum
    {
        A,
        B,
        C
    };

    enum class ScopedEnum
    {
        X,
        Y,
        Z
    };

    enum UnscopedEnumWithBase : int
    {
        D,
        E,
        F
    };

    enum class ScopedEnumWithBase : unsigned char
    {
        G,
        H,
        I
    };

    enum class EmptyEnum{};

    static_assert(Enumeration<UnscopedEnum>);
    static_assert(Enumeration<ScopedEnum>);
    static_assert(Enumeration<UnscopedEnumWithBase>);
    static_assert(Enumeration<ScopedEnumWithBase>);
    static_assert(Enumeration<EmptyEnum>);

    // Negative cases

    struct Struct{};

    class Class{};

    union Union
    {
        int i;
        
        float f;
    };

    static_assert(not Enumeration<int>);
    static_assert(not Enumeration<float>);
    static_assert(not Enumeration<bool>);
    static_assert(not Enumeration<char>);
    static_assert(not Enumeration<void>);
    static_assert(not Enumeration<int*>);
    static_assert(not Enumeration<int&>);
    static_assert(not Enumeration<int[]>);
    static_assert(not Enumeration<Struct>);
    static_assert(not Enumeration<Class>);
    static_assert(not Enumeration<Union>);

    // CV-qualified cases

    static_assert(Enumeration<const UnscopedEnum>);
    static_assert(Enumeration<volatile ScopedEnum>);
    static_assert(Enumeration<const volatile ScopedEnumWithBase>);

    // Should not satisfy with references or pointers to enums

    static_assert(not Enumeration<UnscopedEnum*>);
    static_assert(not Enumeration<ScopedEnum&>);
    static_assert(not Enumeration<const ScopedEnum*>);

    struct Incomplete;
    return not Enumeration<Incomplete>;
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