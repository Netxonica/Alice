// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/UnboundedArray.hpp"

using Alice::Trait::UnboundedArray;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Should satisfy UnboundedArray
    static_assert(UnboundedArray<int[]>);
    static_assert(UnboundedArray<const int[]>);
    static_assert(UnboundedArray<volatile int[]>);
    static_assert(UnboundedArray<const volatile int[]>);
    static_assert(UnboundedArray<int*[]>);
    static_assert(UnboundedArray<int[][4]>);

    // Should NOT satisfy UnboundedArray
    static_assert(not UnboundedArray<int>);
    static_assert(not UnboundedArray<int*>);
    static_assert(not UnboundedArray<int**>);
    static_assert(not UnboundedArray<int[4]>);
    static_assert(not UnboundedArray<int[4][4]>);
    static_assert(not UnboundedArray<int(&)[]>);
    static_assert(not UnboundedArray<int(*)[]>);
    static_assert(not UnboundedArray<void>);
    static_assert(not UnboundedArray<void*>);

    struct S{};

    static_assert(not UnboundedArray<S>);
    static_assert(not UnboundedArray<S*>);
    static_assert(not UnboundedArray<S[8]>);
    static_assert(UnboundedArray<S[]>);

    struct Incomplete;
    return not UnboundedArray<Incomplete>;
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