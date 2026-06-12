// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/CopyMaterializable.hpp"

using Alice::Trait::CopyMaterializable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Helper types for user-defined-conversion tests ────────────────────────
    //
    //   Source  ──[Target(Source const&)]──►  Target
    //
    // `Unrelated` has no conversion to or from the others.

    struct Source{};

    struct Target
    {
        Target(Source const&) noexcept;
    };  // implicit; intentionally not `explicit`

    struct Unrelated{};


    // ═════════════════════════════════════════════════════════════════════════
    // TRUE — Self is a reference type that binds to a materialised temporary
    // ═════════════════════════════════════════════════════════════════════════

    // const lvalue reference ← same-type prvalue

    static_assert(CopyMaterializable<int const&, int>);

    // rvalue reference ← same-type prvalue

    static_assert(CopyMaterializable<int&&, int>);

    // const lvalue reference ← prvalue of a widening-converted type
    //   (a temporary of the wider type is materialised)

    static_assert(CopyMaterializable<long const&, int>);
    static_assert(CopyMaterializable<double const&, float>);

    // rvalue reference ← prvalue of a widening-converted type

    static_assert(CopyMaterializable<long&&, int>);
    static_assert(CopyMaterializable<double&&, float>);

    // const lvalue reference ← prvalue of a narrowing-converted type
    //   (narrowing still materialises a temporary — the reference binding is valid)

    static_assert(CopyMaterializable<int const&, double>);

    // const lvalue reference ← lvalue of a *different* type
    //   Although Temporary is an lvalue here, the implicit conversion to Self's referent
    //   type creates a fresh temporary (unlike the same-type case which binds directly).

    static_assert(CopyMaterializable<long const&, int const&>);

    // const lvalue reference ← xvalue of a *different* type
    //   Same reasoning: the type mismatch forces a conversion, materialising a temporary.

    static_assert(CopyMaterializable<long const&, int&&>);

    // user-defined conversion: Source prvalue is converted to a temporary Target

    static_assert(CopyMaterializable<Target const&, Source>);
    static_assert(CopyMaterializable<Target&&, Source>);


    // ═════════════════════════════════════════════════════════════════════════
    // FALSE — no temporary is materialised, or the initialisation is ill-formed
    // ═════════════════════════════════════════════════════════════════════════

    // ── Non-reference Self types are never satisfied ──────────────────────────
    
    static_assert(not CopyMaterializable<int, int>);
    static_assert(not CopyMaterializable<int, double>);
    static_assert(not CopyMaterializable<double, double>);

    // ── Pointer types are not reference types ─────────────────────────────────

    static_assert(not CopyMaterializable<int*, int>);

    // ── Lvalue references that cannot bind to a prvalue (ill-formed) ──────────
    //   A non-const lvalue reference cannot bind to an rvalue.

    static_assert(not CopyMaterializable<int&, int>);

    //   A volatile-only (non-const) lvalue reference cannot bind to an rvalue.

    static_assert(not CopyMaterializable<int volatile&, int>);

    //   A const volatile lvalue reference: the volatile qualifier prevents binding
    //   to a temporary (only `const T&` and `T&&` may bind to temporaries).

    static_assert(not CopyMaterializable<int const volatile&, int>);

    // ── Same-type direct bindings: no temporary is materialised ──────────────
    //   const lvalue reference ← lvalue of the *same* type
    
    static_assert(not CopyMaterializable<int const&, int&>);
    static_assert(not CopyMaterializable<int const&, int const&>);
    
    //   const lvalue reference ← xvalue of the same type
    //   (the reference binds to the existing object; no new temporary is created)
    
    static_assert(not CopyMaterializable<int const&, int&&>);
    
    //   rvalue reference ← xvalue of the same type
    
    static_assert(not CopyMaterializable<int&&, int&&>);

    // ── Rvalue reference ← lvalue (always ill-formed) ────────────────────────
    
    static_assert(not CopyMaterializable<int&&, int&>);

    // ── No viable conversion: the initialisation is ill-formed ───────────────
    
    static_assert(not CopyMaterializable<Target const&, Unrelated>);
    static_assert(not CopyMaterializable<Target&&, Unrelated>);

    struct Incomplete;
    return not CopyMaterializable<Incomplete, Incomplete>;
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