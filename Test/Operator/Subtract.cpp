// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Subtract.hpp"

using Alice::Operator::Subtract;
using Alice::Operator::ReturnSubtract;

// Subtraction supplied as a free function rather than a member, found via ADL.

struct Kelvin{};

struct DegreeDelta{};

// (Given a trivial body, unlike the member declarations above, only so this
// internal-linkage free function isn't flagged as declared-but-never-defined;
// it is still never actually called, since a requires-expression only checks
// well-formedness and never evaluates the expressions inside it.)

DegreeDelta operator-(Kelvin const&, Kelvin const&)
{
    return DegreeDelta{};
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // -------------------------------------------------------------------------
    // Fixtures
    // -------------------------------------------------------------------------

    // No operator- overload whatsoever.

    struct Inert{};

    // Subtracts against its own type and returns its own type.

    struct Vector
    {
        Vector operator-(Vector const&) const;
    };

    // operator- returns something other than Self.

    struct Distance{};

    struct Point
    {
        Distance operator-(Point const&) const;
    };

    // operator- only accepts a Rhs other than Self.

    struct Scalar{};

    struct Measurement
    {
        Measurement operator-(Scalar const&) const;
    };

    // Only subtractable when *this is an rvalue.

    struct Fuel
    {
        Fuel operator-(Fuel const&) &&;
    };

    // Deliberately one-directional: Left - Right exists, Right - Left does not.

    struct Right{};

    struct Left
    {
        Left operator-(Right const&) const;
    };

    // -------------------------------------------------------------------------
    // Subtract
    // -------------------------------------------------------------------------

    // Built-in arithmetic types, including mixed operand types.
    
    static_assert(Subtract<int, int>);
    static_assert(Subtract<double, int>);
    static_assert(Subtract<int, double>);

    // Built-in pointer subtraction is arithmetic subtraction too.
    
    static_assert(Subtract<int*, int*>);

    // A class overloading operator- against its own type.
    
    static_assert(Subtract<Vector, Vector>);

    // A class overloading operator- against a different Rhs.
    
    static_assert(Subtract<Measurement, Scalar>);
    static_assert(not Subtract<Measurement, Measurement>);
    static_assert(not Subtract<Scalar, Scalar>);

    // A free operator- found via ADL is honored just as a member would be.
    
    static_assert(Subtract<Kelvin, Kelvin>);

    // No operator- overload anywhere, in either direction.
    
    static_assert(not Subtract<Inert, Inert>);
    static_assert(not Subtract<Inert, int>);
    static_assert(not Subtract<int, Inert>);

    // Operand order matters: satisfying it one way says nothing about the other.
    
    static_assert(Subtract<Left, Right>);
    static_assert(not Subtract<Right, Left>);

    // $forward must carry Self's value category through correctly: as an rvalue,
    // the rvalue-qualified overload applies ...
    
    static_assert(Subtract<Fuel, Fuel>);
    
    // ... but as an lvalue (Self given as a reference type), it must not.
    
    static_assert(not Subtract<Fuel&, Fuel>);

    // -------------------------------------------------------------------------
    // ReturnSubtract
    // -------------------------------------------------------------------------

    // Return defaults to Self, and matches when the operator genuinely returns Self.
    
    static_assert(ReturnSubtract<int, int>);
    static_assert(ReturnSubtract<Vector, Vector>);
    static_assert(ReturnSubtract<Measurement, Scalar>);

    // The defaulted Return (= Self) is rejected when the real return type differs ...
    
    static_assert(not ReturnSubtract<Point, Point>);
    
    // ... but naming that real return type explicitly is accepted.
    
    static_assert(ReturnSubtract<Point, Point, Distance>);

    // The match is exact, not merely convertible: int - int returns int, and int
    // converts to double, but they are not the same type.
    
    static_assert(not ReturnSubtract<int, int, double>);

    // Works through a free operator- too, given an explicit Return.
    
    static_assert(ReturnSubtract<Kelvin, Kelvin, DegreeDelta>);
    static_assert(not ReturnSubtract<Kelvin, Kelvin>);

    // No operator- overload fails ReturnSubtract no matter what Return is asked for.
    
    static_assert(not ReturnSubtract<Inert, Inert>);
    static_assert(not ReturnSubtract<Inert, Inert, Inert>);
    
    struct Incomplete;
    return not Subtract<Incomplete, Incomplete> and not ReturnSubtract<Incomplete, Incomplete>;
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