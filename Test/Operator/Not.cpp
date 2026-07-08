// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Not.hpp"

using Alice::Operator::Not;
using Alice::Operator::ReturnNot;

// A scoped enum with a free (non-member) operator~ overload: the usual
// shape of a "bitmask" enum class. Not/ReturnNot must find this via
// ordinary operator lookup just as readily as a member overload.

enum class BitmaskFlags
{
    None = 0,
    A = 1 << 0,
    B = 1 << 1,
};

constexpr BitmaskFlags operator~(BitmaskFlags self) noexcept
{
    return static_cast<BitmaskFlags>(compl static_cast<int>(self));
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // A type with no bitwise-not operator at all.

    struct NoOperator{};

    // operator~ exists and returns Self by value: the ordinary case that
    // ReturnNot's default template argument (Return = Self) is meant to
    // recognise.

    struct ReturnsSelf
    {
        constexpr ReturnsSelf operator~() const noexcept
        {
            return ReturnsSelf{};
        }
    };

    // operator~ exists but returns something other than Self.

    struct ReturnsBool
    {
        constexpr bool operator~() const noexcept
        {
            return true;
        }
    };

    // operator~ exists and returns void.

    struct ReturnsVoid
    {
        constexpr void operator~() const noexcept{}
    };

    // operator~ is usable only on an rvalue *this.

    struct RvalueQualifiedOnly
    {
        constexpr RvalueQualifiedOnly operator~() && noexcept
        {
            return RvalueQualifiedOnly{};
        }
    };

    // operator~ is usable only on an lvalue *this. Not/ReturnNot invoke the
    // operator through $forward(self), which casts self to an rvalue, so
    // this overload can never be selected.

    struct LvalueQualifiedOnly
    {
        constexpr LvalueQualifiedOnly operator~() & noexcept
        {
            return LvalueQualifiedOnly{};
        }
    };

    // A scoped enum with no operator~ overload at all.

    enum class PlainFlags
    {
        None,
        A,
        B,
    };

    // ---------------------------------------------------------------------
    // Not: does Self overload a bitwise-not operator at all?
    // ---------------------------------------------------------------------

    static_assert(Not<int>, "a builtin integral type must satisfy Not");
    static_assert(not Not<int*>, "pointers have no operator~");
    static_assert(not Not<double>, "floating-point types have no operator~");
    static_assert(not Not<NoOperator>, "a type with no operator~ must fail Not");
    static_assert(Not<ReturnsSelf>);
    static_assert(Not<ReturnsBool>);
    static_assert(Not<ReturnsVoid>);
    static_assert(Not<RvalueQualifiedOnly>,
    "self is forwarded as an rvalue, so an &&-qualified overload must be found");
    static_assert(not Not<LvalueQualifiedOnly>,
    "self is forwarded as an rvalue, so a &-qualified overload must not be found");
    static_assert(not Not<PlainFlags>, "a scoped enum has no builtin operator~");
    static_assert(Not<BitmaskFlags>, "a free-function operator~ must be found too");

    // ---------------------------------------------------------------------
    // ReturnNot: does Self overload operator~, and does it return exactly
    // Return (Self, by default)?
    // ---------------------------------------------------------------------

    static_assert(ReturnNot<int>, "int's operator~ returns int");
    static_assert(ReturnNot<int, int>);

    // A short is integer-promoted to int before compl is applied, so the
    // result is int, not short: the default Return = Self must fail here.

    static_assert(Not<short>);
    static_assert(not ReturnNot<short>,
    "compl on a short yields int due to integral promotion, not short");
    static_assert(ReturnNot<short, int>);
    static_assert(ReturnNot<ReturnsSelf>);
    static_assert(ReturnNot<ReturnsSelf, ReturnsSelf>);
    static_assert(not ReturnNot<ReturnsBool>, "default Return = Self does not match bool");
    static_assert(ReturnNot<ReturnsBool, bool>);
    static_assert(not ReturnNot<ReturnsBool, int>,
    "Trait::Same must require an exact type match, not mere convertibility");
    static_assert(not ReturnNot<ReturnsVoid>);
    static_assert(ReturnNot<ReturnsVoid, void>);
    static_assert(ReturnNot<RvalueQualifiedOnly>);
    static_assert(not ReturnNot<LvalueQualifiedOnly>);
    static_assert(ReturnNot<BitmaskFlags>, "the free operator~ returns BitmaskFlags by value");
    
    struct Incomplete;
    return not Not<Incomplete> and not ReturnNot<Incomplete>;
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