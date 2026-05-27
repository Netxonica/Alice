// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Convertible.hpp"

using Alice::Trait::Convertible;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Positive cases ─────────────────────────────────────────────────────────

    // Arithmetic conversions – both sides are Sized, static_cast is well-formed

    static_assert(Convertible<int, float>, "int -> float");
    static_assert(Convertible<float, int>, "float -> int");
    static_assert(Convertible<int, double>, "int -> double");
    static_assert(Convertible<double, long>, "double -> long");
    static_assert(Convertible<char, int>, "char -> int");
    static_assert(Convertible<int, int>, "int  -> int (identity)");

    // Enum to its underlying integer type
    
    enum Colour
    {
        Red,
        Green,
        Blue
    };

    static_assert(Convertible<Colour, int>, "Colour -> int");

    // Pointer up-cast (Derived* -> Base*) is valid for static_cast

    struct Base{};

    struct Child : Base{};

    static_assert(Convertible<Child*, Base*>, "Child* -> Base* (up-cast)");
    static_assert(Convertible<Child*, const Base*>, "Child* -> const Base*");
    static_assert(Convertible<int*, const int*>, "int* -> const int* (const-adding)");
    static_assert(Convertible<int*, int*>, "int* -> int* (pointer identity)");

    // ── Negative cases ──────────────────────────────────────────────────────────

    // void is not Sized → Cast must be false regardless of the other side
    
    static_assert(not Convertible<void, int>, "void -> int:  void is not Sized");
    static_assert(not Convertible<int, void>, "int -> void: void is not Sized");
    static_assert(not Convertible<void, void>, "void -> void: neither are Sized");

    // static_cast between pointers to unrelated, non-void types is ill-formed
    
    struct Unrelated{};

    static_assert(not Convertible<Child*, Unrelated*>,
    "Child* -> Unrelated*: no inheritance relation");
    static_assert(not Convertible<int*, float*>, "int* -> float*: unrelated pointer types");

    struct Incomplete;
    return not Convertible<Incomplete, Incomplete>;
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