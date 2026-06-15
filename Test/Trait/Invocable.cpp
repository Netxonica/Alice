// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Invocable.hpp"

using Alice::Trait::Invocable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─────────────────────────────────────────────────────────────────────────────
    // Fixtures  (no standard library, no third-party code)
    // ─────────────────────────────────────────────────────────────────────────────

    // Opaque, convertible-to-nothing types eliminate implicit-conversion
    // false-positives in negative tests.
    struct Opaque{};

    struct Other{};

    struct Third{};

    // A plain non-callable struct.

    struct NotCallable
    {
        int value;
    };

    // ── Zero-argument callables ──────────────────────────────────────────────────

    struct ReturnVoid
    {
        auto operator()() -> void{}
    };

    struct ReturnInt
    {
        auto operator()() -> int
        {
            return 0;
        }
    };

    struct ReturnIntConst
    {
        auto operator()() const -> int
        {
            return 0;
        }
    };

    // Non-const only: operator() is NOT callable on a const object.

    struct ReturnIntMutable
    {
        auto operator()() -> int
        {
            return 0;
        }
        // Deliberately no const overload.
    };

    // ── Single-argument callables ────────────────────────────────────────────────

    struct TakesIntRetFloat
    {
        auto operator()(int) -> float
        {
            return 0.f;
        }
    };

    // Custom types make argument-type mismatches impossible to hide behind
    // implicit numeric conversions.

    struct TakesOpaqueRetOther
    {
        auto operator()(Opaque) -> Other
        {
            return {};
        }
    };

    // ── Two-argument callable ────────────────────────────────────────────────────

    struct TakesTwoRetChar
    {
        auto operator()(int, bool) -> char
        {
            return '\0';
        }
    };

    // ── Reference return ─────────────────────────────────────────────────────────

    struct ReturnIntRef
    {
        int value{};

        auto operator()() -> int&
        {
            return value;
        }
    };

    // ── Overloaded operator() ────────────────────────────────────────────────────

    struct Overloaded
    {
        auto operator()(int) -> int
        {
            return 0;
        }

        auto operator()(float) -> float
        {
            return 0.f;
        }
    };

    // ── Lvalue-ref-qualified operator() ─────────────────────────────────────────
    // Only callable on lvalues; exercises the $forward(self) value-category path.

    struct LvalueOnly
    {
        auto operator()() & -> int
        {
            return 0;
        }
    };

    // ── Callable with a default argument ────────────────────────────────────────

    struct DefaultArg
    {
        auto operator()(int x = 0) -> int
        {
            return x;
        }
    };


    // ─────────────────────────────────────────────────────────────────────────────
    // POSITIVE  —  concept must be satisfied
    // ─────────────────────────────────────────────────────────────────────────────

    // Basic zero-argument callables.

    static_assert(Invocable<ReturnVoid, void>);
    static_assert(Invocable<ReturnInt, int>);
    static_assert(Invocable<ReturnIntConst, int>);

    // Const-qualified Self (lvalue ref to const) works with a const operator().

    static_assert(Invocable<const ReturnIntConst&, int>);

    // Single-argument callables.

    static_assert(Invocable<TakesIntRetFloat, float, int>);
    static_assert(Invocable<TakesOpaqueRetOther, Other, Opaque>);

    // Two-argument callable.

    static_assert(Invocable<TakesTwoRetChar, char, int, bool>);

    // Overloaded operator(): each overload is individually reachable.
    
    static_assert(Invocable<Overloaded, int, int>);
    static_assert(Invocable<Overloaded, float, float>);

    // Reference return: exact type must match (int& ≠ int).
 
    static_assert(Invocable<ReturnIntRef, int&>); // Self forwarded as rvalue
    static_assert(Invocable<ReturnIntRef&, int&>); // Self forwarded as lvalue ref

    // Lvalue-ref-qualified operator() is reachable when Self is an lvalue ref.

    static_assert(Invocable<LvalueOnly&, int>);

    // Default argument: callable with zero or one explicit argument.

    static_assert(Invocable<DefaultArg, int>); // uses default
    static_assert(Invocable<DefaultArg, int, int>); // supplies explicit arg

    // Function pointers.

    static_assert(Invocable<void(*)(), void>);
    static_assert(Invocable<int(*)(), int>);
    static_assert(Invocable<float(*)(int), float, int>);
    static_assert(Invocable<char(*)(int, bool), char, int, bool>);

    // Lambdas in unevaluated context (permitted since C++20).

    static_assert(Invocable<decltype([]() -> int
    {
        return 0;
    }), int>);
    static_assert(Invocable<decltype([](Opaque) -> Other
    {
        return {};
    }), Other, Opaque>);

    // ─────────────────────────────────────────────────────────────────────────────
    // NEGATIVE  —  concept must NOT be satisfied
    // ─────────────────────────────────────────────────────────────────────────────

    // ── Types that are not callable at all ──────────────────────────────────────

    static_assert(not Invocable<NotCallable, int>);
    static_assert(not Invocable<int, int>);
    static_assert(not Invocable<void*, void>);

    // ── Return-type mismatches ───────────────────────────────────────────────────

    static_assert(not Invocable<ReturnInt, float>); // returns int, not float
    static_assert(not Invocable<ReturnVoid, int>); // returns void, not int
    static_assert(not Invocable<TakesIntRetFloat, int, int>); // returns float, not int

    // Custom-type mismatch: Other ≠ Opaque, no conversion exists.

    static_assert(not Invocable<TakesOpaqueRetOther, Opaque, Opaque>);

    // ── Reference / value precision ──────────────────────────────────────────────
    // operator() returns int&; int& and int are distinct types under Same<>.

    static_assert(not Invocable<ReturnIntRef, int>);
    static_assert(not Invocable<ReturnIntRef&, int>);

    // ── Argument-count mismatches ────────────────────────────────────────────────

    static_assert(not Invocable<ReturnInt, int, int>); // takes 0, given 1
    static_assert(not Invocable<TakesTwoRetChar, char, int>); // takes 2, given 1
    static_assert(not Invocable<TakesTwoRetChar, char>); // takes 2, given 0

    // ── Argument-type mismatches ─────────────────────────────────────────────────
    // Custom types rule out silent implicit conversions.

    static_assert(not Invocable<TakesOpaqueRetOther, Other, Other>); // arg Other, expects Opaque
    static_assert(not Invocable<TakesOpaqueRetOther, Other, Third>); // arg Third, expects Opaque

    // ── const-correctness ────────────────────────────────────────────────────────
    // Non-const operator() cannot be called through a const-qualified Self.

    static_assert(not Invocable<const ReturnIntMutable, int>);
    static_assert(not Invocable<const ReturnIntMutable&, int>);

    // ── Lvalue-ref-qualified operator() cannot be called on an rvalue Self ───────
    // $forward(self) yields Self&&; lvalue-only operator() rejects that.

    static_assert(not Invocable<LvalueOnly, int>);

    // ── Overloaded: no overload produces the requested return type ───────────────
    // Overloaded(float arg) resolves to operator()(float)->float, not ->int.

    static_assert(not Invocable<Overloaded, int, float>);
    
    struct Incomplete;
    return not Invocable<Incomplete, Incomplete>;
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