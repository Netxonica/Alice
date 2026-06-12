// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/DirectMaterializable.hpp"

using Alice::Trait::DirectMaterializable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------------------
    // Helper types
    // ---------------------------------------------------------------------------

    struct Opaque{};

    struct Base{};

    struct Derived : Base{};

    struct WithConv
    {
        constexpr operator int() const noexcept
        {
            return 0;
        }
    };

    // ===========================================================================
    // Positive — a temporary is materialised when binding Self from Temporary
    // ===========================================================================

    // Const lvalue reference from a prvalue of the exact same type.

    static_assert(DirectMaterializable<const int&, int>);

    // Const lvalue reference from a prvalue via arithmetic conversion
    // (a fresh int temporary holds the narrowed value).
    
    static_assert(DirectMaterializable<const int&, double>);

    // Rvalue reference from a prvalue of the same type.
    
    static_assert(DirectMaterializable<int&&, int>);

    // Rvalue reference from a prvalue of a convertible type
    // (double → temporary int materialised; rvalue ref extends its lifetime).
    
    static_assert(DirectMaterializable<int&&, double>);

    // Const lvalue reference to a UDT from a prvalue of the same UDT.
    
    static_assert(DirectMaterializable<const Opaque&, Opaque>);

    // Const lvalue reference from a prvalue produced by a user-defined conversion.
    
    static_assert(DirectMaterializable<const int&, WithConv>);

    // Const base-class lvalue reference from a derived prvalue.
    // Slicing materialises a fresh Base temporary; the reference extends its lifetime.
    
    static_assert(DirectMaterializable<const Base&, Derived>);

    // ===========================================================================
    // Negative — no temporary is materialised, or Self is not a reference type
    // ===========================================================================

    // Self is a non-reference type: the trait is inapplicable by definition.
    
    static_assert(not DirectMaterializable<int, int>);

    // Non-const lvalue reference: cannot bind to a temporary.
    
    static_assert(not DirectMaterializable<int&, int>);

    // Const lvalue reference from an lvalue reference: binds to the
    // pre-existing object without creating any temporary.
    
    static_assert(not DirectMaterializable<const int&, int&>);

    // Same as above, but the source reference is itself const.
    
    static_assert(not DirectMaterializable<const int&, const int&>);

    // Rvalue reference from an lvalue reference: the binding is ill-formed,
    // so no temporary is involved.
    
    static_assert(not DirectMaterializable<int&&, int&>);

    // Rvalue reference from an rvalue reference: merely extends the lifetime
    // of the already-existing referred-to object; no fresh temporary.
    
    static_assert(not DirectMaterializable<int&&, int&&>);

    // Const lvalue reference from a completely unrelated, non-convertible type.
    
    static_assert(not DirectMaterializable<const Opaque&, int>);

    // Const lvalue reference from a type whose conversion goes the other way.
    
    static_assert(not DirectMaterializable<const WithConv&, Opaque>);

    struct Incomplete;
    return not DirectMaterializable<Incomplete, Incomplete>;
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