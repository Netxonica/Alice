// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/AddAssignment.hpp"

using Alice::Operator::AddAssignment;
using Alice::Operator::ReturnAddAssignment;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ------------------------------------------------------------------
    // Fixture types
    // ------------------------------------------------------------------

    // Canonical shape: operator+= takes Rhs by value and returns Self&,
    // exactly matching ReturnAddAssignment's default Return argument.

    struct Canonical
    {
        Canonical& operator+=(int)
        {
            return *this;
        }
    };

    // No operator+= at all.

    struct Missing{};

    // Unrelated to everything below: no implicit conversion in or out.

    struct Incompatible{};

    // operator+= exists, but only for a type int cannot convert to.

    struct WrongRhs
    {
        struct Tag{};

        WrongRhs& operator+=(Tag)
        {
            return *this;
        }
    };

    // operator+= takes a type that Rhs converts to implicitly, proving the
    // concept follows ordinary overload resolution rather than requiring
    // an exact match between Rhs and the parameter type.

    struct ConvertibleRhs
    {
        ConvertibleRhs& operator+=(long)
        {
            return *this;
        }
    };

    // Well formed, but the return type is void.

    struct ReturnsVoid
    {
        void operator+=(int){}
    };

    // Well formed, but returns by value instead of by reference.

    struct ReturnsByValue
    {
        ReturnsByValue operator+=(int)
        {
            return *this;
        }
    };

    // Returns an arbitrary, unrelated type, to be paired with an explicit
    // Return argument.

    struct ReturnsCustom
    {
        struct Result{};

        Result operator+=(int)
        {
            return Result{};
        }
    };

    // Move-only type used to prove that $forward genuinely preserves the
    // value category implied by Rhs instead of always yielding an lvalue.

    struct MoveOnly
    {
        MoveOnly() = default;

        MoveOnly(const MoveOnly&) = delete;

        MoveOnly& operator=(const MoveOnly&) = delete;

        MoveOnly(MoveOnly&&) = default;

        MoveOnly& operator=(MoveOnly&&) = default;
    };

    struct AcceptsRvalueRhs
    {
        AcceptsRvalueRhs& operator+=(MoveOnly&&)
        {
            return *this;
        }
    };

    struct AcceptsLvalueRhs
    {
        AcceptsLvalueRhs& operator+=(MoveOnly&)
        {
            return *this;
        }
    };

    // operator+= is a non-const member, so a const-qualified Self must fail.

    struct NonConstMember
    {
        NonConstMember& operator+=(int)
        {
            return *this;
        }
    };

    // ----------------------------------------------------------------------
    // AddAssignment
    // ----------------------------------------------------------------------

    static_assert(AddAssignment<Canonical, int>,
    "A type with a matching operator+= must satisfy AddAssignment");
    static_assert(not AddAssignment<Missing, int>,
    "A type with no operator+= at all must not satisfy AddAssignment");
    static_assert(not AddAssignment<WrongRhs, int>,
    "AddAssignment must fail when Rhs cannot be converted to any accepted parameter");
    static_assert(not AddAssignment<Canonical, Incompatible>,
    "AddAssignment must fail when Rhs has no relationship to the accepted parameter");
    static_assert(AddAssignment<ConvertibleRhs, int>,
    "AddAssignment must succeed when Rhs converts implicitly to the accepted parameter");
    static_assert(AddAssignment<ReturnsVoid, int>,
    "AddAssignment must not care about the return type of operator+=");
    static_assert(AddAssignment<ReturnsByValue, int>,
    "AddAssignment must not care whether operator+= returns by value or by reference");
    static_assert(AddAssignment<AcceptsRvalueRhs, MoveOnly>,
    "$forward must present rhs as an rvalue so an operator+=(MoveOnly&&) overload is viable");
    static_assert(not AddAssignment<AcceptsLvalueRhs, MoveOnly>,
    "$forward must present rhs as an rvalue, so an lvalue-only operator+= must be rejected");
    static_assert(not AddAssignment<const NonConstMember, int>,
    "A const-qualified Self must not satisfy AddAssignment when operator+= is a non-const member");

    // ----------------------------------------------------------------------
    // ReturnAddAssignment - default Return (Self&)
    // ----------------------------------------------------------------------

    static_assert(ReturnAddAssignment<Canonical, int>,
    "operator+= returning Self& must satisfy ReturnAddAssignment with the default Return");
    static_assert(not ReturnAddAssignment<ReturnsVoid, int>,
    "operator+= returning void must not satisfy ReturnAddAssignment with the default Return");
    static_assert(not ReturnAddAssignment<ReturnsByValue, int>,
    "operator+= returning by value must not satisfy ReturnAddAssignment with the default Return");
    static_assert(not ReturnAddAssignment<Missing, int>,
    "A missing operator+= must not satisfy ReturnAddAssignment either");

    // ----------------------------------------------------------------------
    // ReturnAddAssignment - explicit Return
    // ----------------------------------------------------------------------

    static_assert(ReturnAddAssignment<ReturnsVoid, int, void>,
    "operator+= returning void must satisfy ReturnAddAssignment<..., void>");
    static_assert(ReturnAddAssignment<ReturnsByValue, int, ReturnsByValue>,
    "operator+= returning Self by value must satisfy ReturnAddAssignment<..., Self>");
    static_assert(ReturnAddAssignment<ReturnsCustom, int, ReturnsCustom::Result>,
    "operator+= returning an arbitrary type must satisfy ReturnAddAssignment<..., ThatType>");
    static_assert(not ReturnAddAssignment<ReturnsCustom, int, int>,
    "ReturnAddAssignment must fail when Return does not exactly match operator+='s actual return "
    "type");

    struct Incomplete;
    return not AddAssignment<Incomplete, Incomplete> and not ReturnAddAssignment<Incomplete,
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