// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/PostIncrement.hpp"

using Alice::Operator::PostIncrement;
using Alice::Operator::ReturnPostIncrement;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Types that DO provide post-increment ──────────────────────────────

    struct Simple
    {
        Simple operator++(int)
        {
            return *this;
        }
    };

    struct WithBothIncrements
    {
        WithBothIncrements& operator++()
        {
            return *this;
        }

        WithBothIncrements operator++(int)
        {
            return *this;
        }
    };

    struct AltReturn{};

    struct ReturnsAlt
    {
        AltReturn operator++(int)
        {
            return {};
        }
    };

    // ── Types that do NOT provide post-increment ──────────────────────────

    struct PreIncrementOnly
    {
        PreIncrementOnly& operator++()
        {
            return *this;
        }
    };

    struct NoOperators{};

    struct DeletedPostIncrement
    {
        DeletedPostIncrement operator++(int) = delete;
    };

    // ── PostIncrement: positive ───────────────────────────────────────────────

    static_assert(PostIncrement<Simple>, "A type with operator++(int) must satisfy PostIncrement");
    static_assert(PostIncrement<WithBothIncrements>,
    "A type with both pre- and post-increment must satisfy PostIncrement");
    static_assert(PostIncrement<ReturnsAlt>,
    "PostIncrement must not constrain the return type of operator++(int)");

    // ── PostIncrement: negative ───────────────────────────────────────────────

    static_assert(not PostIncrement<PreIncrementOnly>,
    "A type with only pre-increment must not satisfy PostIncrement");
    static_assert(not PostIncrement<NoOperators>,
    "A type with no increment operators must not satisfy PostIncrement");
    static_assert(not PostIncrement<DeletedPostIncrement>,
    "A type with a deleted operator++(int) must not satisfy PostIncrement");

    // ── ReturnPostIncrement: positive ─────────────────────────────────────────

    static_assert(ReturnPostIncrement<Simple>,
    "Simple::operator++(int) returns Simple; must satisfy ReturnPostIncrement<Simple>");
    static_assert(ReturnPostIncrement<WithBothIncrements>,
    "WithBothIncrements::operator++(int) returns Self; must satisfy ReturnPostIncrement<"
    "WithBothIncrements>");
    static_assert(ReturnPostIncrement<ReturnsAlt, AltReturn>,
    "ReturnsAlt::operator++(int) returns AltReturn; must satisfy ReturnPostIncrement<ReturnsAlt, "
    "AltReturn>");

    // ── ReturnPostIncrement: negative (no post-increment at all) ─────────────

    static_assert(not ReturnPostIncrement<PreIncrementOnly>,
    "A type with only pre-increment must not satisfy ReturnPostIncrement");
    static_assert(not ReturnPostIncrement<NoOperators>,
    "A type with no operators must not satisfy ReturnPostIncrement");
    static_assert(not ReturnPostIncrement<DeletedPostIncrement>,
    "A type with a deleted operator++(int) must not satisfy ReturnPostIncrement");

    // ── ReturnPostIncrement: negative (return type mismatch) ─────────────────

    static_assert(not ReturnPostIncrement<ReturnsAlt>,
    "ReturnsAlt returns AltReturn, not ReturnsAlt; must not satisfy ReturnPostIncrement<ReturnsAlt"
    ">");
    static_assert(not ReturnPostIncrement<Simple, AltReturn>,
    "Simple returns Simple, not AltReturn; must not satisfy ReturnPostIncrement<Simple, AltReturn>"
    );
    static_assert(not ReturnPostIncrement<ReturnsAlt, Simple>,
    "ReturnsAlt returns AltReturn, not Simple; must not satisfy ReturnPostIncrement<ReturnsAlt, "
    "Simple>");

    struct Incomplete;
    return not PostIncrement<Incomplete> and not ReturnPostIncrement<Incomplete>;
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