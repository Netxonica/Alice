// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/SubtractionAssignment.hpp"

using Alice::Operator::SubtractionAssignment;
using Alice::Operator::ReturnSubtractionAssignment;

// A non-member operator-=, only reachable through ADL.

struct FreeFunctionOperand{};

struct FreeFunctionSelf
{
    int value = 0;
};

FreeFunctionSelf& operator-=(FreeFunctionSelf& self, FreeFunctionOperand)
{
    return self;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // The conventional shape: a member operator-= returning Self&.

    struct Counter
    {
        int value = 0;

        Counter& operator-=(int rhs)
        {
            value -= rhs;
            return *this;
        }

        Counter& operator-=(const Counter& rhs)
        {
            value -= rhs.value;
            return *this;
        }
    };

    // Only accepts an rvalue Rhs; the lvalue overload is deleted, so this
    // type only compiles cleanly if $forward genuinely forwards as an rvalue.

    struct MoveOnlyRhs
    {
        MoveOnlyRhs& operator-=(MoveOnlyRhs&&)
        {
            return *this;
        }

        MoveOnlyRhs& operator-=(const MoveOnlyRhs&) = delete;
    };

    // The mirror image of MoveOnlyRhs: only accepts an lvalue Rhs.

    struct LvalueOnlyRhs
    {
        LvalueOnlyRhs& operator-=(LvalueOnlyRhs&)
        {
            return *this;
        }

        LvalueOnlyRhs& operator-=(LvalueOnlyRhs&&) = delete;
    };

    // operator-= exists but does not return anything chainable.

    struct NoChainReturn
    {
        int value = 0;

        void operator-=(int rhs)
        {
            value -= rhs;
        }
    };

    // operator-= exists and returns a bespoke, non-reference type.

    struct BoolReturn
    {
        int value = 0;

        bool operator-=(int rhs)
        {
            value -= rhs;
            return value == 0;
        }
    };

    // operator-= returns Self by value instead of by reference.

    struct ValueReturn
    {
        int value = 0;

        ValueReturn operator-=(int rhs)
        {
            value -= rhs;
            return *this;
        }
    };

    // operator-= returns Self by const reference instead of by reference.

    struct ConstReturn
    {
        int value = 0;

        const ConstReturn& operator-=(int rhs)
        {
            value -= rhs;
            return *this;
        }
    };

    // No operator-= whatsoever.

    struct NotSubtractAssignable
    {
        int value = 0;
    };

    // Only operator- is defined; must never be confused with operator-=.

    struct OnlyBinaryMinus
    {
        int value = 0;

        OnlyBinaryMinus operator-(const OnlyBinaryMinus& rhs) const
        {
            return OnlyBinaryMinus{value - rhs.value};
        }
    };

    // =====================================================================
    // SubtractAssignment: is `self -= $forward(rhs)` well-formed at all?
    // =====================================================================

    // -- fundamental types ---------------------------------------------------

    static_assert(SubtractionAssignment<int, int>,
    "int -= int is built into the language and must be detected");
    static_assert(SubtractionAssignment<double, int>,
    "int converts to double, so double -= int must be detected");
    static_assert(SubtractionAssignment<int, const int>,
    "a const Rhs only needs to be read, so this must be detected too");
    static_assert(SubtractionAssignment<int*, int>,
    "pointer -= integral is ordinary pointer arithmetic");
    static_assert(not SubtractionAssignment<int*, int*>,
    "there is no built-in pointer -= pointer, only pointer - pointer");

    // -- ordinary class types -------------------------------------------------

    static_assert(SubtractionAssignment<Counter, int>, "Counter declares operator-=(int)");
    static_assert(SubtractionAssignment<Counter, Counter>,
    "Counter declares operator-=(const Counter&)");
    static_assert(SubtractionAssignment<Counter, const Counter&>,
    "an explicit lvalue-reference Rhs must be recognized too");

    // -- a free-function operator-= found via ADL -----------------------------
    
    static_assert(SubtractionAssignment<FreeFunctionSelf, FreeFunctionOperand>,
    "a non-member operator-= must satisfy the concept just as well");

    // -- SubtractAssignment must not care what operator-= returns -------------

    static_assert(SubtractionAssignment<NoChainReturn, int>,
    "existence of operator-= is all that matters here");
    static_assert(SubtractionAssignment<BoolReturn, int>,
    "existence of operator-= is all that matters here");

    // -- $forward must preserve the value category Rhs stands for ------------
    
    static_assert(SubtractionAssignment<MoveOnlyRhs, MoveOnlyRhs>,
    "a by-value Rhs must be forwarded as an rvalue");
    static_assert(not SubtractionAssignment<MoveOnlyRhs, const MoveOnlyRhs&>,
    "the lvalue overload is deleted, so a lvalue-reference Rhs must fail");
    static_assert(SubtractionAssignment<LvalueOnlyRhs, LvalueOnlyRhs&>,
    "an explicit lvalue-reference Rhs must be forwarded as an lvalue");
    static_assert(not SubtractionAssignment<LvalueOnlyRhs, LvalueOnlyRhs>,
    "the rvalue overload is deleted, so a by-value Rhs must fail");

    // -- the expression is simply ill-formed ----------------------------------

    static_assert(not SubtractionAssignment<NotSubtractAssignable, int>,
    "a type with no operator-= at all must not satisfy the concept");
    static_assert(not SubtractionAssignment<OnlyBinaryMinus, OnlyBinaryMinus>,
    "operator- must never be mistaken for operator-=");
    static_assert(not SubtractionAssignment<int, Counter>,
    "int has no operator-= that accepts a Counter");

    // -- a const Self cannot be the target of a mutating operator -------------
    
    static_assert(not SubtractionAssignment<const int, int>,
    "a const object cannot be modified by operator-=");
    static_assert(not SubtractionAssignment<const Counter, int>,
    "a const object cannot be modified by operator-=");

    // =====================================================================
    // ReturnSubtractAssignment: same question, but decltype((self -= rhs))
    // must also be Trait::Same as Return, which defaults to Self&.
    // =====================================================================

    // -- the conventional idiom returns exactly Self& -------------------------
    
    static_assert(ReturnSubtractionAssignment<Counter, int>,
    "Counter::operator-=(int) returns Counter&, the default Return");
    static_assert(ReturnSubtractionAssignment<Counter, Counter>,
    "Counter::operator-=(const Counter&) returns Counter&, the default Return");
    static_assert(ReturnSubtractionAssignment<FreeFunctionSelf, FreeFunctionOperand>,
    "the free-function overload also returns FreeFunctionSelf&");

    // -- confirm the default Return argument really is exactly Self& ----------

    static_assert(ReturnSubtractionAssignment<Counter, int> == ReturnSubtractionAssignment<Counter,
    int, Counter&>, "omitting Return must behave identically to requesting Self& explicitly");

    // -- an explicit Return matches non-conventional signatures ----------------

    static_assert(ReturnSubtractionAssignment<NoChainReturn, int, void>,
    "NoChainReturn::operator-= genuinely returns void");
    static_assert(ReturnSubtractionAssignment<BoolReturn, int, bool>,
    "BoolReturn::operator-= genuinely returns bool");
    static_assert(ReturnSubtractionAssignment<ValueReturn, int, ValueReturn>,
    "ValueReturn::operator-= genuinely returns Self by value");
    static_assert(ReturnSubtractionAssignment<ConstReturn, int, const ConstReturn&>,
    "ConstReturn::operator-= genuinely returns const Self&");

    // -- a mismatched Return must fail even though SubtractAssignment holds ----

    static_assert(not ReturnSubtractionAssignment<NoChainReturn, int>,
    "the default Return is Self&, but this overload returns void");
    static_assert(not ReturnSubtractionAssignment<BoolReturn, int>,
    "the default Return is Self&, but this overload returns bool");
    static_assert(not ReturnSubtractionAssignment<ValueReturn, int>,
    "a by-value Self is not Trait::Same as Self&");
    static_assert(not ReturnSubtractionAssignment<ConstReturn, int>,
    "a const Self& is not Trait::Same as a non-const Self&");

    // -- if SubtractAssignment cannot hold, neither can ReturnSubtractAssignment
    
    static_assert(not ReturnSubtractionAssignment<NotSubtractAssignable, int>,
    "no operator-= exists at all, so no Return could ever match");
    static_assert(not ReturnSubtractionAssignment<NotSubtractAssignable, int, void>,
    "no operator-= exists at all, so no Return could ever match");

    struct Incomplete;
    return not SubtractionAssignment<Incomplete, Incomplete> and not ReturnSubtractionAssignment<
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