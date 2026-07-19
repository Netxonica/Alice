// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Add.hpp"

using Alice::Operator::Add;
using Alice::Operator::ReturnAdd;

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

    static_assert(Add<Point2D, Point2D>);
    static_assert(ReturnAdd<Point2D, Point2D>);

    // 2. No operator+ at all.

    struct NotAddable
    {
        int value;
    };

    static_assert(not Add<NotAddable, NotAddable>);
    static_assert(not ReturnAdd<NotAddable, NotAddable>);
    static_assert(not ReturnAdd<NotAddable, NotAddable, int>);

    // 3. operator+ exists but is deleted.

    struct DeletedAdd
    {
        DeletedAdd operator+(DeletedAdd const&) const = delete;
    };

    static_assert(not Add<DeletedAdd, DeletedAdd>);

    // 4. Add only cares that + compiles; ReturnAdd pins the return type.

    struct Ratio
    {
        double value;

        constexpr double operator+(Ratio const& rhs) const noexcept
        {
            return value + rhs.value;
        }
    };

    static_assert(Add<Ratio, Ratio>);
    static_assert(not ReturnAdd<Ratio, Ratio>);
    static_assert(ReturnAdd<Ratio, Ratio, double>);

    // 5. Asymmetric addition through a non-member operator+.

    static_assert(Add<Left, Right>);
    static_assert(not Add<Right, Left>);
    static_assert(ReturnAdd<Left, Right>);
    static_assert(not ReturnAdd<Left, Right, Right>);

    // 6. Ref-qualification sensitivity via $forward.

    struct RvalueOnly
    {
        constexpr RvalueOnly operator+(RvalueOnly const&) && noexcept
        {
            return RvalueOnly{};
        }
    };

    static_assert(Add<RvalueOnly, RvalueOnly>);
    static_assert(not Add<RvalueOnly&, RvalueOnly>);

    // 7. Fundamental types and usual arithmetic conversions.

    static_assert(Add<int, int>);
    static_assert(ReturnAdd<int, int>);
    static_assert(Add<int, double>);
    static_assert(not ReturnAdd<int, double>);
    static_assert(ReturnAdd<int, double, double>);
    static_assert(Add<bool, bool>);
    static_assert(not ReturnAdd<bool, bool>);
    static_assert(ReturnAdd<bool, bool, int>);

    // 8. Pointer arithmetic.

    static_assert(Add<int*, int>);
    static_assert(ReturnAdd<int*, int>);
    static_assert(not Add<int*, int*>);

    // 9. Scoped enum has no arithmetic operators by default.

    enum class Color
    {
        Red,
        Green,
        Blue,
    };

    static_assert(not Add<Color, Color>);

    struct Incomplete;
    return not Add<Incomplete, Incomplete> and not ReturnAdd<Incomplete, Incomplete>;
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