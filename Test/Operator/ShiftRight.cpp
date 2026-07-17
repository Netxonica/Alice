// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/ShiftRight.hpp"

using Alice::Operator::ShiftRight;
using Alice::Operator::ReturnShiftRight;

// A heterogeneous, stream-extraction-style pair joined only by a free
// operator>>, proving non-member overloads found via ADL count too,
// and that both argument order and Rhs type still matter.

struct Stream{};

struct Payload{};

[[maybe_unused]] Stream& operator>>(Stream& self, Payload&)
{
    return self;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // -----------------------------------------------------------------
    // Fixtures
    // -----------------------------------------------------------------

    // No operator>> whatsoever, and nothing convertible to anything that
    // would let a built-in operator>> kick in either.

    struct Empty{};

    // A plain, const-qualified member operator>>. Being const-qualified and
    // not ref-qualified, it must be reachable no matter whether Self is
    // forwarded as an lvalue, an rvalue, or const.

    struct ConstMember
    {
        ConstMember operator>>(int) const
        {
            return ConstMember{};
        }
    };

    // A non-const member operator>>. Reachable through a non-const Self,
    // but not through a const one.

    struct SelfNonConstOnly
    {
        SelfNonConstOnly operator>>(int)
        {
            return SelfNonConstOnly{};
        }
    };

    // Ref-qualified overloads, used to prove that $forward(self) really
    // preserves Self's value category instead of always binding as an
    // lvalue.

    struct SelfRvalueOnly
    {
        SelfRvalueOnly operator>>(int) &&
        {
            return SelfRvalueOnly{};
        }
    };

    struct SelfLvalueOnly
    {
        SelfLvalueOnly operator>>(int) &
        {
            return SelfLvalueOnly{};
        }
    };

    // Returns something other than Self, exercising ReturnShiftRight.

    struct ReturnsInt
    {
        int operator>>(int) const
        {
            return 0;
        }
    };

    // Only accepts an rvalue Rhs, used to prove that $forward(rhs)
    // preserves Rhs's value category too.

    struct RhsRvalueOnly
    {
        RhsRvalueOnly operator>>(int&&) const
        {
            return RhsRvalueOnly{};
        }
    };

    // -----------------------------------------------------------------
    // ShiftRight
    // -----------------------------------------------------------------

    // A type with no operator>> must never satisfy the concept.
    
    static_assert(not ShiftRight<Empty, int>,
    "a type with no operator>> must not satisfy ShiftRight");
    static_assert(not ShiftRight<Empty, Empty>,
    "an unrelated pair of empty types must not satisfy ShiftRight");

    // The built-in operator>> on integral types must be picked up; there is
    // no built-in overload for floating point operands.
    
    static_assert(ShiftRight<int, int>,
    "the built-in operator>> between ints must satisfy ShiftRight");
    static_assert(ShiftRight<unsigned, int>,
    "the built-in operator>> works across distinct integral types");
    static_assert(not ShiftRight<double, double>,
    "there is no built-in operator>> for floating point operands");

    // A basic member overload, plus Rhs sensitivity: there is no conversion
    // from Empty to int, so the call cannot be formed.
    
    static_assert(ShiftRight<ConstMember, int>, "a member operator>>(int) must satisfy ShiftRight")
    ;
    static_assert(not ShiftRight<ConstMember, Empty>,
    "Rhs must actually be usable as the call argument");

    // Self value-category sensitivity: $forward(self) must preserve
    // whether Self is an lvalue or an rvalue, since that is exactly what
    // ref-qualified overloads dispatch on.
    
    static_assert(ShiftRight<SelfRvalueOnly, int>,
    "Self forwarded as an rvalue must reach an && qualified overload");
    static_assert(not ShiftRight<SelfRvalueOnly&, int>,
    "Self forwarded as an lvalue must not reach an && qualified overload");
    static_assert(ShiftRight<SelfLvalueOnly&, int>,
    "Self forwarded as an lvalue must reach a & qualified overload");
    static_assert(not ShiftRight<SelfLvalueOnly, int>,
    "Self forwarded as an rvalue must not reach a & qualified overload");

    // Self const sensitivity: a const member is reachable everywhere, a
    // non-const one only through a non-const Self.

    static_assert(ShiftRight<const ConstMember&, int>,
    "a const member operator>> is reachable through a const lvalue Self");
    static_assert(ShiftRight<SelfNonConstOnly&, int>,
    "a non-const member operator>> is reachable through a non-const Self");
    static_assert(not ShiftRight<const SelfNonConstOnly&, int>,
    "a non-const member operator>> must not be reachable through a const Self");

    // Rhs value-category sensitivity: $forward(rhs) must equally preserve
    // whether Rhs is an lvalue or an rvalue.

    static_assert(ShiftRight<RhsRvalueOnly, int>,
    "Rhs forwarded as an rvalue must bind to an int&& parameter");
    static_assert(not ShiftRight<RhsRvalueOnly, int&>,
    "Rhs forwarded as an lvalue must not bind to an int&& parameter");

    // A free operator>> found via ADL, where both argument order and Rhs
    // type still matter.

    static_assert(ShiftRight<Stream&, Payload&>,
    "a free operator>> found via ADL must satisfy ShiftRight");
    static_assert(not ShiftRight<Payload&, Stream&>,
    "operands are not interchangeable; the declared parameter order is required");
    static_assert(not ShiftRight<Stream&, int>,
    "Rhs must match the free operator>>'s parameter, not just any type");

    // -----------------------------------------------------------------
    // ReturnShiftRight
    // -----------------------------------------------------------------

    // The built-in operator>> between ints returns int; Trait::Same
    // requires an exact type match rather than mere convertibility.

    static_assert(ReturnShiftRight<int, int>,
    "default Return equals Self, which matches the built-in int result");
    static_assert(ReturnShiftRight<int, int, int>,
    "an explicit Return matching the actual return type is satisfied");
    static_assert(not ReturnShiftRight<int, int, long>,
    "int and long are distinct types, even though int converts to long");

    // Default Return argument equals Self.

    static_assert(ReturnShiftRight<ConstMember, int>, "default Return equals Self");

    // A well-formed operator>> whose return type differs from Return must
    // fail ReturnShiftRight while still satisfying ShiftRight.

    static_assert(ShiftRight<ReturnsInt, int>, "sanity check: the operator>> itself is well-formed"
    );
    static_assert(not ReturnShiftRight<ReturnsInt, int>,
    "default Return (Self) does not match the actual int return type");
    static_assert(ReturnShiftRight<ReturnsInt, int, int>,
    "an explicit Return of int matches the actual return type");

    // A reference-returning operator>>: the default Return must track
    // Self's reference-ness exactly, not just its underlying class type.
    
    static_assert(ReturnShiftRight<Stream&, Payload&>,
    "default Return is Stream&, matching the actual Stream& result");
    static_assert(not ReturnShiftRight<Stream&, Payload&, Stream>,
    "Stream and Stream& are not the same type");

    // A Self/Rhs pair that fails ShiftRight must also fail
    // ReturnShiftRight, rather than triggering a hard error.
    
    static_assert(not ReturnShiftRight<Empty, int>,
    "an ill-formed self >> rhs must not satisfy ReturnShiftRight either");

    struct Incomplete;
    return not ShiftRight<Incomplete, Incomplete> and not ReturnShiftRight<Incomplete, Incomplete>;
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