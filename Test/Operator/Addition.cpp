// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Addition.hpp"

using Alice::Operator::Addition;
using Alice::Operator::ReturnAddition;

struct Left
{
    int value;
};

struct Right
{
    int value;
};

constexpr Left operator+(Left const& lhs, Right const& rhs) noexcept
{
    return Left{lhs.value + rhs.value};
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // 1. Ordinary member operator+ returning Self.

    struct Point2D
    {
        int x, y;

        constexpr Point2D operator+(Point2D const& rhs) const noexcept
        {
            return Point2D{x + rhs.x, y + rhs.y};
        }
    };

    static_assert(Addition<Point2D, Point2D>);
    static_assert(ReturnAddition<Point2D, Point2D>);

    // 2. No operator+ at all.

    struct NotAddable
    {
        int value;
    };

    static_assert(not Addition<NotAddable, NotAddable>);
    static_assert(not ReturnAddition<NotAddable, NotAddable>);
    static_assert(not ReturnAddition<NotAddable, NotAddable, int>);

    // 3. operator+ exists but is deleted.

    struct DeletedAdd
    {
        DeletedAdd operator+(DeletedAdd const&) const = delete;
    };

    static_assert(not Addition<DeletedAdd, DeletedAdd>);

    // 4. Add only cares that + compiles; ReturnAdd pins the return type.

    struct Ratio
    {
        double value;

        constexpr double operator+(Ratio const& rhs) const noexcept
        {
            return value + rhs.value;
        }
    };

    static_assert(Addition<Ratio, Ratio>);
    static_assert(not ReturnAddition<Ratio, Ratio>);
    static_assert(ReturnAddition<Ratio, Ratio, double>);

    // 5. Asymmetric addition through a non-member operator+.

    static_assert(Addition<Left, Right>);
    static_assert(not Addition<Right, Left>);
    static_assert(ReturnAddition<Left, Right>);
    static_assert(not ReturnAddition<Left, Right, Right>);

    // 6. Ref-qualification sensitivity via $forward.

    struct RvalueOnly
    {
        constexpr RvalueOnly operator+(RvalueOnly const&) && noexcept
        {
            return RvalueOnly{};
        }
    };

    static_assert(Addition<RvalueOnly, RvalueOnly>);
    static_assert(not Addition<RvalueOnly&, RvalueOnly>);

    // 7. Fundamental types and usual arithmetic conversions.

    static_assert(Addition<int, int>);
    static_assert(ReturnAddition<int, int>);
    static_assert(Addition<int, double>);
    static_assert(not ReturnAddition<int, double>);
    static_assert(ReturnAddition<int, double, double>);
    static_assert(Addition<bool, bool>);
    static_assert(not ReturnAddition<bool, bool>);
    static_assert(ReturnAddition<bool, bool, int>);

    // 8. Pointer arithmetic.

    static_assert(Addition<int*, int>);
    static_assert(ReturnAddition<int*, int>);
    static_assert(not Addition<int*, int*>);

    // 9. Scoped enum has no arithmetic operators by default.

    enum class Color
    {
        Red,
        Green,
        Blue,
    };

    static_assert(not Addition<Color, Color>);

    struct Incomplete;
    return not Addition<Incomplete, Incomplete> and not ReturnAddition<Incomplete, Incomplete>;
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