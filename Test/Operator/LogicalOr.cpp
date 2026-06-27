// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/LogicalOr.hpp"

using Alice::Operator::LogicalOr;
using Alice::Operator::ReturnLogicalOr;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Fixture types ─────────────────────────────────────────────────────────────

    struct NoOr{};                                // no operator|| whatsoever

    struct ReturnsBool
    {                           // operator|| → bool
        bool operator||(ReturnsBool) noexcept
        {
            return false;
        }
    };

    struct ReturnsInt
    {                            // operator|| → int (deliberately not bool)
        int operator||(ReturnsInt) noexcept
        {
            return 0;
        }
    };

    struct CustomTag{};

    struct ReturnsCustomTag
    {                      // operator|| → CustomTag
        CustomTag operator||(ReturnsCustomTag) noexcept
        {
            return {};
        }
    };

    struct Right{};

    struct AsymLeft
    {                              // operator|| only as (AsymLeft, Right)
        bool operator||(Right) noexcept
        {
            return false;
        }
    };

    // ── LogicalOr ─────────────────────────────────────────────────────────────────

    // Built-in arithmetic types always support ||

    static_assert(LogicalOr<bool, bool>);
    static_assert(LogicalOr<int, int>);
    static_assert(LogicalOr<bool, int>);
    static_assert(LogicalOr<int, bool>);

    // User-defined operators are detected regardless of return type

    static_assert(LogicalOr<ReturnsBool, ReturnsBool>);
    static_assert(LogicalOr<ReturnsInt, ReturnsInt>);
    static_assert(LogicalOr<ReturnsCustomTag, ReturnsCustomTag>);

    // Asymmetric pair: correct operand order satisfies; reversed does not

    static_assert(LogicalOr<AsymLeft, Right>);
    static_assert(not LogicalOr<Right, AsymLeft>);

    // Missing or mismatched operator
    
    static_assert(not LogicalOr<AsymLeft, NoOr>);
    static_assert(not LogicalOr<NoOr, NoOr>);
    static_assert(not LogicalOr<NoOr, bool>);
    static_assert(not LogicalOr<bool, NoOr>);

    // ── ReturnLogicalOr ───────────────────────────────────────────────────────────

    // Built-in || always yields bool, even for integer operands

    static_assert(ReturnLogicalOr<bool, bool>);          // default Return=bool ✓
    static_assert(ReturnLogicalOr<int, int, bool>);          // int||int → bool ✓
    static_assert(not ReturnLogicalOr<bool, bool, int>);          // bool||bool ≠ int ✗
    static_assert(not ReturnLogicalOr<int, int, int>);          // int||int ≠ int ✗

    // User type returning bool

    static_assert(ReturnLogicalOr<ReturnsBool, ReturnsBool>);   // default ✓
    static_assert(not ReturnLogicalOr<ReturnsBool, ReturnsBool, int>);   // bool ≠ int ✗

    // User type returning int — does not satisfy the default bool expectation

    static_assert(ReturnLogicalOr<ReturnsInt, ReturnsInt, int>);    // exact match ✓
    static_assert(not ReturnLogicalOr<ReturnsInt, ReturnsInt>);    // int ≠ bool ✗
    static_assert(not ReturnLogicalOr<ReturnsInt, ReturnsInt, bool>);    // int ≠ bool ✗

    // User type returning a custom tag — never matches the bool default

    static_assert(ReturnLogicalOr<ReturnsCustomTag, ReturnsCustomTag, CustomTag>);  // ✓
    static_assert(not ReturnLogicalOr<ReturnsCustomTag, ReturnsCustomTag>);  // CustomTag ≠ bool ✗
    static_assert(not ReturnLogicalOr<ReturnsCustomTag, ReturnsCustomTag, bool>);  // CustomTag ≠ bool ✗

    // Asymmetric pair: correct order works; reversed has no operator

    static_assert(ReturnLogicalOr<AsymLeft, Right>);   // returns bool, default ✓
    static_assert(not ReturnLogicalOr<AsymLeft, Right, int>);   // bool ≠ int ✗
    static_assert(not ReturnLogicalOr<Right, AsymLeft>);   // no operator ✗

    // No operator at all — both concepts must fail

    static_assert(not ReturnLogicalOr<NoOr, NoOr>);
    static_assert(not ReturnLogicalOr<NoOr, bool>);
    static_assert(not ReturnLogicalOr<bool, NoOr>);

    struct Incomplete;
    return not LogicalOr<Incomplete, Incomplete> and not ReturnLogicalOr<Incomplete, Incomplete>;
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