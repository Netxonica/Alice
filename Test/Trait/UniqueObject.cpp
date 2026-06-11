// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/UniqueObject.hpp"

using Alice::Trait::UniqueObject;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: unsigned integer types — every bit pattern maps to exactly one
    // value; no padding possible in a fundamental type.
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(UniqueObject<unsigned char>);
    static_assert(UniqueObject<unsigned short>);
    static_assert(UniqueObject<unsigned int>);
    static_assert(UniqueObject<unsigned long>);
    static_assert(UniqueObject<unsigned long long>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: signed integer types — two's complement is mandated as of C++20,
    // so every bit pattern is also a distinct value.
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(UniqueObject<signed char>);
    static_assert(UniqueObject<short>);
    static_assert(UniqueObject<int>);
    static_assert(UniqueObject<long>);
    static_assert(UniqueObject<long long>);
    static_assert(UniqueObject<char>);   // distinct type from signed/unsigned char

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: character types with fixed widths.
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(UniqueObject<char8_t>);
    static_assert(UniqueObject<char16_t>);
    static_assert(UniqueObject<char32_t>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: pointer types — two equal pointers always have the same bit pattern
    // on all common ABIs.
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(UniqueObject<int*>);
    static_assert(UniqueObject<void*>);
    static_assert(UniqueObject<const int*>);   // pointer-to-const; the pointer itself is unique

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: arrays inherit uniqueness from their element type.
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(UniqueObject<unsigned char[8]>);
    static_assert(UniqueObject<int[4]>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: structs without padding.  The sizeof guard is a precondition that
    // makes the test self-documenting and prevents a silent false-positive on any
    // exotic platform where the layout assumption might not hold.
    // ─────────────────────────────────────────────────────────────────────────────

    struct FourBytes
    {
        unsigned char a, b, c, d;
    };

    static_assert(sizeof(FourBytes) == 4 * sizeof(unsigned char));
    static_assert(UniqueObject<FourBytes>);

    struct TwoInts
    {
        int a, b;
    };

    static_assert(sizeof(TwoInts) == 2 * sizeof(int));
    static_assert(UniqueObject<TwoInts>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: const-qualification does not alter object representation.
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(UniqueObject<const int> == UniqueObject<int>);
    static_assert(UniqueObject<const float> == UniqueObject<float>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Negative: floating-point types — IEEE 754 permits multiple bit patterns for
    // the same abstract value (e.g. ±0.0 compare equal; distinct NaN encodings).
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(not UniqueObject<float>);
    static_assert(not UniqueObject<double>);
    static_assert(not UniqueObject<long double>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Negative: a struct is non-unique if any member is non-unique.
    // ─────────────────────────────────────────────────────────────────────────────

    struct HasFloat
    {
        float x;
    };

    struct HasDouble
    {
        double x;
    };

    static_assert(not UniqueObject<HasFloat>);
    static_assert(not UniqueObject<HasDouble>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Negative: non-trivially copyable types are excluded by definition, regardless
    // of what their data members look like.
    // ─────────────────────────────────────────────────────────────────────────────

    struct WithDtor
    {
        int x;
        
        ~WithDtor(){}
    };

    static_assert(not UniqueObject<WithDtor>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Portable padding probe: on platforms where sizeof(CharThenInt) exceeds
    // sizeof(char) + sizeof(int), structural padding exists and the struct must NOT
    // satisfy UniqueObject.  On the rare platform with no such padding the members
    // are both uniquely represented, so it will satisfy.  The equivalence is
    // therefore correct in both directions without hard-coding a platform assumption.
    // ─────────────────────────────────────────────────────────────────────────────

    struct CharThenInt
    {
        char a;
        
        int b;
    };

    static_assert(UniqueObject<CharThenInt> == (sizeof(CharThenInt) == sizeof(char) + sizeof(int)))
    ;

    struct Incomplete;
    return not UniqueObject<Incomplete>;
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