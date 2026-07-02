// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Unequal.hpp"

using Alice::Operator::Unequal;
using Alice::Operator::ReturnUnequal;

struct Meters
{
    double value;
};

constexpr bool operator!=(Meters const& lhs, Meters const& rhs)
{
    return lhs.value not_eq rhs.value;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ----------------------------------------------------------------------
    // Built-in types: `!=` is provided by the language itself.
    // ----------------------------------------------------------------------

    static_assert(Unequal<int, int>);
    static_assert(Unequal<int, double>);
    static_assert(Unequal<int*, int*>);
    static_assert(Unequal<int*, decltype(nullptr)>);
    static_assert(not Unequal<int*, double*>); // unrelated pointer types: no viable `!=`
    static_assert(ReturnUnequal<int, int>);          // default Return == bool
    static_assert(ReturnUnequal<int, int, bool>);
    static_assert(not ReturnUnequal<int, int, int>); // `int != int` yields bool, not int

    // ----------------------------------------------------------------------
    // A type with no comparison operators at all: the baseline negative case.
    // ----------------------------------------------------------------------

    struct Uncomparable
    {
        int value;
    };

    static_assert(not Unequal<Uncomparable, Uncomparable>);
    static_assert(not ReturnUnequal<Uncomparable, Uncomparable>);

    // ----------------------------------------------------------------------
    // Ordinary member `operator!=`, returning bool.
    // ----------------------------------------------------------------------
    struct Point
    {
        int x, y;

        constexpr bool operator!=(Point const& other) const
        {
            return x not_eq other.x or y not_eq other.y;
        }
    };

    static_assert(Unequal<Point, Point>);
    static_assert(ReturnUnequal<Point, Point>);
    static_assert(ReturnUnequal<Point, Point, bool>);
    static_assert(not ReturnUnequal<Point, Point, int>);

    // ----------------------------------------------------------------------
    // Free-function `operator!=`.
    // ----------------------------------------------------------------------

    static_assert(Unequal<Meters, Meters>);
    static_assert(ReturnUnequal<Meters, Meters, bool>);

    // ----------------------------------------------------------------------
    // Heterogeneous comparison: the overload only goes in one direction, and
    // the concept must respect that direction (Self != Rhs is not Rhs != Self).
    // ----------------------------------------------------------------------
    
    struct Feet
    {
        double value;
    };

    struct Kilograms
    {
        double value;

        constexpr bool operator!=(Feet const&) const
        {
            return true;
        }
    };

    static_assert(Unequal<Kilograms, Feet>);
    static_assert(not Unequal<Feet, Kilograms>); // no `operator!=` taking a Kilograms

    // ----------------------------------------------------------------------
    // Implicit conversions must be honored, exactly as in ordinary overload
    // resolution: Rhs need not be identical to the operator's parameter type.
    // ----------------------------------------------------------------------
    
    struct Wrapped
    {
        constexpr Wrapped(int){}

        constexpr bool operator!=(Wrapped const&) const
        {
            return true;
        }
    };

    static_assert(Unequal<Wrapped, int>); // int converts to Wrapped

    // ----------------------------------------------------------------------
    // Const-correctness: Self's qualifiers must reach the operator lookup.
    // ----------------------------------------------------------------------

    struct ConstQualified
    {
        constexpr bool operator!=(ConstQualified const&) const
        {
            return true;
        }
    };

    static_assert(Unequal<ConstQualified const&, ConstQualified const&>);
    static_assert(Unequal<ConstQualified&, ConstQualified const&>);

    struct NonConstOnly
    {
        bool operator!=(NonConstOnly const&)
        {
            return true;
        }
    };

    static_assert(Unequal<NonConstOnly&, NonConstOnly const&>);
    static_assert(not Unequal<NonConstOnly const&, NonConstOnly const&>); // can't call a non-const method on a const object

    // ----------------------------------------------------------------------
    // Ref-qualified operators: this is what $forward inside the concept is
    // actually for. Self given as a value type (e.g. `RvalueOnly`) must be
    // forwarded as an rvalue, matching how a forwarding-reference template
    // parameter deduces `Self = RvalueOnly` for an rvalue argument. Self
    // given as `T&` must stay an lvalue.
    // ----------------------------------------------------------------------

    struct RvalueOnly
    {
        bool operator!=(RvalueOnly const&) &&
        {
            return true;
        } // only callable on an rvalue *this
    };

    static_assert(Unequal<RvalueOnly, RvalueOnly>);        // Self by value -> forwarded as rvalue: OK
    static_assert(not Unequal<RvalueOnly&, RvalueOnly>);   // Self as lvalue ref -> stays an lvalue: rejected

    struct LvalueOnly
    {
        bool operator!=(LvalueOnly const&) &
        {
            return true;
        } // only callable on an lvalue *this
    };

    static_assert(Unequal<LvalueOnly&, LvalueOnly>);       // Self as lvalue ref: OK
    static_assert(not Unequal<LvalueOnly, LvalueOnly>);    // Self by value -> forwarded as rvalue: rejected

    // ----------------------------------------------------------------------
    // A deleted `operator!=` must be treated the same as a missing one.
    // ----------------------------------------------------------------------
    
    struct Deleted
    {
        bool operator!=(Deleted const&) const = delete;
    };

    static_assert(not Unequal<Deleted, Deleted>);
    static_assert(not ReturnUnequal<Deleted, Deleted>);

    // ----------------------------------------------------------------------
    // ReturnUnequal must check the return type exactly, not merely that it
    // converts to Return. A type that only converts to bool must fail
    // against Return = bool, yet still satisfy Unequal (which never looks
    // at the return type at all).
    // ----------------------------------------------------------------------
    
    struct ConvertibleToBoolOnly
    {
        struct BoolLike
        {
            constexpr operator bool() const
            {
                return true;
            }
        };

        constexpr BoolLike operator!=(ConvertibleToBoolOnly const&) const
        {
            return {};
        }
    };

    static_assert(Unequal<ConvertibleToBoolOnly, ConvertibleToBoolOnly>);
    static_assert(not ReturnUnequal<ConvertibleToBoolOnly, ConvertibleToBoolOnly, bool>);
    static_assert(ReturnUnequal<ConvertibleToBoolOnly, ConvertibleToBoolOnly, ConvertibleToBoolOnly
    ::BoolLike>);

    // ----------------------------------------------------------------------
    // A fully custom, non-bool Return type used consistently by both concepts.
    // ----------------------------------------------------------------------
    
    struct Tag
    {
        int code;
    };

    struct CustomReturn
    {
        constexpr Tag operator!=(CustomReturn const&) const
        {
            return Tag{1};
        }
    };

    static_assert(Unequal<CustomReturn, CustomReturn>);
    static_assert(not ReturnUnequal<CustomReturn, CustomReturn>); // default Return = bool does not match Tag
    static_assert(ReturnUnequal<CustomReturn, CustomReturn, Tag>);

    struct Incomplete;
    return not Unequal<Incomplete, Incomplete> and not ReturnUnequal<Incomplete, Incomplete>;
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