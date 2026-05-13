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

// ─────────────────────────────────────────────────────────────────────────────
// Section 2 – Runtime behavioural tests
// ─────────────────────────────────────────────────────────────────────────────

// --- 2a. Trivial value is forwarded correctly --------------------------------

[[nodiscard]] constexpr auto Test_TrivialValueIsPreserved() noexcept -> bool
{
    int x = 42, y = $move(x);   // trivially copied from rvalue; value must survive
    
    if(y not_eq 42)
        return false;

    return true;
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
    
    MoveTracker& operator=(MoveTracker&& other)
    {
        Value = other.Value;
        other.Value = -1;
        return *this;
    }
};

[[nodiscard]] constexpr auto Test_MoveConstructorIsInvoked() noexcept -> bool
{
    MoveTracker src(7), dst($move(src));

    if(not dst.MoveConstructed)        // move ctor ran
        return false;

    if(dst.CopyConstructed)       // copy ctor did not run
        return false;

    if(dst.Value not_eq 7)             // value was transferred
        return false;

    return src.Value == -1;            // source was drained (sentinel)
}

// --- 2c. Move assignment is invoked via $move --------------------------------

[[nodiscard]] constexpr auto Test_MoveAssignmentIsInvoked() noexcept -> bool
{
    MoveTracker src(99), dst(0);

    dst = $move(src);

    if(dst.Value not_eq 99)
        return false;

    return src.Value == -1;            // source was drained
}

// --- 2d. $move on a reference variable strips the ref correctly at runtime --

[[nodiscard]] constexpr auto Test_MoveOnReferenceVariable() noexcept -> bool
{
    int original = 55;

    int& ref = original;

    // decltype($move(ref)) must be int&&, not int&&&.
    // We verify the value reaches the destination correctly.
    int moved = $move(ref);

    return moved == 55;
}

// --- 2e. Repeated $move of a trivial value is safe --------------------------

[[nodiscard]] constexpr auto Test_RepeatedMoveOfTrivial() noexcept -> bool
{
    int x = 3, a = $move(x), b = $move(x); // trivial: second move is still valid

    return a == 3 and b == 3;
}

// --- 2f. $move inside a function argument (expression context) --------------

[[nodiscard]] constexpr auto sink(MoveTracker&& t) noexcept -> bool
{
    return t.Value == 21;
}

static int Test_MoveInArgumentExpression()
{
    MoveTracker obj(21);

    return sink($move(obj));
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─────────────────────────────────────────────────────────────────────────────
    // Section 1 – Static (compile-time) type-category tests
    // ─────────────────────────────────────────────────────────────────────────────

    // 1a. Plain lvalue → T&&
    
    {
        int x = 0;
    
        static_assert(Same<decltype($move(x)), int&&>, "$move on a plain lvalue must yield T&&");
    }

    // 1b. Lvalue reference → T&& (the lvalue-ref must be stripped)

    {
        int x = 0;
        
        int& ref = x;
        
        static_assert(Same<decltype($move(ref)), int&&>,
        "$move on an lvalue reference must yield T&&, not T&&&");
    }

    // 1c. const lvalue → const T&&

    {
        const int cx = 0;

        static_assert(Same<decltype($move(cx)), const int&&>,
        "$move on a const lvalue must yield const T&&");
    }

    // 1d. const lvalue reference → const T&&

    {
        int x = 0;

        const int& cref = x;

        static_assert(Same<decltype($move(cref)), const int&&>,
        "$move on a const lvalue reference must yield const T&&");
    }

    // 1e. Result is always an rvalue reference, never an lvalue reference

    {
        int x = 0;
    
        static_assert(RvalueReference<decltype($move(x))>,
        "$move result must be an rvalue reference");
        static_assert(not LvalueReference<decltype($move(x))>,
        "$move result must not be an lvalue reference");
    }

    // 1f. Works on user-defined struct types

    struct Trivial
    {
        int a, b;
    };

    {
        Trivial s{};

        static_assert(Same<decltype($move(s)), Trivial&&>,
        "$move on a struct lvalue must yield Struct&&");
    }

    // Runtime tests: return the failing number on any assertion failure,
    // or 0 (CTest "pass") when all assertions hold.

    return Test_TrivialValueIsPreserved() and Test_MoveConstructorIsInvoked() and
    Test_MoveAssignmentIsInvoked() and Test_MoveOnReferenceVariable() and
    Test_RepeatedMoveOfTrivial() and Test_MoveInArgumentExpression();
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