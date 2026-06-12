// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/Underlying.hpp"

using Alice::Trait::Same;
using Alice::Meta::Underlying;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Fixtures: one enum per legal integral underlying type ──────────────────────
    
    enum class WithInt : int
    {
        A
    };

    enum class WithUnsignedInt : unsigned int
    {
        A
    };

    enum class WithChar : char
    {
        A
    };

    enum class WithSignedChar : signed char
    {
        A
    };
    
    enum class WithUnsignedChar : unsigned char
    {
        A
    };
    
    enum class WithShort : short
    {
        A
    };
    
    enum class WithUnsignedShort : unsigned short
    {
        A
    };
    
    enum class WithLong : long
    {
        A
    };

    enum class WithUnsignedLong : unsigned long
    {
        A
    };

    enum class WithLongLong : long long
    {
        A
    };

    enum class WithUnsignedLLong : unsigned long long
    {
        A
    };

    enum class WithWcharT : wchar_t
    {
        A
    };

    enum class WithChar8T : char8_t
    {
        A
    };

    enum class WithChar16T : char16_t
    {
        A
    };

    enum class WithChar32T : char32_t
    {
        A
    };

    // Implicit-int: no fixed underlying type specified — [dcl.enum] §9.7.1

    enum class WithDefaultUnderlying
    {
        A
    };

    // Unscoped enum — underlying type also defaults to int for single-zero enumerator
    
    enum PlainEnum
    {
        PlainA
    };

    // ── Positive: Underlying<E> must equal the declared underlying type ────────────

    static_assert(Same<Underlying<WithInt>, int>);
    static_assert(Same<Underlying<WithUnsignedInt>, unsigned int>);
    static_assert(Same<Underlying<WithChar>, char>);
    static_assert(Same<Underlying<WithSignedChar>, signed char>);
    static_assert(Same<Underlying<WithUnsignedChar>, unsigned char>);
    static_assert(Same<Underlying<WithShort>, short>);
    static_assert(Same<Underlying<WithUnsignedShort>, unsigned short>);
    static_assert(Same<Underlying<WithLong>, long>);
    static_assert(Same<Underlying<WithUnsignedLong>, unsigned long>);
    static_assert(Same<Underlying<WithLongLong>, long long>);
    static_assert(Same<Underlying<WithUnsignedLLong>, unsigned long long>);
    static_assert(Same<Underlying<WithWcharT>, wchar_t>);
    static_assert(Same<Underlying<WithChar8T>, char8_t>);
    static_assert(Same<Underlying<WithChar16T>, char16_t>);
    static_assert(Same<Underlying<WithChar32T>, char32_t>);
    static_assert(Same<Underlying<WithDefaultUnderlying>, int>);
    static_assert(Same<Underlying<PlainEnum>, unsigned>);

    // ── Aliasing: a type alias of an enum must forward to the same underlying type ─

    using AliasOfWithInt = WithInt;

    static_assert(Same<Underlying<AliasOfWithInt>, int>);

    enum class Incomplete;
    return Same<int, Underlying<Incomplete>>;
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