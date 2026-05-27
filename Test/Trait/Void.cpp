// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Void.hpp"

using Alice::Trait::Void;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Positive cases: all void-qualified variants must satisfy the concept ---

    static_assert(Void<void>, "void must satisfy Void");
    static_assert(Void<const void>, "const void must satisfy Void");
    static_assert(Void<volatile void>, "volatile void must satisfy Void");
    static_assert(Void<const volatile void>, "const volatile void must satisfy Void");

    // --- Negative cases: no non-void type may satisfy the concept ---

    static_assert(not Void<int>, "int must not satisfy Void");
    static_assert(not Void<unsigned>, "unsigned must not satisfy Void");
    static_assert(not Void<bool>, "bool must not satisfy Void");
    static_assert(not Void<char>, "char must not satisfy Void");
    static_assert(not Void<float>, "float must not satisfy Void");
    static_assert(not Void<double>, "double must not satisfy Void");
    static_assert(not Void<void*>, "void* must not satisfy Void");
    static_assert(not Void<const void*>, "const void* must not satisfy Void");
    static_assert(not Void<int*>, "int* must not satisfy Void");
    static_assert(not Void<int&>, "int& must not satisfy Void");
    static_assert(not Void<int&&>, "int&& must not satisfy Void");
    static_assert(not Void<int[]>, "int[] must not satisfy Void");
    static_assert(not Void<int[4]>, "int[4] must not satisfy Void");
    static_assert(not Void<decltype(nullptr)>, "nullptr_t must not satisfy Void");

    // --- The concept must reject cv-qualified non-void types too ---

    static_assert(not Void<const int>, "const int must not satisfy Void");
    static_assert(not Void<volatile int>, "volatile int must not satisfy Void");
    static_assert(not Void<const volatile int>, "const volatile int must not satisfy Void");

    // --- Struct / union / enum types must not satisfy the concept ---

    struct S{};

    union U
    {
        int i;
        
        float f;
    };

    enum E
    {
        A,
        B
    };

    enum class EC
    {
        X,
        Y
    };

    static_assert(not Void<S>, "struct type must not satisfy Void");
    static_assert(not Void<U>, "union type must not satisfy Void");
    static_assert(not Void<E>, "enum type must not satisfy Void");
    static_assert(not Void<EC>, "scoped enum type must not satisfy Void");

    // --- Function types must not satisfy the concept ---

    static_assert(not Void<void()>, "function type void() must not satisfy Void");
    static_assert(not Void<void(int)>, "function type void(int) must not satisfy Void");
    static_assert(not Void<int(int, int)>, "function type int(int,int) must not satisfy Void");

    struct Incomplete;
    return not Void<Incomplete>;
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