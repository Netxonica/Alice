// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Void.hpp"

using Alice::Trait::Void;

template<Void> constexpr bool is_void_constrained()
{
    return true;
}

template<class> constexpr bool is_void_constrained()
{
    return false;
}

struct EmptyStruct{};

union EmptyUnion{};

enum PlainEnum
{
    A,
    B
};

enum class ScopedEnum
{
    X,
    Y
};

struct Incomplete;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Positive cases: types that satisfy Void ---

    static_assert(Void<void>, "void must satisfy Void");
    static_assert(Void<const void>, "const void must satisfy Void");
    static_assert(Void<volatile void>, "volatile void must satisfy Void");
    static_assert(Void<const volatile void>, "const volatile void must satisfy Void");

    // --- Negative cases: types that must not satisfy Void ---

    static_assert(not Void<void*>, "void* must not satisfy Void");
    static_assert(not Void<const void*>, "const void* must not satisfy Void");
    static_assert(not Void<int>, "int must not satisfy Void");
    static_assert(not Void<const int>, "const int must not satisfy Void");
    static_assert(not Void<volatile int>, "volatile int must not satisfy Void");
    static_assert(not Void<const volatile int>, "const volatile int must not satisfy Void");
    static_assert(not Void<int*>, "int* must not satisfy Void");
    static_assert(not Void<int&>, "int& must not satisfy Void");
    static_assert(not Void<int&&>, "int&& must not satisfy Void");
    static_assert(not Void<int[]>, "int[] must not satisfy Void");
    static_assert(not Void<int[4]>, "int[4] must not satisfy Void");
    static_assert(not Void<float>, "float must not satisfy Void");
    static_assert(not Void<double>, "double must not satisfy Void");
    static_assert(not Void<bool>, "bool must not satisfy Void");
    static_assert(not Void<char>, "char must not satisfy Void");
    static_assert(not Void<unsigned char>, "unsigned char must not satisfy Void");
    static_assert(not Void<long long>, "long long must not satisfy Void");

    // --- User-defined types must not satisfy Void ---

    static_assert(not Void<EmptyStruct>, "EmptyStruct must not satisfy Void");
    static_assert(not Void<EmptyUnion>, "EmptyUnion must not satisfy Void");
    static_assert(not Void<PlainEnum>, "PlainEnum must not satisfy Void");
    static_assert(not Void<ScopedEnum>, "ScopedEnum must not satisfy Void");

    // --- Function and member pointer types must not satisfy Void ---

    static_assert(not Void<void()>, "void() (function type) must not satisfy Void");
    static_assert(not Void<void(*)()>, "void(*)() must not satisfy Void");
    static_assert(not Void<void(EmptyStruct::*)()>, "member function pointer must not satisfy Void"
    );
    static_assert(not Void<int EmptyStruct::*>, "member object pointer must not satisfy Void");

    // --- Concept constraint usage via a constrained template ---

    static_assert(is_void_constrained<void>(),
    "constrained template must select void overload for void");
    static_assert(is_void_constrained<const void>(),
    "constrained template must select void overload for const void");
    static_assert(not is_void_constrained<int>(),
    "constrained template must not select void overload for int");
    static_assert(not is_void_constrained<void*>(),
    "constrained template must not select void overload for void*");

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