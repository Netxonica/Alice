// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Comma.hpp"

using Alice::Trait::Same;
using Alice::Operator::Comma;
using Alice::Operator::ReturnComma;

/// operator,(int) → Self by value; no ref-qualifier (lvalue + rvalue callable)
    
struct WithIntCommaSelf
{
    template<Same<int> T> WithIntCommaSelf operator,(T)
    {
        return {};
    }
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ==========================================================================
    // Test fixtures
    // ==========================================================================

    /// operator,(int) → int by value; no ref-qualifier

    struct WithIntCommaInt
    {
        int operator,(int)
        {
            return 0;
        }
    };

    /// operator,(int) → void

    struct WithIntCommaVoid
    {
        void operator,(int){}
    };

    /// operator,(int) → Self by value; rvalue ref-qualifier only (&&).
    /// $forward(self) yields an rvalue, so this overload is directly reachable.

    struct WithIntCommaRvSelf
    {
        WithIntCommaRvSelf operator,(int) &&
        {
            return {};
        }
    };

    /// operator,(int) → Self by value; lvalue ref-qualifier only (&).
    /// $forward(self) yields an rvalue, so this overload is UNREACHABLE in the concept;
    /// the built-in comma fires instead.

    struct WithIntCommaLvSelf
    {
        WithIntCommaLvSelf operator,(int) &
        {
            return *this;
        }
    };

    /// No user-defined operator,

    struct NoCommaOp{};

    // ==========================================================================
    // Comma<Self, Rhs>
    // ==========================================================================

    // User-defined overloads that accept Rhs are reached when the operator is callable
    // on the rvalue produced by $forward(self).

    static_assert(Comma<WithIntCommaSelf, int>);
    static_assert(Comma<WithIntCommaInt, int>);
    static_assert(Comma<WithIntCommaVoid, int>);
    static_assert(Comma<WithIntCommaRvSelf, int>);    // && overload: directly reachable via rvalue

    // The built-in comma is an unconditional fallback, so Comma is satisfied even when no
    // user-defined overload is viable.
    
    static_assert(Comma<WithIntCommaLvSelf, int>);    // & overload unreachable → built-in used
    static_assert(Comma<NoCommaOp, int>);    // no overload at all → built-in used
    static_assert(Comma<WithIntCommaSelf, double>);  // no op,(double) defined → built-in used

    // ==========================================================================
    // ReturnComma<Self, Rhs, Return = Self>
    // ==========================================================================

    // ── Positive: the called operator's return type matches Return ─────────────

    // Default Return = Self; operator,(int) returns Self
    
    static_assert(ReturnComma<WithIntCommaSelf, int>);
    static_assert(ReturnComma<WithIntCommaRvSelf, int>);

    // Explicit Return = int; operator,(int) returns int

    static_assert(ReturnComma<WithIntCommaInt, int, int>);

    // Explicit Return = void; operator,(int) returns void
    static_assert(ReturnComma<WithIntCommaVoid, int, void>);

    // ── Negative: user-defined operator return type ≠ Return ──────────────────

    // Default Return = Self, but operator returns int ≠ Self

    static_assert(not ReturnComma<WithIntCommaInt, int>);

    // Default Return = Self, but operator returns void ≠ Self

    static_assert(not ReturnComma<WithIntCommaVoid, int>);

    // Explicit Return = int, but operator returns Self ≠ int

    static_assert(not ReturnComma<WithIntCommaSelf, int, int>);

    // Explicit Return = Self type, but operator returns int ≠ Self

    static_assert(not ReturnComma<WithIntCommaInt, int, WithIntCommaInt>);

    // Explicit Return = void, but operator returns Self ≠ void

    static_assert(not ReturnComma<WithIntCommaSelf, int, void>);

    // ── Negative: lvalue-only overload unreachable via $forward (rvalue) ───────
    // Built-in comma fires instead; it returns Rhs&& (xvalue) ≠ Self (prvalue type).

    static_assert(not ReturnComma<WithIntCommaLvSelf, int>);

    // ── Negative: no user-defined operator for this Rhs type ───────────────────
    // Built-in comma fires; returns Rhs&& ≠ Self.
    static_assert(not ReturnComma<WithIntCommaSelf, double>);  // no op,(double) defined
    static_assert(not ReturnComma<NoCommaOp, int>);    // no operator, at all

    struct Incomplete;
    return Comma<Incomplete, Incomplete> and not ReturnComma<Incomplete, Incomplete>;
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