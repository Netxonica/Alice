// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Less.hpp"

using Alice::Operator::Less;
using Alice::Operator::ReturnLess;

// Heterogeneous pair with a *free* operator<, found via ADL, again
// defined in one direction only.

struct Weight
{
    double kilograms;
};

struct Currency
{
    double amount;
};

bool operator<(Weight const& lhs, Currency const& rhs)
{
    return lhs.kilograms < rhs.amount;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // A conventional homogeneous operator<, returning bool.

    struct Ordinal
    {
        int value;

        bool operator<(Ordinal const& rhs) const
        {
            return value < rhs.value;
        }
    };

    // No relational operators at all.

    struct Opaque
    {
        int value;
    };

    // Heterogeneous pair with a *member* operator<, defined in one
    // direction only, to check directionality.

    struct Feet
    {
        double value;
    };

    struct Meters
    {
        double value;

        bool operator<(Feet const& rhs) const
        {
            return value < rhs.value * 0.3048;
        }
    };

    // operator< that is well-formed but does not return bool: Less must
    // not care, ReturnLess must be exact about it.

    struct LegacyOrdinal
    {
        int value;

        int operator<(LegacyOrdinal const& rhs) const
        {
            return value < rhs.value ? 1 : 0;
        }
    };

    struct VoidOrdinal
    {
        void operator<(VoidOrdinal const&) const{}
    };

    // Stands in for a lazily-evaluated / expression-template comparison
    // result, to prove ReturnLess works for arbitrary Return types, not
    // just bool-like ones.

    struct Tribool
    {
        signed char state;
    };

    struct LazyOrdinal
    {
        int value;

        Tribool operator<(LazyOrdinal const& rhs) const
        {
            return Tribool{static_cast<signed char>(value < rhs.value ? 1 : 0)};
        }
    };

    // =====================================================================
    // Less<Self, Rhs>
    // =====================================================================

    // A conventional homogeneous operator< is detected.

    static_assert(Less<Ordinal, Ordinal>,
    "Ordinal defines operator<(Ordinal const&) const, so it must satisfy Less<Ordinal, Ordinal>");

    // Built-in types must work with no user-defined operator at all.

    static_assert(Less<int, int>, "built-in int must satisfy Less<int, int>");
    static_assert(Less<double, double>, "built-in double must satisfy Less<double, double>");
    static_assert(Less<int*, int*>, "built-in pointers must satisfy Less<int*, int*>");

    // No operator< at all must be rejected.

    static_assert(not Less<Opaque, Opaque>,
    "Opaque declares no relational operators, so it must not satisfy Less<Opaque, Opaque>");

    // Unrelated types must be rejected, even if each is separately comparable
    // to itself.

    static_assert(not Less<Ordinal, Opaque>,
    "Ordinal has no operator<(Opaque const&) overload, so it must not satisfy Less<Ordinal, Opaque"
    ">");

    // Heterogeneous, member-based operator< is directional.

    static_assert(Less<Meters, Feet>,
    "Meters defines operator<(Feet const&) const, so it must satisfy Less<Meters, Feet>");
    static_assert(not Less<Feet, Meters>,
    "Feet defines no operator< at all, so it must not satisfy Less<Feet, Meters>");

    // Heterogeneous, free-function operator< is likewise directional, and is
    // found via ADL even though it is not a member.

    static_assert(Less<Weight, Currency>,
    "a free operator<(Weight const&, Currency const&) exists, so Less<Weight, Currency> must hold")
    ;
    static_assert(not Less<Currency, Weight>,
    "no operator<(Currency const&, Weight const&) exists, so Less<Currency, Weight> must not hold")
    ;

    // Less only checks that the expression is well-formed: it must not care
    // what operator< actually returns.

    static_assert(Less<LegacyOrdinal, LegacyOrdinal>,
    "Less must be satisfied even though operator< returns int instead of bool");
    static_assert(Less<VoidOrdinal, VoidOrdinal>,
    "Less must be satisfied even though operator< returns void");
    static_assert(Less<LazyOrdinal, LazyOrdinal>,
    "Less must be satisfied even though operator< returns a non-bool proxy type");

    // =====================================================================
    // ReturnLess<Self, Rhs, Return = bool>
    // =====================================================================

    // The default Return argument is bool, and behaves identically to
    // specifying it explicitly.
    
    static_assert(ReturnLess<Ordinal, Ordinal>,
    "Ordinal::operator< returns bool, so it must satisfy the default ReturnLess<Ordinal, Ordinal>")
    ;
    static_assert(ReturnLess<Ordinal, Ordinal, bool>,
    "explicitly requesting Return = bool must behave the same as the default");

    // Built-in relational operators yield bool, satisfying the default.
    
    static_assert(ReturnLess<int, int>, "built-in int < int yields bool");
    static_assert(ReturnLess<int*, int*>, "built-in pointer < pointer yields bool");

    // No operator< means neither concept can be satisfied.
    
    static_assert(not ReturnLess<Opaque, Opaque>,
    "Opaque declares no relational operators, so it must not satisfy ReturnLess<Opaque, Opaque>");

    // ReturnLess must require the *exact* return type, not merely something
    // convertible to it: int is convertible to bool, but is not bool.
    
    static_assert(not ReturnLess<LegacyOrdinal, LegacyOrdinal>,
    "LegacyOrdinal::operator< returns int, so the default (bool) ReturnLess must fail");
    static_assert(not ReturnLess<LegacyOrdinal, LegacyOrdinal, bool>,
    "int is convertible to bool but is not the same type as bool, so this must fail");
    static_assert(ReturnLess<LegacyOrdinal, LegacyOrdinal, int>,
    "requesting Return = int must succeed, since operator< genuinely returns int");

    // Arbitrary, non-arithmetic Return types must be matched exactly too.
    
    static_assert(not ReturnLess<LazyOrdinal, LazyOrdinal>,
    "LazyOrdinal::operator< returns Tribool, so the default (bool) ReturnLess must fail");
    static_assert(ReturnLess<LazyOrdinal, LazyOrdinal, Tribool>,
    "requesting Return = Tribool must succeed, since operator< genuinely returns Tribool");

    // void is an unusual but legal return type: Less accepts it, but the
    // default ReturnLess must not, since void is not bool.
    
    static_assert(not ReturnLess<VoidOrdinal, VoidOrdinal>,
    "VoidOrdinal::operator< returns void, so the default (bool) ReturnLess must fail");
    static_assert(ReturnLess<VoidOrdinal, VoidOrdinal, void>,
    "requesting Return = void must succeed, since operator< genuinely returns void");

    // Heterogeneous and free-function cases mirror the Less checks above.
    
    static_assert(ReturnLess<Meters, Feet>,
    "Meters::operator<(Feet const&) returns bool, so the default ReturnLess<Meters, Feet> must "
    "hold");
    static_assert(not ReturnLess<Feet, Meters>,
    "Feet has no operator< at all, so it must not satisfy ReturnLess<Feet, Meters>");
    static_assert(ReturnLess<Weight, Currency>,
    "the free operator< for (Weight, Currency) returns bool, so the default ReturnLess must hold");
    static_assert(not ReturnLess<Currency, Weight>,
    "no operator<(Currency const&, Weight const&) exists, so ReturnLess<Currency, Weight> must not"
    " hold");

    struct Incomplete;
    return not Less<Incomplete, Incomplete> and not ReturnLess<Incomplete, Incomplete>;
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