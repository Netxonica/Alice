// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/Decay.hpp"

using Alice::Trait::Same;
using Alice::Meta::Decay;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─── Auxiliary types ─────────────────────────────────────────

    struct Foo{};

    enum Bar : int{};

    // ─────────────────────────────────────────────────────────────
    // 1. Plain types
    //    Top-level cv qualifiers are stripped; nothing else changes.
    // ─────────────────────────────────────────────────────────────

    static_assert(Same<Decay<int>, int>, "plain int");
    static_assert(Same<Decay<const int>, int>, "const int → int");
    static_assert(Same<Decay<volatile int>, int>, "volatile int → int");
    static_assert(Same<Decay<const volatile int>, int>, "cv int → int");
    static_assert(Same<Decay<void>, void>, "void unchanged");
    static_assert(Same<Decay<const void>, void>, "const void → void");
    static_assert(Same<Decay<Foo>, Foo>, "struct unchanged");
    static_assert(Same<Decay<const Foo>, Foo>, "const struct → struct");
    static_assert(Same<Decay<volatile Foo>, Foo>, "volatile struct → struct");
    static_assert(Same<Decay<const volatile Foo>, Foo>, "cv struct → struct");
    static_assert(Same<Decay<Bar>, Bar>, "enum unchanged");
    static_assert(Same<Decay<const Bar>, Bar>, "const enum → enum");

    // Top-level cv on the pointer itself is stripped;
    // cv on the pointed-to type is part of the element type and is preserved.

    static_assert(Same<Decay<int*>, int*>, "int* unchanged");
    static_assert(Same<Decay<int* const>, int*>, "const ptr → ptr");
    static_assert(Same<Decay<int* volatile>, int*>, "volatile ptr → ptr");
    static_assert(Same<Decay<int* const volatile>, int*>, "cv ptr → ptr");
    static_assert(Same<Decay<const int*>, const int*>, "ptr-to-const unchanged");

    // ─────────────────────────────────────────────────────────────
    // 2. Lvalue references
    //    Reference is stripped, then the underlying type is decayed.
    // ─────────────────────────────────────────────────────────────

    static_assert(Same<Decay<int&>, int>, "int&");
    static_assert(Same<Decay<const int&>, int>, "const int&");
    static_assert(Same<Decay<volatile int&>, int>, "volatile int&");
    static_assert(Same<Decay<const volatile int&>, int>, "cv int&");
    static_assert(Same<Decay<Foo&>, Foo>, "Foo&");
    static_assert(Same<Decay<const Foo&>, Foo>, "const Foo&");
    static_assert(Same<Decay<int*&>, int*>, "int*&  → int*");
    static_assert(Same<Decay<int* const&>, int*>, "int* const& → int*");

    // ─────────────────────────────────────────────────────────────
    // 3. Rvalue references
    //    Reference is stripped, then the underlying type is decayed.
    // ─────────────────────────────────────────────────────────────

    static_assert(Same<Decay<int&&>, int>, "int&&");
    static_assert(Same<Decay<const int&&>, int>, "const int&&");
    static_assert(Same<Decay<Foo&&>, Foo>, "Foo&&");

    // ─────────────────────────────────────────────────────────────
    // 4. Bounded arrays
    //    Array decays to a pointer to its element type.
    // ─────────────────────────────────────────────────────────────
    
    static_assert(Same<Decay<int[1]>, int*>, "int[1]");
    static_assert(Same<Decay<int[42]>, int*>, "int[42]");
    static_assert(Same<Decay<const int[5]>, const int*>, "const int[5]");
    static_assert(Same<Decay<volatile int[5]>, volatile int*>, "volatile int[5]");
    static_assert(Same<Decay<Foo[3]>, Foo*>, "Foo[3]");

    // ─────────────────────────────────────────────────────────────
    // 5. Unbounded arrays
    //    Same rule: pointer to element type.
    // ─────────────────────────────────────────────────────────────
    
    static_assert(Same<Decay<int[]>, int*>, "int[]");
    static_assert(Same<Decay<const int[]>, const int*>, "const int[]");
    static_assert(Same<Decay<Foo[]>, Foo*>, "Foo[]");

    // ─────────────────────────────────────────────────────────────
    // 6. References to arrays
    //    Strip the reference first, then apply the array-to-pointer rule.
    // ─────────────────────────────────────────────────────────────
    
    static_assert(Same<Decay<int(&)[5]>, int*>, "int(&)[5]");
    static_assert(Same<Decay<int(&&)[5]>, int*>, "int(&&)[5]");
    static_assert(Same<Decay<const int(&)[5]>, const int*>, "const int(&)[5]");

    // ─────────────────────────────────────────────────────────────
    // 7. Function types
    //    A function type decays to a pointer to that function.
    // ─────────────────────────────────────────────────────────────

    static_assert(Same<Decay<void()>, void(*)()>, "void()");
    static_assert(Same<Decay<int(float)>, int(*)(float)>, "int(float)");
    static_assert(Same<Decay<void(int, float)>, void(*)(int, float)>, "void(int, float)");
    static_assert(Same<Decay<int(...)>, int(*)(...)>, "C-variadic fn");

    // A function *pointer* is NOT a function type; it receives the plain type rules.

    static_assert(Same<Decay<void(*)()>, void(*)()>, "fn ptr unchanged");
    static_assert(Same<Decay<void(* const)()>, void(*)()>, "const fn ptr → fn ptr");

    // ─────────────────────────────────────────────────────────────
    // 8. References to function types
    //    Strip the reference first, then apply the function-to-pointer rule.
    // ─────────────────────────────────────────────────────────────

    static_assert(Same<Decay<void(&)()>, void(*)()>, "fn lvalue ref → fn ptr");
    static_assert(Same<Decay<void(&&)()>, void(*)()>, "fn rvalue ref → fn ptr");

    // ─────────────────────────────────────────────────────────────
    // 9. Idempotency
    //    Decay of an already-decayed type must be a no-op.
    // ─────────────────────────────────────────────────────────────

    static_assert(Same<Decay<Decay<int>>, int>, "idem: int");
    static_assert(Same<Decay<Decay<const int&>>, int>, "idem: const int&");
    static_assert(Same<Decay<Decay<int[5]>>, int*>, "idem: int[5]");
    static_assert(Same<Decay<Decay<void()>>, void(*)()>, "idem: void()");

    struct Incomplete;
    return Same<Incomplete, Decay<Incomplete>>;
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