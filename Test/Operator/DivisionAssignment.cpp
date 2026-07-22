// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/DivisionAssignment.hpp"

using Alice::Operator::DivisionAssignment;
using Alice::Operator::ReturnDivisionAssignment;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // The "textbook" shape: operator/= taking Rhs by value, returning Self&.
    
    struct Ordinary
    {
        Ordinary& operator/=(int)
        {
            return *this;
        }
    };

    // No operator/= at all.

    struct Bare{};

    // operator/= exists but returns void.

    struct VoidReturning
    {
        void operator/=(int){}
    };

    // operator/= exists but returns a new Self by value instead of Self&.

    struct ValueReturning
    {
        ValueReturning operator/=(int)
        {
            return *this;
        }
    };

    // operator/= is overloaded on the Rhs type, with a different return
    // type per overload.

    struct Overloaded
    {
        Overloaded& operator/=(int)
        {
            return *this;
        }

        bool operator/=(double)
        {
            return true;
        }
    };

    // operator/= is const-qualified and returns a const reference.

    struct ConstQualified
    {
        const ConstQualified& operator/=(int) const
        {
            return *this;
        }
    };

    // Only accepts a Rhs of its own type through a const lvalue reference.
    
    struct Fraction
    {
        Fraction& operator/=(const Fraction&)
        {
            return *this;
        }
    };

    // Only accepts an lvalue Rhs of its own type (no const on the parameter).

    struct FractionLvalueOnly
    {
        FractionLvalueOnly& operator/=(FractionLvalueOnly&)
        {
            return *this;
        }
    };

    // Shares nothing with any type above: no shared base, no converting
    // constructor, no conversion operator. Used to exercise Rhs types that
    // have no conversion path at all.

    struct Unrelated{};

    // -----------------------------------------------------------------------
    // DivisionAssignment: existence and argument compatibility
    // -----------------------------------------------------------------------

    // A matching operator/= satisfies the concept.

    static_assert(DivisionAssignment<Ordinary, int>);

    // The concept only asks that the expression be well-formed, so an
    // implicit conversion to the operator's parameter type is enough.

    static_assert(DivisionAssignment<Ordinary, short>);

    // No operator/= at all never satisfies the concept.

    static_assert(not DivisionAssignment<Bare, int>);

    // A Rhs with no conversion path to any overload's parameter fails.

    static_assert(not DivisionAssignment<Ordinary, Unrelated>);
    static_assert(not DivisionAssignment<Fraction, Unrelated>);

    // The concept does not care what operator/= returns.

    static_assert(DivisionAssignment<VoidReturning, int>);
    static_assert(DivisionAssignment<ValueReturning, int>);

    // Each overload is checked against its own matching Rhs.

    static_assert(DivisionAssignment<Overloaded, int>);
    static_assert(DivisionAssignment<Overloaded, double>);

    // Works for fundamental types too, not just class types.

    static_assert(DivisionAssignment<int, int>);
    static_assert(DivisionAssignment<double, int>);
    static_assert(not DivisionAssignment<int, Unrelated>);

    // -----------------------------------------------------------------------
    // DivisionAssignment: value category via $forward
    // -----------------------------------------------------------------------
    // self /= $forward(rhs) forwards rhs the same way a forwarding-reference
    // call site would: as an rvalue when Rhs is a plain (non-reference) type,
    // and as an lvalue when Rhs is itself given as a reference type.

    // const Fraction& binds to the rvalue produced by forwarding a plain
    // Fraction, so this holds...

    static_assert(DivisionAssignment<Fraction, Fraction>);

    // ...but a parameter of type FractionLvalueOnly& (no const) cannot bind
    // to that same rvalue, so this must NOT hold...

    static_assert(not DivisionAssignment<FractionLvalueOnly, FractionLvalueOnly>);

    // ...unless Rhs is specified as an lvalue reference, which makes the
    // forwarded argument an lvalue too.

    static_assert(DivisionAssignment<FractionLvalueOnly, FractionLvalueOnly&>);

    // -----------------------------------------------------------------------
    // DivisionAssignment: const-qualification of Self
    // -----------------------------------------------------------------------

    // A non-const operator/= cannot be called through a const Self.

    static_assert(not DivisionAssignment<const Ordinary, int>);

    // A const-qualified operator/= can be called through either a const or a
    // non-const Self.

    static_assert(DivisionAssignment<ConstQualified, int>);
    static_assert(DivisionAssignment<const ConstQualified, int>);

    // -----------------------------------------------------------------------
    // ReturnDivisionAssignment: default Return (Self&)
    // -----------------------------------------------------------------------

    // The textbook shape satisfies the concept with the default Return.

    static_assert(ReturnDivisionAssignment<Ordinary, int>);

    // If the argument itself is unusable, the return type is never even
    // reached.

    static_assert(not ReturnDivisionAssignment<Bare, int>);
    static_assert(not ReturnDivisionAssignment<Ordinary, Unrelated>);

    // Returning void, or Self by value instead of Self&, fails the default
    // Return check even though DivisionAssignment itself holds for both.

    static_assert(not ReturnDivisionAssignment<VoidReturning, int>);
    static_assert(not ReturnDivisionAssignment<ValueReturning, int>);

    // A const-qualified operator/= returning const Self& does not match the
    // default (non-const) Self&, even though DivisionAssignment holds.

    static_assert(not ReturnDivisionAssignment<ConstQualified, int>);

    // Fundamental types yield a plain lvalue of themselves, matching the
    // default Self&.

    static_assert(ReturnDivisionAssignment<int, int>);

    // -----------------------------------------------------------------------
    // ReturnDivisionAssignment: explicit Return
    // -----------------------------------------------------------------------

    // Naming the actual return type explicitly makes each case above hold.

    static_assert(ReturnDivisionAssignment<VoidReturning, int, void>);
    static_assert(ReturnDivisionAssignment<ValueReturning, int, ValueReturning>);
    static_assert(ReturnDivisionAssignment<ConstQualified, int, const ConstQualified&>);

    // Trait::Same is exact: Self and Self& are different types, so asking for
    // a by-value Return when the operator actually returns a reference (or
    // vice versa) must fail.

    static_assert(not ReturnDivisionAssignment<Ordinary, int, Ordinary>);
    static_assert(not ReturnDivisionAssignment<ValueReturning, int, ValueReturning&>);

    // Each overload's own return type is checked against its own Rhs.

    static_assert(ReturnDivisionAssignment<Overloaded, int>);
    static_assert(ReturnDivisionAssignment<Overloaded, double, bool>);
    static_assert(not ReturnDivisionAssignment<Overloaded, double>);

    struct Incomplete;
    return not DivisionAssignment<Incomplete, Incomplete> and not ReturnDivisionAssignment<
    Incomplete, Incomplete>;
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