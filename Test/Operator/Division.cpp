// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Division.hpp"

using Alice::Operator::Division;
using Alice::Operator::ReturnDivision;

// Division: satisfied via a non-member operator/ found only through ADL.

struct Cents
{
    long value;
};

constexpr Cents operator/(Cents lhs, int shares) noexcept
{
    return Cents{lhs.value / shares};
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Division: a type that divides by itself and yields itself -- the golden path.

    struct Quotient
    {
        int value;

        constexpr Quotient operator/(Quotient const& rhs) const noexcept
        {
            return Quotient{value / rhs.value};
        }
    };

    // Division: no operator/ overload at all.

    struct Opaque
    {
        int value;
    };

    // Division: Rhs matters independently of Self; only Meters / double is defined.

    struct Meters
    {
        double value;

        constexpr Meters operator/(double scalar) const noexcept
        {
            return Meters{value / scalar};
        }
    };

    // ReturnDivision: Self / Self compiles, but returns something other than Self.

    struct Ratio
    {
        double value;
    };

    struct Distance
    {
        double value;

        constexpr Ratio operator/(Distance const& rhs) const noexcept
        {
            return Ratio{value / rhs.value};
        }
    };

    // Division/ReturnDivision: operator/ only callable on an rvalue *this. Instantiating
    // Self as a plain type simulates an rvalue self; instantiating it as Self& simulates
    // an lvalue self, since $forward(self) casts to decltype(self)&&, which collapses to
    // an lvalue reference whenever Self is already itself a reference type.
    
    struct RvalueOnlySelf
    {
        RvalueOnlySelf operator/(int) && noexcept;
    };

    // Division: the same forwarding is applied to Rhs, symmetrically.
    
    struct RvalueOnlyArgument{};

    struct RequiresRvalueArgument
    {
        int operator/(RvalueOnlyArgument&&) const noexcept;
    };

    // Fundamental types divide via the built-in operator.

    static_assert(Division<int, int>, "built-in operator/ should satisfy Division");
    static_assert(ReturnDivision<int, int>, "int / int returns int, matching the default Return");

    // Member operator/, Self divided by Self, returning Self.

    static_assert(Division<Quotient, Quotient>, "Quotient defines operator/(Quotient const&)");
    static_assert(ReturnDivision<Quotient, Quotient>,
    "Quotient::operator/ returns Quotient, matching the default Return");

    // No operator/ at all must fail, for both concepts.
    
    static_assert(not Division<Opaque, Opaque>, "Opaque has no operator/ overload");
    static_assert(not ReturnDivision<Opaque, Opaque>, "Opaque has no operator/ overload");

    // Rhs is significant on its own: Meters only divides by double, not by itself, and
    // double has no overload accepting a Meters.

    static_assert(Division<Meters, double>, "Meters defines operator/(double)");
    static_assert(not Division<Meters, Meters>, "Meters has no operator/(Meters const&) overload");
    static_assert(not Division<double, Meters>, "double has no operator/ overload accepting Meters"
    );
    static_assert(ReturnDivision<Meters, double>,
    "Meters::operator/ returns Meters, matching the default Return");

    // Division does not care what operator/ returns, only that it is usable at all; Distance
    // / Distance compiles but returns Ratio, so only an explicit, correct Return should pass.
    
    static_assert(Division<Distance, Distance>, "Distance defines operator/(Distance const&)");
    static_assert(not ReturnDivision<Distance, Distance>,
    "the default Return (Distance) does not match the actual return type Ratio");
    static_assert(ReturnDivision<Distance, Distance, Ratio>,
    "Distance::operator/ actually returns Ratio");
    static_assert(not ReturnDivision<Distance, Distance, int>,
    "Distance::operator/ does not return int");

    // A free function found via ADL satisfies the concept just as well as a member does.
    
    static_assert(Division<Cents, int>, "operator/(Cents, int) is visible via ADL");
    static_assert(ReturnDivision<Cents, int>,
    "operator/(Cents, int) returns Cents, matching the default Return");

    // Value category of Self is respected: a plain Self models an rvalue self and satisfies
    // the &&-qualified operator/; Self& models an lvalue self and does not.
    
    static_assert(Division<RvalueOnlySelf, int>,
    "an rvalue self can call an &&-qualified operator/");
    static_assert(not Division<RvalueOnlySelf&, int>,
    "an lvalue self cannot call an &&-qualified operator/");
    static_assert(ReturnDivision<RvalueOnlySelf, int>,
    "RvalueOnlySelf::operator/ returns RvalueOnlySelf, matching the default Return");
    static_assert(not ReturnDivision<RvalueOnlySelf&, int>,
    "an lvalue self cannot call operator/ at all");

    // Value category of Rhs is respected too, via the same forwarding.
    
    static_assert(Division<RequiresRvalueArgument, RvalueOnlyArgument>,
    "a plain Rhs is forwarded as an rvalue argument");
    static_assert(not Division<RequiresRvalueArgument, RvalueOnlyArgument&>,
    "Rhs& is forwarded as an lvalue, which cannot bind to an && parameter");

    struct Incomplete;
    return not Division<Incomplete, Incomplete> and not ReturnDivision<Incomplete, Incomplete>;
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