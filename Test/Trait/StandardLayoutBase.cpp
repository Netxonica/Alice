// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/StandardLayoutBase.hpp"

using Alice::Trait::StandardLayoutBase;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ----------------------------------------------------------------
    // Fixtures
    // ----------------------------------------------------------------

    struct Empty{};

    struct WithInt
    {
        int x;
    };

    struct WithChar
    {
        char c;
    };

    // Direct, single-base standard-layout chains.

    struct DerivedEmpty : Empty{};

    struct DerivedEmptyWithMember : Empty
    {
        int y;
    };

    struct DerivedWithInt : WithInt{};

    struct DeepDerived : DerivedWithInt{};   // three-level chain

    // Completely unrelated type.

    struct Unrelated
    {
        int z;
    };

    // Not standard-layout: virtual member function introduces a vtable pointer
    // at offset 0, displacing any base subobject.

    struct HasVirtualFn : WithInt
    {
        virtual ~HasVirtualFn() = default;
    };

    // Not standard-layout: virtual base class.

    struct HasVirtualBase : virtual Empty{};

    // ================================================================
    // Positive: Self == Derived
    // The standard guarantees a type is pointer-interconvertible with itself.
    // ================================================================

    static_assert(StandardLayoutBase<Empty, Empty>);
    static_assert(StandardLayoutBase<WithInt, WithInt>);
    static_assert(StandardLayoutBase<DerivedWithInt, DerivedWithInt>);
    static_assert(StandardLayoutBase<DeepDerived, DeepDerived>);

    // ================================================================
    // Positive: direct standard-layout base → derived relationships.
    // ================================================================

    static_assert(StandardLayoutBase<Empty, DerivedEmpty>);
    static_assert(StandardLayoutBase<Empty, DerivedEmptyWithMember>);
    static_assert(StandardLayoutBase<WithInt, DerivedWithInt>);

    // ================================================================
    // Positive: transitivity.
    // A standard-layout ancestor reachable via a pointer-interconvertible
    // chain is itself pointer-interconvertible with the leaf type.
    // ================================================================

    static_assert(StandardLayoutBase<WithInt, DeepDerived>);
    static_assert(StandardLayoutBase<DerivedWithInt, DeepDerived>);

    // ================================================================
    // Negative: no inheritance relationship at all.
    // ================================================================

    static_assert(not StandardLayoutBase<WithInt, Unrelated>);
    static_assert(not StandardLayoutBase<Unrelated, WithInt>);
    static_assert(not StandardLayoutBase<Empty, Unrelated>);
    static_assert(not StandardLayoutBase<WithInt, WithChar>);

    // ================================================================
    // Negative: arguments in the wrong order (Derived supplied as Self).
    // ================================================================

    static_assert(not StandardLayoutBase<DerivedEmpty, Empty>);
    static_assert(not StandardLayoutBase<DerivedWithInt, WithInt>);
    static_assert(not StandardLayoutBase<DeepDerived, WithInt>);

    // ================================================================
    // Negative: Derived is not standard-layout due to a virtual function.
    // The vtable pointer occupies offset 0, so the base subobject is
    // no longer pointer-interconvertible with the derived object.
    // ================================================================

    static_assert(not StandardLayoutBase<WithInt, HasVirtualFn>);

    // ================================================================
    // Negative: Derived is not standard-layout due to virtual inheritance.
    // ================================================================

    static_assert(not StandardLayoutBase<Empty, HasVirtualBase>);

    struct Incomplete;
    return not StandardLayoutBase<Incomplete, Incomplete>;
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