// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/OrAssignment.hpp"

using Alice::Operator::OrAssignment;
using Alice::Operator::ReturnOrAssignment;

// A free (non-member) operator|=, found via ADL, must count too.

struct FreeRhs{};

struct FreeSelf{};

FreeSelf& operator|=(FreeSelf& self, FreeRhs const&) noexcept
{
    return self;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // No operators at all: neither concept should be satisfied.

    struct NoOperators{};

    static_assert(not OrAssignment<NoOperators, NoOperators>, "an empty type has no operator|=");
    static_assert(not ReturnOrAssignment<NoOperators, NoOperators>,
    "an empty type has no operator|=");

    // Overloading bitwise or (operator|) must not be mistaken for or-assignment (operator|=).

    struct OnlyBitwiseOr
    {
        OnlyBitwiseOr operator|(OnlyBitwiseOr const&) const
        {
            return *this;
        }
    };

    static_assert(not OrAssignment<OnlyBitwiseOr, OnlyBitwiseOr const&>,
    "operator| is not operator|=");

    // The ordinary case: a member operator|= returning Self&.
    
    struct Basic
    {
        Basic& operator|=(Basic const&) noexcept
        {
            return *this;
        }
    };

    static_assert(OrAssignment<Basic, Basic const&>);
    static_assert(ReturnOrAssignment<Basic, Basic const&>, "default Return should be Self&");
    static_assert(ReturnOrAssignment<Basic, Basic const&, Basic&>,
    "explicit Return should match too");

    // A const Self cannot call the non-const member, so both concepts must fail.

    static_assert(not OrAssignment<Basic const, Basic const&>,
    "a const object can't call a non-const member");
    static_assert(not ReturnOrAssignment<Basic const, Basic const&>);
    static_assert(OrAssignment<FreeSelf, FreeRhs const&>, "non-member operators are found via ADL")
    ;
    static_assert(ReturnOrAssignment<FreeSelf, FreeRhs const&>);

    // A deleted overload must not satisfy the concept.

    struct DeletedRhs{};

    struct HasDeletedOverload
    {
        HasDeletedOverload& operator|=(DeletedRhs const&) = delete;
    };

    static_assert(not OrAssignment<HasDeletedOverload, DeletedRhs const&>,
    "a deleted operator is not usable");

    // $forward(rhs) forwards according to Rhs's own value category. MoveOnly rules out any
    // copy-based workaround, so these assertions only pass if forwarding is truly value-category-correct.
    
    struct MoveOnly
    {
        MoveOnly() = default;
    
        MoveOnly(MoveOnly&&) = default;
    
        MoveOnly(MoveOnly const&) = delete;
    
        MoveOnly& operator=(MoveOnly&&) = default;
    
        MoveOnly& operator=(MoveOnly const&) = delete;
    };

    struct AcceptsRvalue
    {
        AcceptsRvalue& operator|=(MoveOnly&&) noexcept
        {
            return *this;
        }
    };

    static_assert(OrAssignment<AcceptsRvalue, MoveOnly>, "Rhs by value is forwarded as an rvalue");
    static_assert(not OrAssignment<AcceptsRvalue, MoveOnly&>,
    "an lvalue Rhs can't bind to MoveOnly&&");

    struct AcceptsLvalue
    {
        AcceptsLvalue& operator|=(MoveOnly&) noexcept
        {
            return *this;
        }
    };

    static_assert(not OrAssignment<AcceptsLvalue, MoveOnly>,
    "an rvalue Rhs can't bind to MoveOnly&");
    static_assert(OrAssignment<AcceptsLvalue, MoveOnly&>,
    "Rhs as MoveOnly& is forwarded as an lvalue");

    // OrAssignment only asks that the expression be valid: an implicitly convertible Rhs
    // is enough, it need not be the exact parameter type.
    
    struct TakesInt
    {
        TakesInt& operator|=(int) noexcept
        {
            return *this;
        }
    };

    static_assert(OrAssignment<TakesInt, int>);
    static_assert(OrAssignment<TakesInt, short>, "short -> int is an implicit conversion");
    static_assert(not OrAssignment<TakesInt, NoOperators>, "no conversion to int exists");

    // Fundamental types have a built-in operator|= too.
    
    static_assert(OrAssignment<int, int>, "built-in types support operator|=");
    static_assert(ReturnOrAssignment<int, int>,
    "built-in |= yields an lvalue of the left operand's type");

    // ReturnOrAssignment is exact about the returned type: reference-ness and const-ness
    // both matter, not just convertibility.
    
    struct ReturnsVoid
    {
        void operator|=(ReturnsVoid const&) noexcept{}
    };

    static_assert(OrAssignment<ReturnsVoid, ReturnsVoid const&>);
    static_assert(not ReturnOrAssignment<ReturnsVoid, ReturnsVoid const&>,
    "default Return wants Self&, not void");
    static_assert(ReturnOrAssignment<ReturnsVoid, ReturnsVoid const&, void>);

    struct ReturnsByValue
    {
        ReturnsByValue operator|=(ReturnsByValue const&) noexcept
        {
            return *this;
        }
    };

    static_assert(OrAssignment<ReturnsByValue, ReturnsByValue const&>);
    static_assert(not ReturnOrAssignment<ReturnsByValue, ReturnsByValue const&>,
    "a prvalue Self is not Self&");
    static_assert(ReturnOrAssignment<ReturnsByValue, ReturnsByValue const&, ReturnsByValue>);

    struct ReturnsConstRef
    {
        ReturnsConstRef const& operator|=(ReturnsConstRef const&) noexcept
        {
            return *this;
        }
    };

    static_assert(OrAssignment<ReturnsConstRef, ReturnsConstRef const&>);
    static_assert(not ReturnOrAssignment<ReturnsConstRef, ReturnsConstRef const&>,
    "Self const& is not Self&");
    static_assert(ReturnOrAssignment<ReturnsConstRef, ReturnsConstRef const&, ReturnsConstRef const
    &>);

    struct Incomplete;
    return not OrAssignment<Incomplete, Incomplete> and not ReturnOrAssignment<Incomplete,
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