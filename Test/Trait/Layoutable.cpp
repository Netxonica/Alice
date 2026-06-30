// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Layoutable.hpp"

using Alice::Trait::Layoutable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─────────────────────────────────────────────────────────────────────────────
    // Auxiliary types (all standard-layout)
    // ─────────────────────────────────────────────────────────────────────────────

    struct XY
    {
        int x, y;
    };

    struct RowCol
    {
        int row, col;
    };  // same member-type sequence as XY

    struct HasInt
    {
        int v;
    };

    struct HasFloat
    {
        float v;
    };

    struct Triple
    {
        int a, b, c;
    };

    struct Empty1{};

    struct Empty2{};

    // cv-qualified member field vs. mutable field

    struct WithConstMember
    {
        const int x;
        
        int y;
    };

    struct WithMutMember
    {
        int x, y;
    };

    enum class Byte1 : unsigned char
    {
        A,
        B
    };

    enum class Byte2 : unsigned char
    {
        X,
        Y,
        Z
    };

    enum class Word : unsigned int
    {
        Lo,
        Hi
    };

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive assertions (Layoutable must hold)
    // ─────────────────────────────────────────────────────────────────────────────

    // Reflexive for fundamental scalars

    static_assert(Layoutable<int, int>);
    static_assert(Layoutable<float, float>);
    static_assert(Layoutable<double, double>);
    static_assert(Layoutable<char, char>);

    // cv-qualification never changes layout

    static_assert(Layoutable<int, const int>);
    static_assert(Layoutable<const int, int>);
    static_assert(Layoutable<int, volatile int>);
    static_assert(Layoutable<int, const volatile int>);
    static_assert(Layoutable<const float, volatile float>);

    // Standard-layout structs with the same member-type sequence

    static_assert(Layoutable<XY, RowCol>, "same member-type sequence");
    static_assert(Layoutable<RowCol, XY>, "layout-compatibility is symmetric");
    static_assert(Layoutable<XY, XY>, "layout-compatibility is reflexive");

    // cv on an individual member field does not break layout-compatibility

    static_assert(Layoutable<WithConstMember, WithMutMember>,
    "const on a member field should not prevent layout-compatibility");

    // Empty structs (zero-member sequences trivially match)

    static_assert(Layoutable<Empty1, Empty2>);
    static_assert(Layoutable<Empty1, Empty1>);

    // Arrays: same element type and same extent

    static_assert(Layoutable<int[4], int[4]>);
    static_assert(Layoutable<int[4], const int[4]>);  // cv on element type
    static_assert(Layoutable<double[2], double[2]>);

    // Scoped enumerations that share the same underlying type

    static_assert(Layoutable<Byte1, Byte2>, "same underlying type");
    static_assert(Layoutable<Byte2, Byte1>, "layout-compatibility is symmetric");

    // ─────────────────────────────────────────────────────────────────────────────
    // Negative assertions (Layoutable must NOT hold)
    // ─────────────────────────────────────────────────────────────────────────────

    // Distinct fundamental types (different type, possibly different representation)

    static_assert(not Layoutable<int, float>);
    static_assert(not Layoutable<int, double>);
    static_assert(not Layoutable<float, double>);
    static_assert(not Layoutable<int, char>);
    static_assert(not Layoutable<int, long long>);

    // Structs whose corresponding member types differ

    static_assert(not Layoutable<HasInt, HasFloat>,
    "structs with different member types must not be layout-compatible");

    // Structs with different member counts
    
    static_assert(not Layoutable<HasInt, Triple>);
    static_assert(not Layoutable<Triple, HasInt>);  // also check the reverse

    // Struct vs. scalar
    
    static_assert(not Layoutable<HasInt, int>);
    static_assert(not Layoutable<int, HasInt>);

    // Arrays with a different element type

    static_assert(not Layoutable<int[4], float[4]>);

    // Arrays with a different extent

    static_assert(not Layoutable<int[4], int[8]>);

    // Enumerations with different underlying types

    static_assert(not Layoutable<Byte1, Word>,
    "enums with different underlying types must not be layout-compatible");

    struct Incomplete;
    return not Layoutable<Incomplete, Incomplete>;
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