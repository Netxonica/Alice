// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/LogicalNot.hpp"

using Alice::Operator::LogicalNot;
using Alice::Operator::ReturnLogicalNot;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Test types ────────────────────────────────────────────────────────────────

    struct WithBoolReturn
    {
        bool operator!() const
        {
            return true;
        }
    };

    struct WithIntReturn
    {
        int operator!() const
        {
            return 0;
        }
    };

    struct CustomReturnType{};

    struct WithCustomReturn
    {
        CustomReturnType operator!() const
        {
            return {};
        }
    };

    struct WithVoidReturn
    {
        void operator!() const{}
    };

    struct WithNoOperator{};

    // ── LogicalNot ────────────────────────────────────────────────────────────────

    // Any operator! overload satisfies LogicalNot, regardless of return type.

    static_assert(LogicalNot<WithBoolReturn>);
    static_assert(LogicalNot<WithIntReturn>);
    static_assert(LogicalNot<WithCustomReturn>);
    static_assert(LogicalNot<WithVoidReturn>);

    // Built-in types with language-level logical negation also satisfy LogicalNot.

    static_assert(LogicalNot<bool>);
    static_assert(LogicalNot<int>);

    // A type with no operator! does not satisfy LogicalNot.

    static_assert(not LogicalNot<WithNoOperator>);

    // ── ReturnLogicalNot ──────────────────────────────────────────────────────────

    // operator! returning bool satisfies both the default and explicit bool forms.

    static_assert(ReturnLogicalNot<WithBoolReturn>);
    static_assert(ReturnLogicalNot<WithBoolReturn, bool>);

    // operator! returning int fails the default (bool) form but passes with int.

    static_assert(not ReturnLogicalNot<WithIntReturn>);
    static_assert(ReturnLogicalNot<WithIntReturn, int>);

    // operator! returning a user-defined type fails the default form but passes
    // when the expected return type is specified explicitly.

    static_assert(not ReturnLogicalNot<WithCustomReturn>);
    static_assert(ReturnLogicalNot<WithCustomReturn, CustomReturnType>);

    // operator! returning void fails the default (bool) form but passes for void.

    static_assert(not ReturnLogicalNot<WithVoidReturn>);
    static_assert(ReturnLogicalNot<WithVoidReturn, void>);

    // A type with no operator! fails all forms.

    static_assert(not ReturnLogicalNot<WithNoOperator>);
    static_assert(not ReturnLogicalNot<WithNoOperator, bool>);

    // Built-in bool: ! returns bool, so the default and explicit bool forms pass.
    // Specifying a mismatched type (int) fails.

    static_assert(ReturnLogicalNot<bool>);
    static_assert(ReturnLogicalNot<bool, bool>);
    static_assert(not ReturnLogicalNot<bool, int>);

    // Built-in int: ! also returns bool via standard arithmetic conversion, so the
    // same pattern holds. Asking for int fails because the expression yields bool.
    
    static_assert(ReturnLogicalNot<int>);
    static_assert(ReturnLogicalNot<int, bool>);
    static_assert(not ReturnLogicalNot<int, int>);

    struct Incomplete;
    return not LogicalNot<Incomplete> and not ReturnLogicalNot<Incomplete>;
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