// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemoveExtents.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemoveExtents;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Non-array types: RemoveExtents should be a no-op ---

    static_assert(Same<RemoveExtents<int>, int>);
    static_assert(Same<RemoveExtents<const int>, const int>);
    static_assert(Same<RemoveExtents<int*>, int*>);
    static_assert(Same<RemoveExtents<int&>, int&>);
    static_assert(Same<RemoveExtents<int&&>, int&&>);
    static_assert(Same<RemoveExtents<void>, void>);
    static_assert(Same<RemoveExtents<const void>, const void>);

    // --- Single known-bound extent ---

    static_assert(Same<RemoveExtents<int[4]>, int>);
    static_assert(Same<RemoveExtents<int[1]>, int>);
    static_assert(Same<RemoveExtents<const int[4]>, const int>);
    static_assert(Same<RemoveExtents<int*[4]>, int*>);

    // --- Single unknown-bound extent ---

    static_assert(Same<RemoveExtents<int[]>, int>);
    static_assert(Same<RemoveExtents<const int[]>, const int>);
    static_assert(Same<RemoveExtents<int*[]>, int*>);

    // --- Multi-dimensional known-bound extents (all must be stripped) ---

    static_assert(Same<RemoveExtents<int[2][3]>, int>);
    static_assert(Same<RemoveExtents<int[2][3][4]>, int>);
    static_assert(Same<RemoveExtents<const int[2][3]>, const int>);
    static_assert(Same<RemoveExtents<int*[2][3]>, int*>);

    // --- Mixed known/unknown extents ---

    static_assert(Same<RemoveExtents<int[][3]>, int>);
    static_assert(Same<RemoveExtents<int[][3][4]>, int>);

    // --- Pointer-to-array: pointer is NOT an extent, must not be touched ---

    static_assert(Same<RemoveExtents<int(*)[4]>, int(*)[4]>);
    static_assert(Same<RemoveExtents<int(&)[4]>, int(&)[4]>);

    struct Incomplete;
    return Same<RemoveExtents<Incomplete>, Incomplete>;
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