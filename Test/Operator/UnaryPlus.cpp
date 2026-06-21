// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/UnaryPlus.hpp"

using Alice::Operator::UnaryPlus;
using Alice::Operator::ReturnUnaryPlus;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // No operator+ at all.
    struct NoOperators
    {
        int value{};
    };

    // operator+() returning Self by value.
    struct ReturnsSelf
    {
        int value{};

        constexpr ReturnsSelf operator+() const
        {
            return *this;
        }
    };

    // Unrelated type, used below as a non-Self return type.
    struct Other
    {
        int value{};
    };

    // operator+() returning a type other than Self.
    struct ReturnsOther
    {
        constexpr Other operator+() const
        {
            return Other{42};
        }
    };

    // operator+() returning void.
    struct ReturnsVoid
    {
        constexpr void operator+() const{}
    };

    // operator+() returning a reference to a member.
    struct ReturnsIntReference
    {
        int value{7};

        constexpr int& operator+()
        {
            return value;
        }
    };

    // operator+() returning a const lvalue reference to Self.
    struct ReturnsConstSelfReference
    {
        constexpr const ReturnsConstSelfReference& operator+() const
        {
            return *this;
        }
    };

    // Only a binary operator+ is provided; no unary overload exists.
    struct OnlyBinaryPlus
    {
        constexpr OnlyBinaryPlus operator+(const OnlyBinaryPlus& other) const
        {
            return other;
        }
    };

    // UnaryPlus --------------------------------------------------------------

    static_assert(UnaryPlus<int>);
    static_assert(UnaryPlus<double>);
    static_assert(UnaryPlus<int*>);
    static_assert(UnaryPlus<ReturnsSelf>);
    static_assert(UnaryPlus<const ReturnsSelf>);
    static_assert(UnaryPlus<ReturnsOther>);
    static_assert(UnaryPlus<ReturnsVoid>);
    static_assert(UnaryPlus<ReturnsIntReference>);
    static_assert(UnaryPlus<ReturnsConstSelfReference>);

    static_assert(not UnaryPlus<NoOperators>);
    static_assert(not UnaryPlus<OnlyBinaryPlus>);

    // ReturnUnaryPlus, default Return = Self ----------------------------------

    static_assert(ReturnUnaryPlus<int>);
    static_assert(ReturnUnaryPlus<ReturnsSelf>);

    // Self is const-qualified here, so the *default* Return is "const
    // ReturnsSelf" too -- but operator+ returns a plain (non-const)
    // ReturnsSelf, so the default form must fail even though UnaryPlus
    // holds. The explicit, unqualified Return matches instead.

    static_assert(not ReturnUnaryPlus<const ReturnsSelf>);
    static_assert(ReturnUnaryPlus<const ReturnsSelf, ReturnsSelf>);
    static_assert(not ReturnUnaryPlus<ReturnsOther>);
    static_assert(not ReturnUnaryPlus<ReturnsVoid>);
    static_assert(not ReturnUnaryPlus<ReturnsIntReference>);
    static_assert(not ReturnUnaryPlus<ReturnsConstSelfReference>);
    static_assert(not ReturnUnaryPlus<NoOperators>);
    static_assert(not ReturnUnaryPlus<NoOperators, void>);

    // ReturnUnaryPlus, explicit Return -----------------------------------------

    static_assert(ReturnUnaryPlus<ReturnsOther, Other>);
    static_assert(not ReturnUnaryPlus<ReturnsOther, ReturnsOther>);
    static_assert(ReturnUnaryPlus<ReturnsVoid, void>);

    // Result type must match exactly, including reference-ness and
    // cv-qualification.

    static_assert(ReturnUnaryPlus<ReturnsIntReference, int&>);
    static_assert(not ReturnUnaryPlus<ReturnsIntReference, int>);
    static_assert(not ReturnUnaryPlus<ReturnsIntReference, const int&>);
    static_assert(ReturnUnaryPlus<ReturnsConstSelfReference, const ReturnsConstSelfReference&>);
    static_assert(not ReturnUnaryPlus<ReturnsConstSelfReference, ReturnsConstSelfReference>);
    static_assert(not ReturnUnaryPlus<ReturnsConstSelfReference, ReturnsConstSelfReference&>);

    struct Incomplete;
    return not UnaryPlus<Incomplete> and not ReturnUnaryPlus<Incomplete>;
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