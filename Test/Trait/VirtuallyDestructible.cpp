// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/VirtuallyDestructible.hpp"

using Alice::Trait::VirtuallyDestructible;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─── Positive fixtures ────────────────────────────────────────────────────────

    // Defaulted virtual destructor.
    
    struct WithVirtualDefault
    {
        virtual ~WithVirtualDefault() = default;
    };

    // Explicitly defined virtual destructor body.
    
    struct WithVirtualExplicit
    {
        virtual ~WithVirtualExplicit(){}
    };

    // Pure-virtual destructor: the type is still virtually destructible.
    
    struct WithPureVirtual
    {
        virtual ~WithPureVirtual() = 0;
    };

    // Virtual destructor inherited from a base class.
    
    struct DerivedFromVirtual : WithVirtualDefault{};

    // `final` does not remove virtual-ness.
    
    struct FinalDerived final : WithVirtualDefault{};

    // ─── Negative fixtures ────────────────────────────────────────────────────────

    // Implicitly generated, non-virtual destructor.

    struct Empty{};

    // Explicitly defaulted non-virtual destructor.

    struct WithNonVirtualDefault
    {
        ~WithNonVirtualDefault() = default;
    };

    // User-defined non-virtual destructor body.

    struct WithNonVirtualExplicit
    {
        ~WithNonVirtualExplicit(){}
    };

    // Unions cannot have virtual functions at all.

    union SomeUnion
    {
        int i;
        
        float f;
    };

    // ─── Positive assertions ──────────────────────────────────────────────────────

    static_assert(VirtuallyDestructible<WithVirtualDefault>);
    static_assert(VirtuallyDestructible<WithVirtualExplicit>);
    static_assert(VirtuallyDestructible<WithPureVirtual>);
    static_assert(VirtuallyDestructible<DerivedFromVirtual>);
    static_assert(VirtuallyDestructible<FinalDerived>);

    // cv-qualification must not obscure a virtual destructor.

    static_assert(VirtuallyDestructible<const WithVirtualDefault>);
    static_assert(VirtuallyDestructible<volatile WithVirtualDefault>);
    static_assert(VirtuallyDestructible<const volatile WithVirtualDefault>);

    // ─── Negative assertions ──────────────────────────────────────────────────────

    // Class/struct types whose destructor is non-virtual or absent.
    
    static_assert(not VirtuallyDestructible<Empty>);
    static_assert(not VirtuallyDestructible<WithNonVirtualDefault>);
    static_assert(not VirtuallyDestructible<WithNonVirtualExplicit>);
    static_assert(not VirtuallyDestructible<SomeUnion>);

    // Scalar types never have virtual destructors.
    
    static_assert(not VirtuallyDestructible<int>);
    static_assert(not VirtuallyDestructible<float>);
    static_assert(not VirtuallyDestructible<char>);
    static_assert(not VirtuallyDestructible<bool>);

    // A pointer or reference to a virtually-destructible type is not itself
    // virtually destructible — the concept must not be satisfied transitively.
    
    static_assert(not VirtuallyDestructible<WithVirtualDefault*>);
    static_assert(not VirtuallyDestructible<WithVirtualDefault&>);

    struct Incomplete;
    return not VirtuallyDestructible<Incomplete>;
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