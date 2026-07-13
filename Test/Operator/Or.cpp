// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Or.hpp"

using Alice::Operator::Or;
using Alice::Operator::ReturnOr;

// Ordinary value-semantic type: operator| is a hidden friend taking and
// returning by const reference/value, so it is callable regardless of
// self/rhs's value category or const-ness.

struct Plain
{
    friend Plain operator|(Plain const&, Plain const&)
    {
        return Plain{};
    }
};

// operator| only accepts an `int` on the right-hand side.

struct OnlyWithInt
{
    friend OnlyWithInt operator|(OnlyWithInt const&, int)
    {
        return OnlyWithInt{};
    }
};

// ---- Fixtures used by the ReturnOr tests -------------------------------

// operator| returns Self by value, satisfying ReturnOr's default Return.

struct ReturnsSelf
{
    friend ReturnsSelf operator|(ReturnsSelf const&, ReturnsSelf const&)
    {
        return ReturnsSelf{};
    }
};

// operator| exists (so Or is satisfied) but returns something other
// than Self (so ReturnOr's default Return is not satisfied).

struct ReturnsBool
{
    friend bool operator|(ReturnsBool const&, ReturnsBool const&)
    {
        return true;
    }
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---- Fixtures used by the Or tests -------------------------------------

    // Has no operator| at all.

    struct NoOperator{};

    // Member operator|, `&`-qualified: only callable when self is an lvalue.
    
    struct LvalueOnly
    {
        LvalueOnly operator|(LvalueOnly const&) &
        {
            return LvalueOnly{};
        }
    };

    // Member operator|, `&&`-qualified: only callable when self is an rvalue.

    struct RvalueOnly
    {
        RvalueOnly operator|(RvalueOnly const&) &&
        {
            return RvalueOnly{};
        }
    };

    // Member operator|, no ref-qualifier but not const: callable on lvalues
    // and rvalues alike, just never on a const self.

    struct NonConstOnly
    {
        NonConstOnly operator|(NonConstOnly const&)
        {
            return NonConstOnly{};
        }
    };

    // A conventional operator| is satisfied no matter which value category or
    // const-ness Self/Rhs are instantiated with, because $forward can only ever
    // produce something that still binds to `Plain const&`.

    static_assert(Or<Plain, Plain>, "by-value self/rhs must satisfy Or");
    static_assert(Or<Plain&, Plain>, "lvalue self must satisfy Or");
    static_assert(Or<Plain const&, Plain>, "const lvalue self must satisfy Or");
    static_assert(Or<Plain, Plain&>, "lvalue rhs must satisfy Or");

    // No operator| at all can never satisfy Or.

    static_assert(not Or<NoOperator, NoOperator>, "a type with no operator| must not satisfy Or");

    // Or is specific to the requested Rhs.

    static_assert(Or<OnlyWithInt, int>, "operator|(int) must satisfy Or<Self, int>");
    static_assert(not Or<OnlyWithInt, OnlyWithInt>,
    "operator| for int must not satisfy Or<Self, Self>");
    static_assert(not Or<Plain, int>, "Plain has no operator|(int)");

    // Or must respect the value category implied by Self, exactly as an
    // ordinary forwarding-reference call would.
    
    static_assert(Or<LvalueOnly&, LvalueOnly>,
    "'&'-qualified operator| is callable on an lvalue self");
    static_assert(not Or<LvalueOnly, LvalueOnly>,
    "'&'-qualified operator| is not callable on an rvalue self");
    static_assert(Or<RvalueOnly, RvalueOnly>,
    "'&&'-qualified operator| is callable on an rvalue self");
    static_assert(not Or<RvalueOnly&, RvalueOnly>,
    "'&&'-qualified operator| is not callable on an lvalue self");

    // Or must respect const-ness implied by Self. Note a non-const,
    // non-ref-qualified member is still callable on an rvalue -- only a const
    // self should be rejected here.

    static_assert(Or<NonConstOnly, NonConstOnly>,
    "non-const operator| is callable on a non-const rvalue self");
    static_assert(not Or<NonConstOnly const&, NonConstOnly>,
    "non-const operator| is not callable on a const self");

    // ---------------------------------------------------------------------------
    // Alice::Operator::ReturnOr
    // ---------------------------------------------------------------------------

    // Default Return argument (Self) is satisfied when operator| returns Self.
    
    static_assert(ReturnOr<ReturnsSelf, ReturnsSelf>,
    "operator| returning Self must satisfy the default Return");

    // Or ignores the return type entirely; ReturnOr does not.
    
    static_assert(Or<ReturnsBool, ReturnsBool>, "operator| exists regardless of its return type");
    static_assert(not ReturnOr<ReturnsBool, ReturnsBool>,
    "operator| returning bool must not satisfy ReturnOr<Self, Rhs, Self>");
    static_assert(ReturnOr<ReturnsBool, ReturnsBool, bool>,
    "operator| returning bool must satisfy ReturnOr<Self, Rhs, bool>");

    // No operator| at all can never satisfy ReturnOr either.

    static_assert(not ReturnOr<NoOperator, NoOperator>,
    "a type with no operator| must not satisfy ReturnOr");

    // ReturnOr inherits Or's sensitivity to value category: the underlying
    // `self bitor rhs` expression must still compile, whatever Return is asked
    // for.
    
    static_assert(not ReturnOr<LvalueOnly, LvalueOnly, LvalueOnly>,
    "an rvalue self must fail ReturnOr just as it fails Or");
    static_assert(ReturnOr<LvalueOnly&, LvalueOnly, LvalueOnly>,
    "an lvalue self satisfies ReturnOr once Return is given explicitly");

    // Gotcha worth pinning down: the default `Return = Self` reuses Self
    // exactly as written, reference-ness included. operator| returns LvalueOnly
    // by value, so once Self itself is a reference type the default no longer
    // matches -- Return must be given explicitly, as above.

    static_assert(not ReturnOr<LvalueOnly&, LvalueOnly>,
    "default Return becomes 'LvalueOnly&', which the by-value return can't match");

    struct Incomplete;
    return not Or<Incomplete, Incomplete> and not ReturnOr<Incomplete, Incomplete>;
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