// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/LogicalAnd.hpp"

using Alice::Operator::LogicalAnd;
using Alice::Operator::ReturnLogicalAnd;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─────────────────────────────────────────────────────────────────────────────
    // Test helpers
    // ─────────────────────────────────────────────────────────────────────────────

    /// No conversion to bool; no operator&&.
    
    struct Opaque{};

    /// operator&& returning bool.

    struct AndBool
    {
        bool operator&&(const AndBool&) const;
    };

    /// operator&& returning int (intentionally not bool).

    struct AndInt
    {
        int operator&&(const AndInt&) const;
    };

    /// A distinct tag type returned by operator&&.

    struct Tag{};

    struct AndTag
    {
        Tag operator&&(const AndTag&) const;
    };

    /// Accepts only int on the right-hand side; returns bool.

    struct AndWithInt
    {
        bool operator&&(int) const;
    };

    /// Lvalue-ref-qualified operator&&.
    /// Cannot be called when the left operand is an rvalue, which is what
    /// $forward(self) produces when Self is a plain value type.

    struct LvalueOnlyAnd
    {
        bool operator&&(LvalueOnlyAnd&) &;
    };

    // ─────────────────────────────────────────────────────────────────────────────
    // LogicalAnd
    // ─────────────────────────────────────────────────────────────────────────────

    // Built-in types: the built-in operator&& is available.

    static_assert(LogicalAnd<bool, bool>);
    static_assert(LogicalAnd<int, int>);
    static_assert(LogicalAnd<int, bool>);
    static_assert(LogicalAnd<bool, int>);

    // Pointer types implicitly convert to bool, so the built-in && applies.

    static_assert(LogicalAnd<int*, int*>);

    // User-defined operator&& is found regardless of its return type.

    static_assert(LogicalAnd<AndBool, AndBool>);
    static_assert(LogicalAnd<AndInt, AndInt>);
    static_assert(LogicalAnd<AndTag, AndTag>);

    // Heterogeneous rhs accepted by the overload.

    static_assert(LogicalAnd<AndWithInt, int>);

    // When Self is an lvalue-reference type, $forward(self) yields an lvalue,
    // so a &-qualified operator&& becomes callable.

    static_assert(LogicalAnd<LvalueOnlyAnd&, LvalueOnlyAnd&>);

    // ── Negative ────────────────────────────────────────────────────────────────

    // No conversion to bool and no operator&&.

    static_assert(not LogicalAnd<Opaque, Opaque>);
    static_assert(not LogicalAnd<Opaque, bool>);
    static_assert(not LogicalAnd<bool, Opaque>);

    // Rhs type not accepted by the overload.

    static_assert(not LogicalAnd<AndBool, int>);
    static_assert(not LogicalAnd<AndWithInt, Opaque>);

    // $forward(self) yields an rvalue for value types; the &-qualified operator&&
    // cannot be invoked on an rvalue, so the expression is ill-formed.

    static_assert(not LogicalAnd<LvalueOnlyAnd, LvalueOnlyAnd>);

    // ─────────────────────────────────────────────────────────────────────────────
    // ReturnLogicalAnd
    // ─────────────────────────────────────────────────────────────────────────────

    // Built-in operator&& always yields bool; the default Return is bool.

    static_assert(ReturnLogicalAnd<bool, bool>);
    static_assert(ReturnLogicalAnd<bool, bool, bool>);
    static_assert(ReturnLogicalAnd<int, int>);
    static_assert(ReturnLogicalAnd<int, int, bool>);
    static_assert(ReturnLogicalAnd<int*, int*>);

    // User-defined operator&& whose return type matches the requested Return.
    
    static_assert(ReturnLogicalAnd<AndBool, AndBool, bool>);
    static_assert(ReturnLogicalAnd<AndBool, AndBool>);           // default Return = bool
    static_assert(ReturnLogicalAnd<AndInt, AndInt, int>);
    static_assert(ReturnLogicalAnd<AndTag, AndTag, Tag>);
    static_assert(ReturnLogicalAnd<AndWithInt, int>);               // returns bool; default ok
    static_assert(ReturnLogicalAnd<AndWithInt, int, bool>);

    // ── Negative ────────────────────────────────────────────────────────────────

    // Return type mismatch.

    static_assert(not ReturnLogicalAnd<AndInt, AndInt>);               // int != bool (default)
    static_assert(not ReturnLogicalAnd<AndInt, AndInt, bool>);        // returns int, not bool
    static_assert(not ReturnLogicalAnd<AndBool, AndBool, int>);         // returns bool, not int
    static_assert(not ReturnLogicalAnd<AndTag, AndTag, bool>);        // returns Tag, not bool
    static_assert(not ReturnLogicalAnd<int, int, int>);         // built-in && → bool ≠ int

    // No operator&& at all.

    static_assert(not ReturnLogicalAnd<Opaque, Opaque>);
    static_assert(not ReturnLogicalAnd<Opaque, Opaque, bool>);

    struct Incomplete;
    return not LogicalAnd<Incomplete, Incomplete> and not ReturnLogicalAnd<Incomplete, Incomplete>;
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