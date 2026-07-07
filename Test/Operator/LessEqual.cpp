// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/LessEqual.hpp"

using Alice::Operator::LessEqual;
using Alice::Operator::ReturnLessEqual;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Ordinary type, comparable to itself, operator<= returns bool.

    struct Comparable
    {
        constexpr bool operator<=(Comparable const&) const noexcept
        {
            return true;
        }
    };

    // No relational operators at all.

    struct Incomparable{};

    // Comparable to `Comparable`, but not to its own type.

    struct CrossTypeComparable
    {
        constexpr bool operator<=(Comparable const&) const noexcept
        {
            return true;
        }
    };

    // operator<= exists but returns something other than bool.

    struct NonBoolComparable
    {
        constexpr int operator<=(NonBoolComparable const&) const noexcept
        {
            return 0;
        }
    };

    // operator<= is ref-qualified: only callable on rvalues.

    struct RvalueQualifiedComparable
    {
        constexpr bool operator<=(RvalueQualifiedComparable const&) && noexcept
        {
            return true;
        }
    };

    // operator<= is ref-qualified: only callable on lvalues.

    struct LvalueQualifiedComparable
    {
        constexpr bool operator<=(LvalueQualifiedComparable const&) & noexcept
        {
            return true;
        }
    };

    // ---------------------------------------------------------------------------
    // LessEqual: is `self <= rhs` well-formed, regardless of what it returns?
    // ---------------------------------------------------------------------------

    // Fundamental types.

    static_assert(LessEqual<int, int>);
    static_assert(LessEqual<int, double>);

    // A type is comparable to itself.

    static_assert(LessEqual<Comparable, Comparable>);

    // The concept doesn't care what operator<= returns.

    static_assert(LessEqual<NonBoolComparable, NonBoolComparable>);

    // Self and Rhs are legitimately allowed to differ.

    static_assert(LessEqual<CrossTypeComparable, Comparable>);

    // No operator<= at all.

    static_assert(not LessEqual<Incomparable, Incomparable>);

    // Self/Rhs pairing has no viable overload, even though *an* overload exists
    // for a different pairing. There is no implicit conversion between these
    // types, and plain operator<= is not reversed the way operator== is.

    static_assert(not LessEqual<CrossTypeComparable, CrossTypeComparable>);
    static_assert(not LessEqual<Comparable, CrossTypeComparable>);
    static_assert(not LessEqual<Incomparable, int>);

    // ---------------------------------------------------------------------------
    // LessEqual: value-category sensitivity.
    //
    // The concept forwards self/rhs instead of using them as bare lvalues, so it
    // must be sensitive to ref-qualified overloads of operator<=. This is the
    // behavior that distinguishes it from a naive `requires(Self self, Rhs rhs)
    // { self <= rhs; }`, and is worth pinning down explicitly.
    // ---------------------------------------------------------------------------

    // Self, taken by value, forwards as an rvalue: matches &&, not &.

    static_assert(LessEqual<RvalueQualifiedComparable, RvalueQualifiedComparable>);
    static_assert(not LessEqual<LvalueQualifiedComparable, LvalueQualifiedComparable>);

    // Self, taken by lvalue reference, forwards as an lvalue: the reverse.

    static_assert(not LessEqual<RvalueQualifiedComparable&, RvalueQualifiedComparable&>);
    static_assert(LessEqual<LvalueQualifiedComparable&, LvalueQualifiedComparable&>);

    // ---------------------------------------------------------------------------
    // ReturnLessEqual: LessEqual, plus an exact return-type match.
    // ---------------------------------------------------------------------------

    // Return defaults to bool.

    static_assert(ReturnLessEqual<int, int>);
    static_assert(ReturnLessEqual<Comparable, Comparable>);
    static_assert(not ReturnLessEqual<NonBoolComparable, NonBoolComparable>);

    // Explicit, non-bool Return.

    static_assert(ReturnLessEqual<NonBoolComparable, NonBoolComparable, int>);

    // No operator<= at all fails regardless of what Return is asked for.
    static_assert(not ReturnLessEqual<Incomparable, Incomparable>);
    static_assert(not ReturnLessEqual<Incomparable, Incomparable, int>);

    // Spot check: ReturnLessEqual inherits the same value-category sensitivity.

    static_assert(ReturnLessEqual<RvalueQualifiedComparable, RvalueQualifiedComparable>);
    static_assert(not ReturnLessEqual<RvalueQualifiedComparable&, RvalueQualifiedComparable&>);

    struct Incomplete;
    return not LessEqual<Incomplete, Incomplete> and not ReturnLessEqual<Incomplete, Incomplete>;
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