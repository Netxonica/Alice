// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/ShiftLeftAssignment.hpp"

using Alice::Operator::ShiftLeftAssignment;
using Alice::Operator::ReturnShiftLeftAssignment;

// A free function operator<<= must satisfy both concepts exactly as
// well as a member one does.

struct FreeFunctionTarget
{
    int value = 0;
};

FreeFunctionTarget& operator<<=(FreeFunctionTarget& self, int rhs)
{
    self.value <<= rhs;
    return self;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------
    // Fixtures
    // ---------------------------------------------------------------

    // Conventional, well behaved type: member operator<<=, returns Self&.

    struct Conventional
    {
        int value = 0;

        Conventional& operator<<=(int rhs)
        {
            value <<= rhs;
            return *this;
        }
    };

    // No operator<<= whatsoever.

    struct NoOperator{};

    // operator<<= exists, but only for an unrelated type with no
    // conversion path to or from int.

    struct Incompatible{};

    struct OnlyAcceptsIncompatible
    {
        OnlyAcceptsIncompatible& operator<<=(Incompatible)
        {
            return *this;
        }
    };

    // operator<<= exists but returns something other than Self&, to
    // exercise ReturnShiftLeftAssignment's Return parameter.

    struct ReturnsByValue
    {
        ReturnsByValue operator<<=(int)
        {
            return *this;
        }
    };

    struct ReturnsVoid
    {
        void operator<<=(int){}
    };

    struct ReturnsBool
    {
        bool operator<<=(int)
        {
            return true;
        }
    };

    // These only accept one specific value category of int, so they probe
    // whether $forward is applied faithfully rather than always producing
    // an lvalue, or always producing an rvalue.

    struct OnlyRvalueRhs
    {
        OnlyRvalueRhs& operator<<=(int&&)
        {
            return *this;
        }
    };

    struct OnlyLvalueRhs
    {
        OnlyLvalueRhs& operator<<=(int&)
        {
            return *this;
        }
    };

    struct OnlyConstLvalueRhs
    {
        OnlyConstLvalueRhs& operator<<=(const int&)
        {
            return *this;
        }
    };

    // -------------------------------------------------------------------
    // ShiftLeftAssignment
    // -------------------------------------------------------------------

    // Built in integral types already have a compound shift-left-assignment
    // operator, with no user defined type involved at all.

    static_assert(ShiftLeftAssignment<int, int>);
    static_assert(not ShiftLeftAssignment<const int, int>);

    // Shift operators are only defined for integral (and unscoped enumeration)
    // types, so a floating point Self must not satisfy the concept.

    static_assert(not ShiftLeftAssignment<double, int>);

    // Ordinary member operator.

    static_assert(ShiftLeftAssignment<Conventional, int>);

    // No operator present at all.

    static_assert(not ShiftLeftAssignment<NoOperator, int>);

    // Argument type mismatch with no conversion available.

    static_assert(ShiftLeftAssignment<OnlyAcceptsIncompatible, Incompatible>);
    static_assert(not ShiftLeftAssignment<OnlyAcceptsIncompatible, int>);

    // The basic concept only cares that the expression is well formed, never
    // what it returns.

    static_assert(ShiftLeftAssignment<ReturnsByValue, int>);
    static_assert(ShiftLeftAssignment<ReturnsVoid, int>);
    static_assert(ShiftLeftAssignment<ReturnsBool, int>);

    // A free function operator<<= satisfies the concept exactly like a member
    // one does.

    static_assert(ShiftLeftAssignment<FreeFunctionTarget, int>);

    // Value category of Rhs must be forwarded, not collapsed to one case: an
    // operator that only accepts an rvalue must reject a genuine lvalue Rhs,
    // and vice versa.

    static_assert(ShiftLeftAssignment<OnlyRvalueRhs, int>);
    static_assert(ShiftLeftAssignment<OnlyRvalueRhs, int&&>);
    static_assert(not ShiftLeftAssignment<OnlyRvalueRhs, int&>);
    static_assert(ShiftLeftAssignment<OnlyLvalueRhs, int&>);
    static_assert(not ShiftLeftAssignment<OnlyLvalueRhs, int>);
    static_assert(not ShiftLeftAssignment<OnlyLvalueRhs, int&&>);
    static_assert(ShiftLeftAssignment<OnlyConstLvalueRhs, int>);
    static_assert(ShiftLeftAssignment<OnlyConstLvalueRhs, int&>);
    static_assert(ShiftLeftAssignment<OnlyConstLvalueRhs, const int&>);

    // -------------------------------------------------------------------
    // ReturnShiftLeftAssignment
    // -------------------------------------------------------------------

    // Default Return is Self&, matching the conventional "return *this;" idiom.

    static_assert(ReturnShiftLeftAssignment<Conventional, int>);
    static_assert(ReturnShiftLeftAssignment<Conventional, int, Conventional&>);
    static_assert(not ReturnShiftLeftAssignment<Conventional, int, Conventional>);

    // No operator<<= at all can't satisfy this either, regardless of Return.

    static_assert(not ReturnShiftLeftAssignment<NoOperator, int>);

    // An Rhs the operator can't accept fails the same way it does for
    // ShiftLeftAssignment, independent of Return.

    static_assert(not ReturnShiftLeftAssignment<OnlyAcceptsIncompatible, int>);

    // The default Return only matches Self&; every other return type needs to
    // be spelled out explicitly.

    static_assert(not ReturnShiftLeftAssignment<ReturnsByValue, int>);
    static_assert(ReturnShiftLeftAssignment<ReturnsByValue, int, ReturnsByValue>);
    static_assert(not ReturnShiftLeftAssignment<ReturnsVoid, int>);
    static_assert(ReturnShiftLeftAssignment<ReturnsVoid, int, void>);
    static_assert(not ReturnShiftLeftAssignment<ReturnsBool, int>);
    static_assert(ReturnShiftLeftAssignment<ReturnsBool, int, bool>);

    // Free function operators are checked identically to member ones.

    static_assert(ReturnShiftLeftAssignment<FreeFunctionTarget, int>);

    // Structural invariant between the two concepts: satisfying
    // ReturnShiftLeftAssignment for some Return always implies satisfying the
    // weaker ShiftLeftAssignment for the same Self and Rhs.

    static_assert(not ReturnShiftLeftAssignment<Conventional, int> or ShiftLeftAssignment<
    Conventional, int>);
    static_assert(not ReturnShiftLeftAssignment<ReturnsByValue, int, ReturnsByValue> or
    ShiftLeftAssignment<ReturnsByValue, int>);
    static_assert(not ReturnShiftLeftAssignment<FreeFunctionTarget, int> or ShiftLeftAssignment<
    FreeFunctionTarget, int>);

    struct Incomplete;
    return not ShiftLeftAssignment<Incomplete, Incomplete> and not ReturnShiftLeftAssignment<
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