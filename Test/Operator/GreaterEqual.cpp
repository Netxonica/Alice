// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/GreaterEqual.hpp"

using Alice::Operator::GreaterEqual;
using Alice::Operator::ReturnGreaterEqual;

// ------------------------------------------------------------------
// Non-member operator>= found via ADL must count too.
// ------------------------------------------------------------------

struct Currency
{
    long cents{};
};

constexpr bool operator>=(Currency const& lhs, Currency const& rhs)
{
    return lhs.cents >= rhs.cents;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ------------------------------------------------------------------
    // 1. Built-in types: cheap sanity checks the concepts must get right.
    // ------------------------------------------------------------------
    
    static_assert(GreaterEqual<int, int>, "built-in int must satisfy GreaterEqual against itself");
    static_assert(ReturnGreaterEqual<int, int>,
    "int >= int is bool, so the default Return = bool must be satisfied");
    static_assert(GreaterEqual<double, int>,
    "mixed built-in arithmetic types must satisfy GreaterEqual");
    static_assert(GreaterEqual<int*, int*>, "pointer types must satisfy GreaterEqual");

    // ------------------------------------------------------------------
    // 2. Ordinary class type with a matching member operator>=.
    // ------------------------------------------------------------------

    struct Version
    {
        int value{};

        constexpr bool operator>=(Version const& rhs) const
        {
            return value >= rhs.value;
        }
    };

    static_assert(GreaterEqual<Version, Version>,
    "Version defines a member operator>= taking Version");
    static_assert(ReturnGreaterEqual<Version, Version>,
    "Version::operator>= returns bool, matching the default Return");

    // ------------------------------------------------------------------
    // 3. Type with no operator>= at all: both concepts must reject it.
    // ------------------------------------------------------------------
    
    struct NoComparison
    {
        int value{};
    };

    static_assert(not GreaterEqual<NoComparison, NoComparison>,
    "NoComparison has no operator>= and must not satisfy GreaterEqual");
    static_assert(not ReturnGreaterEqual<NoComparison, NoComparison>,
    "an unsatisfied GreaterEqual must also fail ReturnGreaterEqual");

    // ------------------------------------------------------------------
    // 4. Heterogeneous / directional comparisons: Self and Rhs differ,
    //    and the relation is not assumed to be symmetric.
    // ------------------------------------------------------------------

    struct Feet
    {
        double value{};
    };

    struct Meters
    {
        double value{};

        constexpr bool operator>=(Feet const& rhs) const
        {
            return value >= rhs.value * 0.3048;
        }
    };

    static_assert(GreaterEqual<Meters, Feet>, "Meters defines operator>= taking Feet");
    static_assert(not GreaterEqual<Feet, Meters>,
    "Feet has no operator>= taking Meters: GreaterEqual must not assume symmetry");
    static_assert(GreaterEqual<Currency, Currency>,
    "a free operator>= found via ADL must satisfy GreaterEqual");
    static_assert(ReturnGreaterEqual<Currency, Currency>, "the free operator>= above returns bool")
    ;

    // ------------------------------------------------------------------
    // 6. Return-type checks: GreaterEqual must not care what the operator
    //    returns, only ReturnGreaterEqual should.
    // ------------------------------------------------------------------

    struct Ordering{};

    struct Spaceship
    {
        Ordering operator>=(Spaceship const&) const;
    };

    static_assert(GreaterEqual<Spaceship, Spaceship>,
    "GreaterEqual only cares that the call is well-formed, not the return type");
    static_assert(not ReturnGreaterEqual<Spaceship, Spaceship>,
    "default Return is bool, but Spaceship::operator>= returns Ordering");
    static_assert(ReturnGreaterEqual<Spaceship, Spaceship, Ordering>,
    "Return can be supplied explicitly to match a non-bool result type");

    // ------------------------------------------------------------------
    // 7. Value-category sensitivity: $forward must preserve lvalue vs.
    //    rvalue self, so ref-qualified overloads are picked correctly.
    // ------------------------------------------------------------------
    
    struct LvalueOnly
    {
        constexpr bool operator>=(LvalueOnly const&) &
        {
            return true;
        }
    };

    struct RvalueOnly
    {
        constexpr bool operator>=(RvalueOnly const&) &&
        {
            return true;
        }
    };

    static_assert(GreaterEqual<LvalueOnly&, LvalueOnly const&>,
    "a &-qualified operator>= must be usable when Self is an lvalue reference");
    static_assert(not GreaterEqual<LvalueOnly, LvalueOnly const&>,
    "a &-qualified operator>= must not be usable when Self is forwarded as an rvalue");
    static_assert(GreaterEqual<RvalueOnly, RvalueOnly const&>,
    "a &&-qualified operator>= must be usable when Self is forwarded as an rvalue");
    static_assert(not GreaterEqual<RvalueOnly&, RvalueOnly const&>,
    "a &&-qualified operator>= must not be usable when Self is an lvalue reference");
    static_assert(ReturnGreaterEqual<LvalueOnly&, LvalueOnly const&>,
    "a well-formed, bool-returning comparison must satisfy ReturnGreaterEqual too");
    static_assert(not ReturnGreaterEqual<LvalueOnly, LvalueOnly const&>,
    "an ill-formed comparison cannot satisfy ReturnGreaterEqual either");

    // ------------------------------------------------------------------
    // 8. operator>= exists, but Rhs has no path to the parameter type.
    // ------------------------------------------------------------------

    struct OnlyComparesToOwnType
    {
        constexpr bool operator>=(OnlyComparesToOwnType const&) const
        {
            return true;
        }
    };

    struct Unrelated{};

    static_assert(GreaterEqual<OnlyComparesToOwnType, OnlyComparesToOwnType>,
    "sanity check: the type must compare against itself");
    static_assert(not GreaterEqual<OnlyComparesToOwnType, Unrelated>,
    "Unrelated does not convert to OnlyComparesToOwnType and has no matching overload");

    struct Incomplete;
    return not GreaterEqual<Incomplete, Incomplete> and not ReturnGreaterEqual<Incomplete,
    Incomplete>;
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