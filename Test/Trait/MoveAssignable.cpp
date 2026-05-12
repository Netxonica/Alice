// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/MoveAssignable.hpp"

using Alice::Trait::MoveAssignable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Basic move-assignable types

    static_assert(MoveAssignable<int>);
    static_assert(MoveAssignable<float>);
    static_assert(MoveAssignable<double>);
    static_assert(MoveAssignable<char>);
    static_assert(MoveAssignable<int*>);

    // Explicitly move-assignable struct

    struct Movable
    {
        Movable& operator=(Movable&&) = default;
    };

    static_assert(MoveAssignable<Movable>);

    // Copy-only type is still move-assignable (copy assignment binds to rvalue)

    struct CopyOnly
    {
        CopyOnly& operator=(const CopyOnly&) = default;

        CopyOnly& operator=(CopyOnly&&) = delete;
    };

    static_assert(not MoveAssignable<CopyOnly>);

    // Deleted move assignment

    struct NoMove
    {
        NoMove& operator=(NoMove&&) = delete;
    };

    static_assert(not MoveAssignable<NoMove>);

    // Fully non-assignable

    struct NoAssign
    {
        NoAssign& operator=(const NoAssign&) = delete;

        NoAssign& operator=(NoAssign&&) = delete;
    };

    static_assert(not MoveAssignable<NoAssign>);

    // const-qualified types cannot be assigned to

    static_assert(not MoveAssignable<const int>);
    static_assert(not MoveAssignable<const Movable>);

    // References: lvalue refs to assignable types

    static_assert(MoveAssignable<int&>);
    static_assert(not MoveAssignable<Movable&>);

    // rvalue references

    static_assert(MoveAssignable<int&&>);

    struct Incomplete;
    return not MoveAssignable<Incomplete>;
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