// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Core/Unevaluated.hpp"

using Alice::Trait::Same;
using Alice::Unevaluated;

// Binary operator detection.
template<class T, class U> concept Addable = requires
{
    Unevaluated<T>() + Unevaluated<U>();
};

// Nullary member-function detection.
template<class T> concept HasFoo = requires
{
    Unevaluated<T>().foo();
};

// Member-function detection with a forwarded argument — Unevaluated used for both.
template<class T> concept HasBar = requires
{
    Unevaluated<T>().bar(Unevaluated<int>());
};

// Unary operator detection.
template<class T> concept Dereferenceable = requires
{
    *Unevaluated<T>();
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ============================================================
    // Auxiliary types
    // ============================================================

    struct NonDefaultConstructible
    {
        NonDefaultConstructible() = delete;
    };

    struct Abstract
    {
        virtual void method() = 0;

        virtual ~Abstract(){}
    };

    struct WithFoo
    {
        int foo();
    };

    struct WithBar
    {
        double bar(int);
    };

    struct PlainStruct{};

    struct Incomplete; // forward-declared only; never defined

    // ============================================================
    // Group 1 — Return type is exactly Self&& for non-reference types
    // ============================================================

    static_assert(Same<decltype(Unevaluated<int>()), int&&>);
    static_assert(Same<decltype(Unevaluated<float>()), float&&>);
    static_assert(Same<decltype(Unevaluated<double>()), double&&>);
    static_assert(Same<decltype(Unevaluated<bool>()), bool&&>);
    static_assert(Same<decltype(Unevaluated<char>()), char&&>);

    // ============================================================
    // Group 2 — CV qualifiers are preserved
    // ============================================================

    static_assert(Same<decltype(Unevaluated<const int>()), const int&&>);
    static_assert(Same<decltype(Unevaluated<volatile int>()), volatile int&&>);
    static_assert(Same<decltype(Unevaluated<const volatile int>()), const volatile int&&>);

    // ============================================================
    // Group 3 — Reference collapsing:  T&  && → T&,   T&& && → T&&
    // ============================================================

    static_assert(Same<decltype(Unevaluated<int&>()), int&>);
    static_assert(Same<decltype(Unevaluated<const int&>()), const int&>);
    static_assert(Same<decltype(Unevaluated<int&&>()), int&&>);
    static_assert(Same<decltype(Unevaluated<const int&&>()), const int&&>);

    // ============================================================
    // Group 4 — Compound types (pointers, multi-level pointers, arrays)
    // ============================================================

    static_assert(Same<decltype(Unevaluated<int*>()), int*&&>);
    static_assert(Same<decltype(Unevaluated<int**>()), int**&&>);
    static_assert(Same<decltype(Unevaluated<int[3]>()), int(&&)[3]>);
    static_assert(Same<decltype(Unevaluated<int[2][4]>()), int(&&)[2][4]>);

    // ============================================================
    // Group 5 — Non-constructible, abstract, and incomplete types
    //           (the core value-proposition: no constructor required)
    // ============================================================

    static_assert(Same<decltype(Unevaluated<NonDefaultConstructible>()), NonDefaultConstructible&&>
    );
    static_assert(Same<decltype(Unevaluated<Abstract>()), Abstract&&>);
    static_assert(Same<decltype(Unevaluated<Incomplete>()), Incomplete&&>);

    // ============================================================
    // Group 6 — noexcept specifier is respected
    // ============================================================

    static_assert(noexcept(Unevaluated<int>()));
    static_assert(noexcept(Unevaluated<NonDefaultConstructible>()));
    static_assert(noexcept(Unevaluated<Abstract>()));

    // ============================================================
    // Group 7 — sizeof (unevaluated context; references stripped)
    // ============================================================

    // Size of the referenced type is preserved.

    static_assert(sizeof(Unevaluated<int>()) == sizeof(int));
    static_assert(sizeof(Unevaluated<double>()) == sizeof(double));

    // Lvalue-ref and rvalue-ref to the same type yield identical sizeof.

    static_assert(sizeof(Unevaluated<int&>()) == sizeof(Unevaluated<int&&>()));

    // ============================================================
    // Group 8 — Primary use-case: concepts / requires expressions
    //           (Unevaluated supplies "instances" without construction)
    // ============================================================

    static_assert(Addable<int, int>);
    static_assert(Addable<float, double>);
    static_assert(not Addable<PlainStruct, PlainStruct>);

    static_assert(HasFoo<WithFoo>);
    static_assert(not HasFoo<PlainStruct>);
    static_assert(not HasFoo<int>);

    static_assert(HasBar<WithBar>);
    static_assert(not HasBar<WithFoo>);
    static_assert(not HasBar<int>);

    static_assert(Dereferenceable<int*>);
    static_assert(not Dereferenceable<int>);
    static_assert(not Dereferenceable<PlainStruct>);

    return Same<Incomplete&&, decltype(Unevaluated<Incomplete>())>;
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