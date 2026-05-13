// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Trait/LvalueReference.hpp"
#include "Trait/RvalueReference.hpp"
#include "Core/Move.hpp"

using Alice::Trait::Same;
using Alice::Trait::LvalueReference;
using Alice::Trait::RvalueReference;

// ── Runtime assertion (no stdlib; non-zero number signals failure) ──────

#define ASSERT(cond) do { if (not(cond)) return 1; } while(false)

// ─────────────────────────────────────────────────────────────────────────────
// Section 1 – Static (compile-time) type-category tests
// ─────────────────────────────────────────────────────────────────────────────

// 1a. Plain lvalue → T&&

static void StaticTest_PlainLvalue()
{
    int x = 0;
    
    static_assert(Same<decltype($move(x)), int&&>, "$move on a plain lvalue must yield T&&");
}

// 1b. Lvalue reference → T&& (the lvalue-ref must be stripped)

static void StaticTest_LvalueRef()
{
    int x = 0;
    
    int& ref = x;
    
    static_assert(Same<decltype($move(ref)), int&&>,
    "$move on an lvalue reference must yield T&&, not T&&&");
}

// 1c. const lvalue → const T&&

static void StaticTest_ConstLvalue()
{
    const int cx = 0;

    static_assert(Same<decltype($move(cx)), const int&&>,
    "$move on a const lvalue must yield const T&&");
}

// 1d. const lvalue reference → const T&&

static void StaticTest_ConstLvalueRef()
{
    int x = 0;

    const int& cref = x;

    static_assert(Same<decltype($move(cref)), const int&&>,
    "$move on a const lvalue reference must yield const T&&");
}

// 1e. Result is always an rvalue reference, never an lvalue reference

static void StaticTest_IsRvalueNotLvalue()
{
    int x = 0;
    
    static_assert(RvalueReference<decltype($move(x))>, "$move result must be an rvalue reference");
    static_assert(not LvalueReference<decltype($move(x))>,
    "$move result must not be an lvalue reference");
}

// 1f. Works on user-defined struct types

struct Trivial
{
    int a, b;
};

static void StaticTest_StructType()
{
    Trivial s{};

    static_assert(Same<decltype($move(s)), Trivial&&>,
    "$move on a struct lvalue must yield Struct&&");
}

// ─────────────────────────────────────────────────────────────────────────────
// Section 2 – Runtime behavioural tests
// ─────────────────────────────────────────────────────────────────────────────

// --- 2a. Trivial value is forwarded correctly --------------------------------

static int Test_TrivialValueIsPreserved()
{
    int x = 42, y = $move(x);   // trivially copied from rvalue; value must survive
    
    ASSERT(y == 42);

    return 0;
}

// --- 2b. Move constructor is invoked (not copy) via $move -------------------

struct MoveTracker
{
    int Value;

    bool MoveConstructed, CopyConstructed;

    explicit MoveTracker(int v) : Value(v), MoveConstructed(false), CopyConstructed(false){}

    MoveTracker(MoveTracker&& other) noexcept : Value(other.Value), MoveConstructed(true),
    CopyConstructed(false)
    {
        other.Value = -1; // sentinel: source was drained
    }

    // Explicitly deleted so any accidental copy is a hard compile error.
    MoveTracker(const MoveTracker&) = delete;
    
    MoveTracker& operator=(const MoveTracker&) = delete;
    
    MoveTracker& operator=(MoveTracker&&) = default;
};

static int Test_MoveConstructorIsInvoked()
{
    MoveTracker src(7), dst($move(src));

    ASSERT(dst.MoveConstructed);        // move ctor ran

    ASSERT(!dst.CopyConstructed);       // copy ctor did not run

    ASSERT(dst.Value == 7);             // value was transferred

    ASSERT(src.Value == -1);            // source was drained (sentinel)

    return 0;
}

// --- 2c. Move assignment is invoked via $move --------------------------------

static int Test_MoveAssignmentIsInvoked()
{
    MoveTracker src(99), dst(0);

    dst = $move(src);

    ASSERT(dst.Value == 99);

    ASSERT(src.Value == -1);            // source was drained

    return 0;
}

// --- 2d. $move on a reference variable strips the ref correctly at runtime --

static int Test_MoveOnReferenceVariable()
{
    int original = 55;

    int& ref = original;

    // decltype($move(ref)) must be int&&, not int&&&.
    // We verify the value reaches the destination correctly.
    int moved = $move(ref);

    ASSERT(moved == 55);

    return 0;
}

// --- 2e. Repeated $move of a trivial value is safe --------------------------

static int Test_RepeatedMoveOfTrivial()
{
    int x = 3, a = $move(x), b = $move(x); // trivial: second move is still valid

    ASSERT(a == 3);

    ASSERT(b == 3);

    return 0;
}

// --- 2f. $move inside a function argument (expression context) --------------

static int Sink(MoveTracker&& t)
{
    return t.Value;
}

static int Test_MoveInArgumentExpression()
{
    MoveTracker obj(21);

    int result = Sink($move(obj));

    ASSERT(result == 21);

    return 0;
}

// Instantiate all static tests so the compiler checks them.
static void (*const StaticTests[])() =
{
    StaticTest_PlainLvalue,
    StaticTest_LvalueRef,
    StaticTest_ConstLvalue,
    StaticTest_ConstLvalueRef,
    StaticTest_IsRvalueNotLvalue,
    StaticTest_StructType,
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Static tests are checked at translation; no runtime call needed.
    (void)StaticTests;

    // Runtime tests: return the failing number on any assertion failure,
    // or 0 (CTest "pass") when all assertions hold.

    if(Test_TrivialValueIsPreserved())
        return false;
    if(Test_MoveConstructorIsInvoked())
        return false;
    if(Test_MoveAssignmentIsInvoked())
        return false;
    if(Test_MoveOnReferenceVariable())
        return false;
    if(Test_RepeatedMoveOfTrivial())
        return false;
    if(Test_MoveInArgumentExpression())
        return false;

    return true;
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