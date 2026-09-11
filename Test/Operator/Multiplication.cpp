// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Multiplication.hpp"

using Alice::Operator::Multiplication;
using Alice::Operator::ReturnMultiplication;

// Homogeneous: Scalar * Scalar -> Scalar.

struct Scalar
{
    int value;

    friend Scalar operator*(Scalar lhs, Scalar rhs)
    {
        return Scalar{lhs.value * rhs.value};
    }
};

// Heterogeneous and asymmetric: Vector2 * Scalar -> Vector2.
// Scalar * Vector2 and Vector2 * Vector2 are deliberately NOT defined.

struct Vector2
{
    int x, y;

    friend Vector2 operator*(Vector2 lhs, Scalar rhs)
    {
        return Vector2{lhs.x * rhs.value, lhs.y * rhs.value};
    }
};

// Multiply that changes type, like physical units: Length * Length -> Area.
struct Area
{
    double squareMeters;
};

struct Length
{
    double meters;

    friend Area operator*(Length lhs, Length rhs)
    {
        return Area{lhs.meters * rhs.meters};
    }
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------
    // Fixture types
    // ---------------------------------------------------------------

    // No operator* whatsoever.

    struct NotMultiplicable
    {
        int value;
    };

    // operator* that mutates *this and returns a reference to it, instead of
    // producing a new value. Multiply doesn't care about this; ReturnMultiply
    // should, since it returns MutatingScale&, not MutatingScale.

    struct MutatingScale
    {
        int value;

        MutatingScale& operator*(MutatingScale const& rhs)
        {
            value *= rhs.value;
            return *this;
        }
    };

    // ---------------------------------------------------------------------
    // Multiply: is `self * rhs` well-formed at all?
    // ---------------------------------------------------------------------

    static_assert(not Multiplication<NotMultiplicable, NotMultiplicable>,
    "a type with no operator* must not satisfy Multiplication");
    static_assert(not Multiplication<NotMultiplicable, int>,
    "no operator* exists between NotMultiplicable and int");
    static_assert(not Multiplication<int, NotMultiplicable>,
    "no operator* exists between int and NotMultiplicable");
    static_assert(Multiplication<int, int>, "built-in operator* must satisfy Multiplication");
    static_assert(Multiplication<int, double>,
    "mixed built-in arithmetic types satisfy Multiply via usual conversions");
    static_assert(Multiplication<double, int>,
    "Multiply must not care about argument order for built-ins");
    static_assert(Multiplication<Scalar, Scalar>, "Scalar defines Scalar * Scalar");
    static_assert(Multiplication<Vector2, Scalar>, "Vector2 defines Vector2 * Scalar");
    static_assert(not Multiplication<Scalar, Vector2>,
    "Scalar * Vector2 is not defined, only the reverse order");
    static_assert(not Multiplication<Vector2, Vector2>, "Vector2 * Vector2 is not defined");
    static_assert(Multiplication<Vector2 const&, Scalar const&>,
    "const lvalue-reference operands still bind to the by-value operator*");
    static_assert(Multiplication<MutatingScale, MutatingScale>,
    "Multiply only requires the expression to be well-formed, not what it returns");

    // ---------------------------------------------------------------------
    // ReturnMultiply: is `self * rhs` well-formed AND exactly of type Return?
    // ---------------------------------------------------------------------

    static_assert(ReturnMultiplication<Scalar, Scalar>,
    "Scalar * Scalar really returns Scalar, matching the default Return = Self");
    static_assert(ReturnMultiplication<Scalar, Scalar, Scalar>,
    "explicit Return works the same way as the default");
    static_assert(ReturnMultiplication<Vector2, Scalar>,
    "Vector2 * Scalar returns Vector2, matching the default Return = Self");
    static_assert(not ReturnMultiplication<Vector2, Scalar, Scalar>,
    "Vector2 * Scalar does not return Scalar");
    static_assert(Multiplication<Length, Length>, "Length * Length is well-formed");
    static_assert(not ReturnMultiplication<Length, Length>,
    "Length * Length returns Area, not Length, so the default Return must fail");
    static_assert(ReturnMultiplication<Length, Length, Area>,
    "explicit Return = Area matches what Length * Length actually returns");
    static_assert(ReturnMultiplication<int, double, double>,
    "int * double returns double via the usual arithmetic conversions");
    static_assert(not ReturnMultiplication<int, double, int>, "int * double does not return int");
    static_assert(not ReturnMultiplication<MutatingScale, MutatingScale>,
    "operator* returns MutatingScale&, which is not the same type as MutatingScale");
    static_assert(ReturnMultiplication<MutatingScale, MutatingScale, MutatingScale&>,
    "the exact reference type returned does satisfy ReturnMultiply");

    struct Incomplete;
    return not Multiplication<Incomplete, Incomplete> and not ReturnMultiplication<Incomplete,
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