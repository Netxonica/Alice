// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/LvalueReference.hpp"

using Alice::Trait::LvalueReference;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Positive cases: types that must satisfy LvalueReference ---

    static_assert(LvalueReference<int&>, "int& must satisfy LvalueReference");
    static_assert(LvalueReference<const int&>, "const int& must satisfy LvalueReference");
    static_assert(LvalueReference<volatile int&>, "volatile int& must satisfy LvalueReference");
    static_assert(LvalueReference<const volatile int&>,
    "const volatile int& must satisfy LvalueReference");
    static_assert(LvalueReference<int*&>, "int*& must satisfy LvalueReference");
    static_assert(LvalueReference<const int*&>, "const int*& must satisfy LvalueReference");
    static_assert(LvalueReference<int(&)[]>, "int(&)[] must satisfy LvalueReference");
    static_assert(LvalueReference<int(&)[4]>, "int(&)[4] must satisfy LvalueReference");
    static_assert(LvalueReference<void*&>, "void*& must satisfy LvalueReference");
    static_assert(LvalueReference<int(&)(int)>,
    "lvalue reference to function must satisfy LvalueReference");

    // --- Negative cases: types that must not satisfy LvalueReference ---

    static_assert(not LvalueReference<int>, "int must not satisfy LvalueReference");
    static_assert(not LvalueReference<const int>, "const int must not satisfy LvalueReference");
    static_assert(not LvalueReference<volatile int>,
    "volatile int must not satisfy LvalueReference");
    static_assert(not LvalueReference<const volatile int>,
    "const volatile int must not satisfy LvalueReference");
    static_assert(not LvalueReference<int*>, "int* must not satisfy LvalueReference");
    static_assert(not LvalueReference<const int*>, "const int* must not satisfy LvalueReference");
    static_assert(not LvalueReference<int**>, "int** must not satisfy LvalueReference");
    static_assert(not LvalueReference<int&&>, "int&& must not satisfy LvalueReference");
    static_assert(not LvalueReference<const int&&>, "const int&& must not satisfy LvalueReference")
    ;
    static_assert(not LvalueReference<void>, "void must not satisfy LvalueReference");
    static_assert(not LvalueReference<int[]>, "int[] must not satisfy LvalueReference");
    static_assert(not LvalueReference<int[4]>, "int[4] must not satisfy LvalueReference");
    static_assert(not LvalueReference<int(int)>,
    "bare function type must not satisfy LvalueReference");
    
    struct Incomplete;
    return not LvalueReference<Incomplete>;
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