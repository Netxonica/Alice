// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/PreIncrement.hpp"

using Alice::Operator::PreIncrement;
using Alice::Operator::ReturnPreIncrement;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─────────────────────────────────────────────────────────────
    // Test fixtures
    // ─────────────────────────────────────────────────────────────

    struct NotIncrementable{};

    /// No ref-qualifier: operator++ is callable on both lvalues and rvalues.

    struct Incrementable
    {
        Incrementable& operator++()
        {
            return *this;
        }
    };

    /// &-qualified: operator++ is callable only on lvalues.

    struct LvalueIncrementable
    {
        LvalueIncrementable& operator++() &
        {
            return *this;
        }
    };

    /// &&-qualified: operator++ is callable only on rvalues.

    struct RvalueIncrementable
    {
        RvalueIncrementable operator++() &&
        {
            return {};
        }
    };

    /// const-qualified, no ref-qualifier: callable regardless of constness.

    struct ConstIncrementable
    {
        const ConstIncrementable& operator++() const
        {
            return *this;
        }
    };

    /// operator++ returning int (a prvalue) instead of Self&.

    struct IntReturnIncrementable
    {
        int operator++()
        {
            return 0;
        }
    };

    // ─────────────────────────────────────────────────────────────
    // PreIncrement — built-in arithmetic types
    // ─────────────────────────────────────────────────────────────

    // Value-type Self → forwarded as rvalue; built-in ++rvalue is ill-formed.

    static_assert(not PreIncrement<int>);
    static_assert(not PreIncrement<int&&>);
    static_assert(not PreIncrement<float>);

    // Lvalue-reference Self → forwarded as lvalue; ++lvalue is well-formed.

    static_assert(PreIncrement<int&>);
    static_assert(PreIncrement<float&>);

    // const lvalue reference → cannot modify through const.

    static_assert(not PreIncrement<const int&>);

    // ─────────────────────────────────────────────────────────────
    // PreIncrement — pointer types
    // ─────────────────────────────────────────────────────────────

    // Pointer rvalue (value type) cannot be pre-incremented.

    static_assert(not PreIncrement<int*>);

    // Pointer lvalue reference can be pre-incremented.
    
    static_assert(PreIncrement<int*&>);

    // ─────────────────────────────────────────────────────────────
    // PreIncrement — user-defined types
    // ─────────────────────────────────────────────────────────────

    // No operator++: never satisfied, regardless of ref-qualification.
    
    static_assert(not PreIncrement<NotIncrementable>);
    static_assert(not PreIncrement<NotIncrementable&>);

    // Unqualified operator++: value (rvalue) form and lvalue-ref form both work.
    
    static_assert(PreIncrement<Incrementable>);
    static_assert(PreIncrement<Incrementable&>);
    
    // Non-const operator++ cannot be called through a const lvalue.
    
    static_assert(not PreIncrement<const Incrementable&>);

    // &-qualified operator++: only the lvalue-ref form satisfies the concept.

    static_assert(not PreIncrement<LvalueIncrementable>);
    static_assert(PreIncrement<LvalueIncrementable&>);

    // &&-qualified operator++: only the value (rvalue) form satisfies the concept.
    
    static_assert(PreIncrement<RvalueIncrementable>);
    static_assert(not PreIncrement<RvalueIncrementable&>);

    // const operator++ with no ref-qualifier: all cv/ref combinations work.
    
    static_assert(PreIncrement<ConstIncrementable>);
    static_assert(PreIncrement<ConstIncrementable&>);
    static_assert(PreIncrement<const ConstIncrementable&>);

    // PreIncrement imposes no constraint on the return type.

    static_assert(PreIncrement<IntReturnIncrementable>);

    // ─────────────────────────────────────────────────────────────
    // ReturnPreIncrement — built-in arithmetic types
    // ─────────────────────────────────────────────────────────────

    // Default Return = (int&)& = int&; ++int_lvalue is a lvalue of type int → int&.

    static_assert(ReturnPreIncrement<int&>);

    // Explicit return-type matching.

    static_assert(ReturnPreIncrement<int&, int&>);

    // int& is an lvalue, not a prvalue, xvalue, wider type, or const-qualified type.
    
    static_assert(not ReturnPreIncrement<int&, int>);
    static_assert(not ReturnPreIncrement<int&, int&&>);
    static_assert(not ReturnPreIncrement<int&, const int&>);
    static_assert(not ReturnPreIncrement<int&, long&>);

    // When pre-increment itself is ill-formed, ReturnPreIncrement is always false.
    
    static_assert(not ReturnPreIncrement<int>);
    static_assert(not ReturnPreIncrement<int, int&>);

    // ─────────────────────────────────────────────────────────────
    // ReturnPreIncrement — user-defined types
    // ─────────────────────────────────────────────────────────────

    // Incrementable::operator++() returns Incrementable& → matches the default Return.
    
    static_assert(ReturnPreIncrement<Incrementable>);
    static_assert(ReturnPreIncrement<Incrementable&>);
    static_assert(ReturnPreIncrement<Incrementable&, Incrementable&>);
    static_assert(not ReturnPreIncrement<Incrementable&, Incrementable>);
    static_assert(not ReturnPreIncrement<Incrementable&, Incrementable&&>);
    static_assert(not ReturnPreIncrement<Incrementable&, int>);

    // LvalueIncrementable: only the lvalue-ref form is valid, and it returns Self&.
    
    static_assert(not ReturnPreIncrement<LvalueIncrementable>);
    static_assert(ReturnPreIncrement<LvalueIncrementable&>);
    static_assert(not ReturnPreIncrement<LvalueIncrementable&, LvalueIncrementable>);

    // RvalueIncrementable::operator++() && returns RvalueIncrementable (prvalue).
    // Default Return = RvalueIncrementable& — does not match a prvalue.
    
    static_assert(not ReturnPreIncrement<RvalueIncrementable>);
    
    // Specifying the exact prvalue type as Return matches.
    
    static_assert(ReturnPreIncrement<RvalueIncrementable, RvalueIncrementable>);
    
    // &&-qualified operator++ cannot be called on a lvalue → always false.
    
    static_assert(not ReturnPreIncrement<RvalueIncrementable&>);

    // IntReturnIncrementable::operator++() returns int (prvalue).
    // Default Return = IntReturnIncrementable& — mismatch.
    
    static_assert(not ReturnPreIncrement<IntReturnIncrementable>);
    static_assert(not ReturnPreIncrement<IntReturnIncrementable&>);
    
    // Explicitly specifying int matches the actual prvalue return type.
    
    static_assert(ReturnPreIncrement<IntReturnIncrementable, int>);
    static_assert(ReturnPreIncrement<IntReturnIncrementable&, int>);
    
    struct Incomplete;
    return not PreIncrement<Incomplete> and not ReturnPreIncrement<Incomplete>;
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