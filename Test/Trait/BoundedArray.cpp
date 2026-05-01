// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/BoundedArray.hpp"

using Alice::Trait::BoundedArray;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    static_assert(BoundedArray<int[5]>, "int[5] is a bounded array");
    static_assert(BoundedArray<float[1]>, "float[1] is a bounded array");
    static_assert(BoundedArray<bool[100]>, "bool[100] is a bounded array");
    static_assert(BoundedArray<char[1024]>, "char[1024] is a bounded array");

    static_assert(not BoundedArray<int[]>, "int[] is not a bounded array (unbounded)");
    static_assert(not BoundedArray<int>, "int is not an array at all");
    static_assert(not BoundedArray<int*>, "int* is not an array");
    static_assert(not BoundedArray<int&>, "int& is not an array");
    static_assert(not BoundedArray<void>, "void is not an array");
    static_assert(not BoundedArray<decltype(nullptr)>, "nullptr_t is not an array");

    struct S{};

    static_assert(BoundedArray<S[3]>, "S[3] is a bounded array");
    static_assert(not BoundedArray<S>, "S is not an array");
    static_assert(not BoundedArray<S[]>, "S[] is not a bounded array");
    static_assert(not BoundedArray<S*>, "S* is not an array");

    static_assert(BoundedArray<int[1][2]>, "int[1][2] is a bounded (multidimensional) array");
    static_assert(not BoundedArray<int(*)[5]>, "int(*)[5] is a pointer, not an array");
    static_assert(not BoundedArray<const int*>, "const int* is not an array");
    static_assert(BoundedArray<const int[4]>, "const int[4] is a bounded array");
    static_assert(BoundedArray<volatile int[4]>, "volatile int[4] is a bounded array");

    struct Incomplete;
    return not BoundedArray<Incomplete>;
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