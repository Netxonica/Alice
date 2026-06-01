// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/Conditional.hpp"

using Alice::Trait::Same;
using Alice::Meta::Conditional;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─── Dummy aggregate types ─────────────────────────────────────────────────

    struct Foo{};

    struct Bar{};

    // ══════════════════════════════════════════════════════════════════════════
    // 1.  Condition == true  →  the first type (True) is selected
    // ══════════════════════════════════════════════════════════════════════════

    static_assert(Same<Conditional<true, int, float>, int>);
    static_assert(Same<Conditional<true, float, int>, float>);
    static_assert(Same<Conditional<true, void, int>, void>);
    static_assert(Same<Conditional<true, int*, float*>, int*>);
    static_assert(Same<Conditional<true, int&, float&>, int&>);
    static_assert(Same<Conditional<true, const int, int>, const int>);
    static_assert(Same<Conditional<true, int, const int>, int>);
    static_assert(Same<Conditional<true, Foo, Bar>, Foo>);

    // ══════════════════════════════════════════════════════════════════════════
    // 2.  Condition == false  →  the second type (False) is selected
    // ══════════════════════════════════════════════════════════════════════════

    static_assert(Same<Conditional<false, int, float>, float>);
    static_assert(Same<Conditional<false, float, int>, int>);
    static_assert(Same<Conditional<false, int, void>, void>);
    static_assert(Same<Conditional<false, int*, float*>, float*>);
    static_assert(Same<Conditional<false, int&, float&>, float&>);
    static_assert(Same<Conditional<false, const int, int>, int>);
    static_assert(Same<Conditional<false, int, const int>, const int>);
    static_assert(Same<Conditional<false, Foo, Bar>, Bar>);

    // ══════════════════════════════════════════════════════════════════════════
    // 3.  Negative checks: the *wrong* type must NOT be returned
    // ══════════════════════════════════════════════════════════════════════════

    static_assert(not Same<Conditional<true, int, float>, float>);
    static_assert(not Same<Conditional<false, int, float>, int>);
    static_assert(not Same<Conditional<true, Foo, Bar>, Bar>);
    static_assert(not Same<Conditional<false, Foo, Bar>, Foo>);
    static_assert(not Same<Conditional<true, int, const int>, const int>);
    static_assert(not Same<Conditional<false, const int, int>, const int>);

    // ══════════════════════════════════════════════════════════════════════════
    // 4.  Both types identical: result is always that same type regardless of
    //     the condition
    // ══════════════════════════════════════════════════════════════════════════

    static_assert(Same<Conditional<true, int, int>, int>);
    static_assert(Same<Conditional<false, int, int>, int>);
    static_assert(Same<Conditional<true, Foo, Foo>, Foo>);
    static_assert(Same<Conditional<false, Foo, Foo>, Foo>);

    // ══════════════════════════════════════════════════════════════════════════
    // 5.  Nested conditionals compose correctly
    // ══════════════════════════════════════════════════════════════════════════
    // Inner conditional in the True slot

    static_assert(Same<Conditional<true, Conditional<true, int, float>, double>, int>);
    static_assert(Same<Conditional<true, Conditional<false, int, float>, double>, float>);

    // Inner conditional in the False slot

    static_assert(Same<Conditional<false, double, Conditional<true, int, float>>, int>);
    static_assert(Same<Conditional<false, double, Conditional<false, int, float>>, float>);

    // Both slots are nested conditionals

    static_assert(Same<Conditional<true, Conditional<false, int, float>, Conditional<true, long,
    double>>, float>);
    static_assert(Same<Conditional<false, Conditional<false, int, float>, Conditional<true, long,
    double>>, long>);

    // ══════════════════════════════════════════════════════════════════════════
    // 6.  The alias is transparent: the resolved type is directly usable as a
    //     concrete type for variable declarations
    // ══════════════════════════════════════════════════════════════════════════

    constexpr Conditional<true, int, float> trueInt = 7;
    constexpr Conditional<false, int, float> falseFloat = 3.14f;
    constexpr Conditional<true, Foo, Bar> trueFoo{};
    constexpr Conditional<false, Foo, Bar> falseBar{};

    static_assert(Same<decltype(trueInt), const int>);
    static_assert(Same<decltype(falseFloat), const float>);
    static_assert(Same<decltype(trueFoo), const Foo>);
    static_assert(Same<decltype(falseBar), const Bar>);

    struct Incomplete;
    return Same<Incomplete, Conditional<true, Incomplete, int>>;
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