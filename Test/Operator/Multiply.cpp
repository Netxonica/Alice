// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Multiply.hpp"

using Alice::Operator::Multiply;
using Alice::Operator::ReturnMultiply;

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

    static_assert(not Multiply<NotMultiplicable, NotMultiplicable>,
    "a type with no operator* must not satisfy Multiply");
    static_assert(not Multiply<NotMultiplicable, int>,
    "no operator* exists between NotMultiplicable and int");
    static_assert(not Multiply<int, NotMultiplicable>,
    "no operator* exists between int and NotMultiplicable");
    static_assert(Multiply<int, int>, "built-in operator* must satisfy Multiply");
    static_assert(Multiply<int, double>,
    "mixed built-in arithmetic types satisfy Multiply via usual conversions");
    static_assert(Multiply<double, int>,
    "Multiply must not care about argument order for built-ins");
    static_assert(Multiply<Scalar, Scalar>, "Scalar defines Scalar * Scalar");
    static_assert(Multiply<Vector2, Scalar>, "Vector2 defines Vector2 * Scalar");
    static_assert(not Multiply<Scalar, Vector2>,
    "Scalar * Vector2 is not defined, only the reverse order");
    static_assert(not Multiply<Vector2, Vector2>, "Vector2 * Vector2 is not defined");
    static_assert(Multiply<Vector2 const&, Scalar const&>,
    "const lvalue-reference operands still bind to the by-value operator*");
    static_assert(Multiply<MutatingScale, MutatingScale>,
    "Multiply only requires the expression to be well-formed, not what it returns");

    // ---------------------------------------------------------------------
    // ReturnMultiply: is `self * rhs` well-formed AND exactly of type Return?
    // ---------------------------------------------------------------------

    static_assert(ReturnMultiply<Scalar, Scalar>,
    "Scalar * Scalar really returns Scalar, matching the default Return = Self");
    static_assert(ReturnMultiply<Scalar, Scalar, Scalar>,
    "explicit Return works the same way as the default");
    static_assert(ReturnMultiply<Vector2, Scalar>,
    "Vector2 * Scalar returns Vector2, matching the default Return = Self");
    static_assert(not ReturnMultiply<Vector2, Scalar, Scalar>,
    "Vector2 * Scalar does not return Scalar");
    static_assert(Multiply<Length, Length>, "Length * Length is well-formed");
    static_assert(not ReturnMultiply<Length, Length>,
    "Length * Length returns Area, not Length, so the default Return must fail");
    static_assert(ReturnMultiply<Length, Length, Area>,
    "explicit Return = Area matches what Length * Length actually returns");
    static_assert(ReturnMultiply<int, double, double>,
    "int * double returns double via the usual arithmetic conversions");
    static_assert(not ReturnMultiply<int, double, int>, "int * double does not return int");
    static_assert(not ReturnMultiply<MutatingScale, MutatingScale>,
    "operator* returns MutatingScale&, which is not the same type as MutatingScale");
    static_assert(ReturnMultiply<MutatingScale, MutatingScale, MutatingScale&>,
    "the exact reference type returned does satisfy ReturnMultiply");

    struct Incomplete;
    return not Multiply<Incomplete, Incomplete> and not ReturnMultiply<Incomplete, Incomplete>;
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