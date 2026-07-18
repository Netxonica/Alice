// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/ShiftRightAssignment.hpp"

using Alice::Operator::ShiftRightAssignment;
using Alice::Operator::ReturnShiftRightAssignment;

// Same shape, but as a free function: the concept must not care
// whether operator>>= is a member or found via ADL.

struct FreeFunctionTarget{};

auto operator>>=(FreeFunctionTarget& self, int) -> FreeFunctionTarget&
{
    return self;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // An opaque marker type with no conversion to or from anything else.
    // Used as a Rhs that must never accidentally satisfy an unrelated
    // operator through an implicit conversion.
    
    struct Tag{};

    // -----------------------------------------------------------------
    // No operator>>= at all: neither concept can be satisfied, for any
    // Rhs.
    // -----------------------------------------------------------------

    struct NoOperator{};

    static_assert(not ShiftRightAssignment<NoOperator, int>,
    "a type with no operator>>= must not satisfy ShiftRightAssignment");
    static_assert(not ShiftRightAssignment<NoOperator, Tag>,
    "a type with no operator>>= must not satisfy ShiftRightAssignment");
    static_assert(not ReturnShiftRightAssignment<NoOperator, int>,
    "a type with no operator>>= must not satisfy ReturnShiftRightAssignment");

    // -----------------------------------------------------------------
    // The textbook shape, `Self& operator>>=(Rhs)`, as a member function.
    // -----------------------------------------------------------------

    struct Canonical
    {
        auto operator>>=(int) -> Canonical&;
    };

    static_assert(ShiftRightAssignment<Canonical, int>,
    "a member operator>>=(int) must satisfy ShiftRightAssignment<Canonical, int>");
    static_assert(ReturnShiftRightAssignment<Canonical, int>,
    "returning Canonical& must satisfy the default Return = Self&");
    static_assert(ReturnShiftRightAssignment<Canonical, int, Canonical&>,
    "Return can also be spelled out explicitly, with the same result");
    static_assert(ShiftRightAssignment<FreeFunctionTarget, int>,
    "a free operator>>= found via ADL must also satisfy ShiftRightAssignment");
    static_assert(ReturnShiftRightAssignment<FreeFunctionTarget, int>,
    "a free operator>>= found via ADL must also satisfy ReturnShiftRightAssignment");

    // An unrelated Rhs, with no conversion to int, must not satisfy
    // either fixture's operator.

    static_assert(not ShiftRightAssignment<Canonical, Tag>,
    "Tag has no conversion to int, so the call is ill-formed");
    static_assert(not ShiftRightAssignment<FreeFunctionTarget, Tag>,
    "Tag has no conversion to int, so the call is ill-formed");

    // -----------------------------------------------------------------
    // ShiftRightAssignment does not care what operator>>= returns.
    // ReturnShiftRightAssignment does, and defaults to expecting Self&.
    // -----------------------------------------------------------------
    
    struct VoidReturn
    {
        auto operator>>=(int) -> void;
    };

    static_assert(ShiftRightAssignment<VoidReturn, int>,
    "the return type is irrelevant to ShiftRightAssignment");
    static_assert(not ReturnShiftRightAssignment<VoidReturn, int>,
    "void does not match the default Return = Self&");
    static_assert(ReturnShiftRightAssignment<VoidReturn, int, void>,
    "void does match once Return is corrected to void");

    struct ByValueReturn
    {
        auto operator>>=(int) -> ByValueReturn;
    };

    static_assert(ShiftRightAssignment<ByValueReturn, int>,
    "the return type is irrelevant to ShiftRightAssignment");
    static_assert(not ReturnShiftRightAssignment<ByValueReturn, int>,
    "a by-value return is a prvalue ByValueReturn, not the default Return = Self&");
    static_assert(ReturnShiftRightAssignment<ByValueReturn, int, ByValueReturn>,
    "a by-value return matches Return = Self with no reference");
    static_assert(not ReturnShiftRightAssignment<ByValueReturn, int, ByValueReturn&>,
    "a prvalue result must not satisfy a reference Return");

    // -----------------------------------------------------------------
    // `self >>= $forward(rhs)` forwards the value category of Rhs, so the
    // concept must distinguish overloads that only bind rvalues, only
    // bind mutable lvalues, or (via const&) accept anything.
    // -----------------------------------------------------------------

    struct RvalueOnly
    {
        auto operator>>=(Tag&&) -> RvalueOnly&;
    };

    static_assert(ShiftRightAssignment<RvalueOnly, Tag>,
    "Rhs = Tag is forwarded as an rvalue, which binds to Tag&&");
    static_assert(not ShiftRightAssignment<RvalueOnly, Tag&>,
    "Rhs = Tag& is forwarded as an lvalue, which cannot bind to Tag&&");
    static_assert(not ShiftRightAssignment<RvalueOnly, const Tag&>,
    "Rhs = const Tag& is forwarded as a const lvalue, which cannot bind to Tag&&");

    struct LvalueOnly
    {
        auto operator>>=(Tag&) -> LvalueOnly&;
    };

    static_assert(ShiftRightAssignment<LvalueOnly, Tag&>,
    "Rhs = Tag& is forwarded as an lvalue, which binds to Tag&");
    static_assert(not ShiftRightAssignment<LvalueOnly, Tag>,
    "Rhs = Tag is forwarded as an rvalue, which cannot bind to Tag&");
    static_assert(not ShiftRightAssignment<LvalueOnly, const Tag&>,
    "Rhs = const Tag& is forwarded as const, which cannot bind to mutable Tag&");

    struct ConstLvalue
    {
        auto operator>>=(const Tag&) -> ConstLvalue&;
    };

    static_assert(ShiftRightAssignment<ConstLvalue, Tag>, "const Tag& binds to a forwarded rvalue")
    ;
    static_assert(ShiftRightAssignment<ConstLvalue, Tag&>,
    "const Tag& binds to a forwarded mutable lvalue");
    static_assert(ShiftRightAssignment<ConstLvalue, const Tag&>,
    "const Tag& binds to a forwarded const lvalue");

    // Return-type checking composes with these forwarding-sensitive
    // overloads: the call must be well-formed before Return is even
    // considered.

    static_assert(ReturnShiftRightAssignment<RvalueOnly, Tag, RvalueOnly&>,
    "well-formed call, and it returns RvalueOnly& as expected");
    static_assert(not ReturnShiftRightAssignment<RvalueOnly, Tag&, RvalueOnly&>,
    "the call itself is ill-formed here, regardless of Return");

    // -----------------------------------------------------------------
    // An operator that exists but can never be *selected* by overload
    // resolution, because it is deleted or inaccessible, must not
    // satisfy the concept either.
    // -----------------------------------------------------------------

    struct DeletedOperator
    {
        auto operator>>=(int) -> DeletedOperator& = delete;
    };

    static_assert(not ShiftRightAssignment<DeletedOperator, int>,
    "overload resolution would select a deleted function");

    class PrivateOperator
    {
    private:
        auto operator>>=(int) -> PrivateOperator&;
    };

    static_assert(not ShiftRightAssignment<PrivateOperator, int>,
    "overload resolution would select an inaccessible function");

    // -----------------------------------------------------------------
    // A const object is not a modifiable lvalue, so it cannot be the
    // left-hand operand of a compound assignment, regardless of Self.
    // -----------------------------------------------------------------

    static_assert(not ShiftRightAssignment<const Canonical, int>,
    "operator>>= is not const-qualified, so a const Self cannot call it");
    static_assert(not ShiftRightAssignment<const int, int>,
    "a const object is not a modifiable lvalue");

    // -----------------------------------------------------------------
    // Fundamental types get operator>>= from the core language itself.
    // `int i; i >>= 1;` yields an lvalue of type int, i.e. decltype((..))
    // is int&.
    // -----------------------------------------------------------------
    
    static_assert(ShiftRightAssignment<int, int>, "built-in integral types support >>= directly");
    static_assert(not ShiftRightAssignment<int, Tag>, "Tag has no conversion to int");
    static_assert(ReturnShiftRightAssignment<int, int, int&>,
    "built-in compound assignment yields an lvalue of the left operand's type");
    static_assert(not ReturnShiftRightAssignment<int, int, int>,
    "the result is int&, not a prvalue int");

    struct Incomplete;
    return not ShiftRightAssignment<Incomplete, Incomplete> and not ReturnShiftRightAssignment<
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