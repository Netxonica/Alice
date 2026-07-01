// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Equal.hpp"

using Alice::Operator::Equal;
using Alice::Operator::ReturnEqual;

struct FreeFunctionEqual{};

bool operator==(FreeFunctionEqual const&, FreeFunctionEqual const&)
{
    return true;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // -----------------------------------------------------------------
    // Fixtures
    // -----------------------------------------------------------------

    struct BoolEqual
    {
        bool operator==(BoolEqual const&) const;
    };

    struct NoEqual{};

    struct IntComparable
    {
        bool operator==(int) const;
    };

    struct MoveOnly
    {
        MoveOnly() = default;

        MoveOnly(MoveOnly const&) = delete;

        MoveOnly(MoveOnly&&) = default;

        bool operator==(MoveOnly const&) const;
    };

    struct Tag{};

    struct TagEqual
    {
        Tag operator==(TagEqual const&) const;
    };

    struct IntEqual
    {
        int operator==(IntEqual const&) const;
    };

    // -----------------------------------------------------------------
    // Equal: only cares whether `self == rhs` is well-formed.
    // -----------------------------------------------------------------

    static_assert(Equal<BoolEqual, BoolEqual>, "a type comparable to itself satisfies Equal");
    static_assert(Equal<int, int>, "fundamental types are comparable to themselves");
    static_assert(Equal<IntComparable, int>,
    "heterogeneous comparison is accepted when operator== accepts Rhs");
    static_assert(Equal<int, IntComparable>,
    "C++20 rewrites int == IntComparable via IntComparable's reversed operator==, so the "
    "heterogeneous concept holds in either argument order even though it is only implemented once")
    ;
    static_assert(Equal<FreeFunctionEqual, FreeFunctionEqual>,
    "a free operator== found by ADL satisfies Equal just as well as a member overload");
    static_assert(Equal<MoveOnly, MoveOnly>,
    "requires-expressions never construct their parameters, so Equal does not require Self/Rhs to "
    "be copyable");
    static_assert(Equal<TagEqual, TagEqual>,
    "Equal does not care what operator== returns, only that it exists");
    static_assert(Equal<IntEqual, IntEqual>,
    "Equal does not care what operator== returns, only that it exists");
    static_assert(not Equal<NoEqual, NoEqual>, "a type with no operator== cannot satisfy Equal");
    static_assert(not Equal<IntComparable, IntComparable>,
    "IntComparable never compares against its own type, and there is no implicit conversion to int"
    " that would make one available");
    static_assert(not Equal<BoolEqual, int>,
    "BoolEqual's operator== does not accept int, and no reversed candidate exists either");

    // -----------------------------------------------------------------
    // ReturnEqual: Equal, plus an exact-match return type check.
    // -----------------------------------------------------------------

    // Default Return argument (bool).

    static_assert(ReturnEqual<BoolEqual, BoolEqual>,
    "operator== returning bool satisfies the default Return = bool");
    static_assert(ReturnEqual<int, int>, "built-in == on int returns bool");
    static_assert(ReturnEqual<IntComparable, int>, "the heterogeneous overload also returns bool");
    static_assert(ReturnEqual<int, IntComparable>,
    "the reversed, rewritten form still returns bool");
    static_assert(ReturnEqual<MoveOnly, MoveOnly>,
    "ReturnEqual, like Equal, never needs to copy Self or Rhs");
    static_assert(not ReturnEqual<NoEqual, NoEqual>,
    "no operator== at all cannot satisfy ReturnEqual");
    static_assert(not ReturnEqual<NoEqual, NoEqual, Tag>,
    "...regardless of which Return is requested");
    static_assert(not ReturnEqual<TagEqual, TagEqual>,
    "operator== returning Tag does not satisfy the default Return = bool");
    static_assert(not ReturnEqual<IntEqual, IntEqual>,
    "operator== returning int does not satisfy Return = bool even though int converts to bool: "
    "Trait::Same demands an exact match");

    // Explicit Return argument.
    
    static_assert(ReturnEqual<TagEqual, TagEqual, Tag>,
    "supplying the actual return type as Return is satisfied");
    static_assert(ReturnEqual<IntEqual, IntEqual, int>,
    "supplying the actual return type as Return is satisfied");
    static_assert(not ReturnEqual<TagEqual, TagEqual, bool>,
    "an explicit Return still demands an exact match, not just convertibility");
    static_assert(not ReturnEqual<IntEqual, IntEqual, bool>,
    "an explicit Return still demands an exact match, not just convertibility");
    
    struct Incomplete;
    return not Equal<Incomplete, Incomplete> and not ReturnEqual<Incomplete, Incomplete>;
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