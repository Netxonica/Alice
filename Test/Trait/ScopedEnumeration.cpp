// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/ScopedEnumeration.hpp"

using Alice::Trait::ScopedEnumeration;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // True positives: scoped enumerations
    enum class Color
    {
        Red,
        Green,
        Blue
    };

    enum class Direction : unsigned char
    {
        North,
        South,
        East,
        West
    };

    enum struct Flags : long
    {
        None = 0,
        Read = 1,
        Write = 2
    };

    // True negatives: unscoped enumerations

    enum PlainColor
    {
        PlainRed,
        PlainGreen,
        PlainBlue
    };

    enum PlainWithBase : int
    {
        A,
        B,
        C
    };

    // True negatives: non-enumeration types

    struct Struct{};

    class Class{};

    union Union
    {
        int i;
        float f;
    };

    using Int = int;

    // --- Scoped enumerations must satisfy the concept ---

    static_assert(ScopedEnumeration<Color>);
    static_assert(ScopedEnumeration<Direction>);
    static_assert(ScopedEnumeration<Flags>);
    static_assert(ScopedEnumeration<const Color>);
    static_assert(ScopedEnumeration<volatile Color>);
    static_assert(ScopedEnumeration<const volatile Color>);

    // --- Unscoped enumerations must NOT satisfy the concept ---

    static_assert(not ScopedEnumeration<PlainColor>);
    static_assert(not ScopedEnumeration<PlainWithBase>);

    // --- Non-enumeration types must NOT satisfy the concept ---

    static_assert(not ScopedEnumeration<Struct>);
    static_assert(not ScopedEnumeration<Class>);
    static_assert(not ScopedEnumeration<Union>);
    static_assert(not ScopedEnumeration<Int>);
    static_assert(not ScopedEnumeration<int>);
    static_assert(not ScopedEnumeration<float>);
    static_assert(not ScopedEnumeration<bool>);
    static_assert(not ScopedEnumeration<void>);

    // --- Reference variants must NOT satisfy the concept ---

    static_assert(not ScopedEnumeration<Color&>);
    static_assert(not ScopedEnumeration<Color&&>);
    static_assert(not ScopedEnumeration<Color*>);

    // --- Pointers and arrays of scoped enumerations are not enumerations themselves ---

    static_assert(not ScopedEnumeration<Color[3]>);
    static_assert(not ScopedEnumeration<Color(*)[3]>);

    struct Incomplete;
    return not ScopedEnumeration<Incomplete>;
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