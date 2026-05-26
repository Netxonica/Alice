// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Pointer.hpp"

using Alice::Trait::Pointer;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Positive cases ────────────────────────────────────────────────────────────

    struct Foo{};

    // Raw pointer to a concrete struct

    static_assert(Pointer<Foo*>, "Foo* must satisfy Pointer");

    // Pointer to const-qualified type

    static_assert(Pointer<const Foo*>, "const Foo* must satisfy Pointer");

    // Pointer to volatile-qualified type

    static_assert(Pointer<volatile Foo*>, "volatile Foo* must satisfy Pointer");

    // Pointer to cv-qualified type

    static_assert(Pointer<const volatile Foo*>, "const volatile Foo* must satisfy Pointer");

    // Pointer to a fundamental type

    static_assert(Pointer<int*>, "int* must satisfy Pointer");

    // Pointer to pointer (double indirection)

    static_assert(Pointer<int**>, "int** must satisfy Pointer");

    // Pointer to void

    static_assert(Pointer<void*>, "void* must satisfy Pointer");

    // const pointer (top-level const on the pointer itself)

    static_assert(Pointer<int* const>, "int* const must satisfy Pointer");

    // Pointer to a function type

    static_assert(Pointer<void(*)(int)>, "void(*)(int) must satisfy Pointer");

    // Pointer to array element type

    static_assert(Pointer<int(*)[4]>, "int(*)[4] must satisfy Pointer");

    // ── Negative cases ────────────────────────────────────────────────────────────

    // Plain struct — not a pointer

    static_assert(not Pointer<Foo>, "Foo must not satisfy Pointer");

    // Reference — not a pointer

    static_assert(not Pointer<int&>, "int& must not satisfy Pointer");

    // rvalue reference — not a pointer

    static_assert(not Pointer<int&&>, "int&& must not satisfy Pointer");

    // Fundamental type — not a pointer

    static_assert(not Pointer<int>, "int must not satisfy Pointer");

    // void — not a pointer

    static_assert(not Pointer<void>, "void must not satisfy Pointer");

    // Array type — not a pointer

    static_assert(not Pointer<int[4]>, "int[4] must not satisfy Pointer");

    // Function type (not pointer-to-function) — not a pointer

    static_assert(not Pointer<void(int)>, "void(int) must not satisfy Pointer");

    // Pointer to member — not a raw pointer

    static_assert(not Pointer<int Foo::*>, "int Foo::* must not satisfy Pointer");

    // Member function pointer — not a raw pointer

    static_assert(not Pointer<void(Foo::*)()>, "void(Foo::*)() must not satisfy Pointer");

    // nullptr_t — not a pointer type

    static_assert(not Pointer<decltype(nullptr)>, "nullptr_t must not satisfy Pointer");

    struct Incomplete;
    return not Pointer<Incomplete>;
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