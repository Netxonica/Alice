// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/UnaryMinus.hpp"

using Alice::Operator::UnaryMinus;
using Alice::Operator::ReturnUnaryMinus;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // A type with no operators at all.
    
    struct Empty{};

    // A type whose unary minus operator is explicitly deleted.
    
    struct Forbidden
    {
        Forbidden operator-() const = delete;
    };

    // A type whose unary minus operator returns the same type.
    
    struct Vector2
    {
        int x, y;

        constexpr Vector2 operator-() const
        {
            return Vector2{-x, -y};
        }
    };

    // A type whose unary minus operator returns a different type.

    struct Magnitude
    {
        int value;

        constexpr int operator-() const
        {
            return -value;
        }
    };

    // A type whose unary minus operator returns void.

    struct Logger
    {
        constexpr void operator-() const{}
    };

    // A type whose unary minus operator returns a reference.

    struct SelfReferencing
    {
        SelfReferencing& operator-() const;
    };

    // A type whose unary minus operator returns a wider, unrelated type.

    struct WidensReturn
    {
        long operator-() const;
    };

    // A type whose unary minus operator is only callable on lvalues.

    struct LvalueOnly
    {
        LvalueOnly operator-() &;
    };

    // A type whose unary minus operator is only callable on rvalues.

    struct RvalueOnly
    {
        RvalueOnly operator-() &&;
    };

    // ===========================================================================
    // UnaryMinus
    // ===========================================================================

    // Built-in arithmetic types support unary minus.

    static_assert(UnaryMinus<int>);
    static_assert(UnaryMinus<double>);
    static_assert(UnaryMinus<short>);

    // Pointers do not support unary minus.

    static_assert(not UnaryMinus<int*>);

    // User-defined types with a usable operator-.

    static_assert(UnaryMinus<Vector2>);
    static_assert(UnaryMinus<Magnitude>);
    static_assert(UnaryMinus<Logger>);
    static_assert(UnaryMinus<SelfReferencing>);
    static_assert(UnaryMinus<WidensReturn>);

    // User-defined types with no usable operator-.

    static_assert(not UnaryMinus<Empty>);
    static_assert(not UnaryMinus<Forbidden>);

    // Self is forwarded according to its own value category: a plain Self
    // forwards as an rvalue, whereas Self& forwards as an lvalue.

    static_assert(not UnaryMinus<LvalueOnly>);
    static_assert(UnaryMinus<LvalueOnly&>);
    static_assert(UnaryMinus<RvalueOnly>);
    static_assert(not UnaryMinus<RvalueOnly&>);

    // ===========================================================================
    // ReturnUnaryMinus
    // ===========================================================================

    // Return defaults to Self.

    static_assert(ReturnUnaryMinus<int>);
    static_assert(ReturnUnaryMinus<int, int>);
    static_assert(ReturnUnaryMinus<Vector2>);
    static_assert(ReturnUnaryMinus<Vector2, Vector2>);

    // short is promoted to int by unary minus, so it does not return short.

    static_assert(not ReturnUnaryMinus<short>);
    static_assert(ReturnUnaryMinus<short, int>);

    // Explicit, non-default Return.

    static_assert(ReturnUnaryMinus<Magnitude, int>);
    static_assert(not ReturnUnaryMinus<Magnitude>);
    static_assert(not ReturnUnaryMinus<Magnitude, double>);

    // void is a legitimate Return.

    static_assert(ReturnUnaryMinus<Logger, void>);
    static_assert(not ReturnUnaryMinus<Logger>);

    // The match performed against Return is exact: references and
    // implicitly-convertible types do not satisfy one another.

    static_assert(ReturnUnaryMinus<SelfReferencing, SelfReferencing&>);
    static_assert(not ReturnUnaryMinus<SelfReferencing>);
    static_assert(ReturnUnaryMinus<WidensReturn, long>);
    static_assert(not ReturnUnaryMinus<WidensReturn, int>);

    // Types with no usable operator- never satisfy ReturnUnaryMinus, regardless
    // of Return.

    static_assert(not ReturnUnaryMinus<Empty>);
    static_assert(not ReturnUnaryMinus<Empty, void>);
    static_assert(not ReturnUnaryMinus<Forbidden>);
    static_assert(not ReturnUnaryMinus<Forbidden, int>);

    struct Incomplete;
    return not UnaryMinus<Incomplete> and not ReturnUnaryMinus<Incomplete>;
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