// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/AndAssignment.hpp"

using Alice::Operator::AndAssignment;
using Alice::Operator::ReturnAndAssignment;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Conventional shape: operator&= takes Self by const reference and
    // returns Self&, exactly like the built-in integer types. Used as the
    // "everything should just work" baseline, and to exercise all four
    // forwarding categories of Rhs (by value, &, const&, &&), since a
    // const&-parameter accepts every one of them.

    struct Canonical
    {
        int value{};

        constexpr Canonical& operator&=(Canonical const& rhs) noexcept
        {
            value &= rhs.value;
            return *this;
        }
    };

    // operator&= only accepts an rvalue. This proves $forward genuinely
    // forwards the value category implied by Rhs instead of always
    // producing an lvalue (or always an rvalue).

    struct RvalueOnly
    {
        int value{};

        constexpr RvalueOnly& operator&=(RvalueOnly&& rhs) noexcept
        {
            value &= rhs.value;
            return *this;
        }
    };

    // Rhs need not be Self.

    struct AcceptsInt
    {
        int value{};

        constexpr AcceptsInt& operator&=(int rhs) noexcept
        {
            value &= rhs;
            return *this;
        }
    };

    // Two overloads: satisfying the concept for either Rhs depends on
    // ordinary overload resolution happening inside the requires-expression.

    struct Overloaded
    {
        int value{};

        constexpr Overloaded& operator&=(Overloaded const& rhs) noexcept
        {
            value &= rhs.value;
            return *this;
        }

        constexpr Overloaded& operator&=(int rhs) noexcept
        {
            value &= rhs;
            return *this;
        }
    };

    // Returns void. AndAssignment doesn't look at the return type at all,
    // so it must still be satisfied; ReturnAndAssignment must reject this
    // unless Return is explicitly void.

    struct ReturnsVoid
    {
        int value{};

        constexpr void operator&=(ReturnsVoid const& rhs) noexcept
        {
            value &= rhs.value;
        }
    };

    // Returns Self by value instead of by reference. decltype((expr)) is
    // Self for a prvalue but Self& for an lvalue, so this must fail the
    // default ReturnAndAssignment<Self, Rhs> (Return defaults to Self&)
    // yet pass once Return is explicitly Self.

    struct ReturnsByValue
    {
        int value{};

        constexpr ReturnsByValue operator&=(ReturnsByValue const& rhs) noexcept
        {
            return ReturnsByValue{value & rhs.value};
        }
    };

    // Returns a type unrelated to Self entirely (a "did this change
    // anything" flag, as a fluent API might do). Exercises a fully custom
    // Return argument rather than just Self by value or by reference.

    struct ReturnsBool
    {
        int value{};

        constexpr bool operator&=(ReturnsBool const& rhs) noexcept
        {
            bool const changed = (value & rhs.value) != value;
            value &= rhs.value;
            return changed;
        }
    };

    // operator&= is const-qualified and returns a const reference. Proves
    // that ReturnAndAssignment's default Self& is an exact type match
    // rather than "close enough": Self const& is a different type to
    // Trait::Same than Self&.

    struct ConstQualified
    {
        int value{};

        constexpr ConstQualified const& operator&=(ConstQualified const&) const noexcept
        {
            return *this;
        }
    };

    // operator&= only exists on the base. Derived inherits it unchanged,
    // return type included: called through a Derived object it still
    // yields a Base&, not a Derived&, because it isn't virtual.

    struct Base
    {
        int value{};

        constexpr Base& operator&=(Base const& rhs) noexcept
        {
            value &= rhs.value;
            return *this;
        }
    };

    struct Derived : Base{};

    // No operator&= at all.

    struct NoOperator
    {
        int value{};
    };

    // operator&= exists, but only for a type with no relationship to int,
    // so there is no implicit conversion that could accidentally make the
    // requires-expression well-formed anyway.

    struct Unrelated
    {
        int value{};
    };

    struct WrongRhs
    {
        int value{};

        constexpr WrongRhs& operator&=(Unrelated const& rhs) noexcept
        {
            value &= rhs.value;
            return *this;
        }
    };

    // ---------------------------------------------------------------------------
    // AndAssignment
    // ---------------------------------------------------------------------------

    // Baseline: works for all four value categories of Rhs, since the
    // parameter is Canonical const&.

    static_assert(AndAssignment<Canonical, Canonical>);
    static_assert(AndAssignment<Canonical, Canonical&>);
    static_assert(AndAssignment<Canonical, Canonical const&>);
    static_assert(AndAssignment<Canonical, Canonical&&>);

    // $forward really forwards: an rvalue-only overload accepts an rvalue Rhs
    // and rejects an lvalue Rhs.

    static_assert(AndAssignment<RvalueOnly, RvalueOnly>);
    static_assert(AndAssignment<RvalueOnly, RvalueOnly&&>);
    static_assert(not AndAssignment<RvalueOnly, RvalueOnly&>);

    // Rhs need not be Self.

    static_assert(AndAssignment<AcceptsInt, int>);

    // Overload resolution picks whichever overload fits Rhs.

    static_assert(AndAssignment<Overloaded, Overloaded>);
    static_assert(AndAssignment<Overloaded, int>);

    // The return type is irrelevant to AndAssignment.

    static_assert(AndAssignment<ReturnsVoid, ReturnsVoid>);
    static_assert(AndAssignment<ReturnsByValue, ReturnsByValue>);
    static_assert(AndAssignment<ReturnsBool, ReturnsBool>);

    // A const-qualified operator&= is callable through a const Self; a
    // non-const one is not.

    static_assert(AndAssignment<ConstQualified, ConstQualified>);
    static_assert(AndAssignment<ConstQualified const, ConstQualified>);
    static_assert(not AndAssignment<Canonical const, Canonical>);

    // Inherited operators are visible through the derived type, and
    // derived-to-base conversions apply to Rhs too.

    static_assert(AndAssignment<Derived, Base>);
    static_assert(AndAssignment<Derived, Derived>);

    // Fundamental types satisfy the concept through the built-in &=, since
    // the concept only checks that the expression is well-formed.

    static_assert(AndAssignment<int, int>);

    // No operator, and no viable conversion to a type that has one.

    static_assert(not AndAssignment<NoOperator, NoOperator>);
    static_assert(not AndAssignment<WrongRhs, int>);
    static_assert(not AndAssignment<int, Canonical>);

    // ---------------------------------------------------------------------------
    // ReturnAndAssignment
    // ---------------------------------------------------------------------------

    // Default Return is Self&, matching the common case.

    static_assert(ReturnAndAssignment<Canonical, Canonical>);
    static_assert(ReturnAndAssignment<Canonical, Canonical, Canonical&>);
    static_assert(ReturnAndAssignment<AcceptsInt, int>);
    static_assert(ReturnAndAssignment<Overloaded, Overloaded>);
    static_assert(ReturnAndAssignment<Overloaded, int>);
    static_assert(ReturnAndAssignment<int, int>);

    // void is a legitimate Return when that's genuinely what's returned.

    static_assert(not ReturnAndAssignment<ReturnsVoid, ReturnsVoid>);
    static_assert(ReturnAndAssignment<ReturnsVoid, ReturnsVoid, void>);

    // By-value vs. by-reference returns are different types as far as
    // Trait::Same is concerned.

    static_assert(not ReturnAndAssignment<ReturnsByValue, ReturnsByValue>);
    static_assert(ReturnAndAssignment<ReturnsByValue, ReturnsByValue, ReturnsByValue>);

    // An arbitrary Return works as long as it matches exactly.

    static_assert(not ReturnAndAssignment<ReturnsBool, ReturnsBool>);
    static_assert(ReturnAndAssignment<ReturnsBool, ReturnsBool, bool>);

    // Self const& is not Self&: the default Return rejects a const-qualified
    // return even though AndAssignment is satisfied.

    static_assert(not ReturnAndAssignment<ConstQualified, ConstQualified>);
    static_assert(ReturnAndAssignment<ConstQualified, ConstQualified, ConstQualified const&>);

    // The inherited operator returns Base&, not Derived&, since it isn't
    // virtual: the default Return fails on Derived, and only the explicit
    // Base& form succeeds.

    static_assert(not ReturnAndAssignment<Derived, Base>);
    static_assert(ReturnAndAssignment<Derived, Base, Base&>);
    
    struct Incomplete;
    return not AndAssignment<Incomplete, Incomplete> and not ReturnAndAssignment<Incomplete,
    Incomplete>;
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