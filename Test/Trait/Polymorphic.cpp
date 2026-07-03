// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Polymorphic.hpp"

using Alice::Trait::Polymorphic;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─── Test types ───────────────────────────────────────────────────────────────

    // Positive group ──────────────────────────────────────────────────────────────

    // Owns a regular virtual member function.
    
    struct WithVirtualMethod
    {
        virtual void f(){}

        virtual ~WithVirtualMethod(){}
    };

    // Owns a pure-virtual member function (abstract class).

    struct WithPureVirtual
    {
        virtual void f() = 0;

        virtual ~WithPureVirtual(){}
    };

    // Has only a virtual destructor — the minimal polymorphic surface.
    
    struct WithVirtualDtor
    {
        virtual ~WithVirtualDtor(){}
    };

    // Inherits a virtual without re-declaring it at all.
    
    struct DerivedSilent : WithVirtualMethod{};

    // Inherits and explicitly overrides the virtual.

    struct DerivedOverride : WithVirtualMethod
    {
        void f() override{}
    };

    // Two levels of inheritance — virtual must propagate transitively.

    struct GrandChild : DerivedSilent{};

    // One non-polymorphic and one polymorphic base: poly wins.

    struct PlainBase{};

    struct MixedBases : PlainBase, WithVirtualMethod{};

    // Virtual (diamond-safe) inheritance of a polymorphic base.

    struct VirtuallyInherited : virtual WithVirtualMethod{};

    // cv-qualification is transparent to __is_polymorphic.

    using ConstPoly = const WithVirtualMethod;
    using VolatilePoly = volatile WithVirtualMethod;

    // Negative group ──────────────────────────────────────────────────────────────

    // Empty class: no virtuals whatsoever.

    struct Empty{};

    // Has data members and a non-virtual method, but no virtual anything.
    
    struct OnlyData
    {
        int x;
        
        void f();
    };

    // Destructor present but explicitly non-virtual.
    
    struct NonVirtualDtor
    {
        ~NonVirtualDtor();
    };

    // Union: explicitly excluded by the concept's documented contract.
    
    union SomeUnion
    {
        int i;
        
        float f;
    };

    // Enumerations: not class types.
    
    enum PlainEnum
    {
        EnumA
    };

    enum class ScopedEnum
    {
        A
    };

    // ─── Positive assertions: must satisfy Polymorphic ───────────────────────────

    static_assert(Polymorphic<WithVirtualMethod>, "direct virtual method");
    static_assert(Polymorphic<WithPureVirtual>, "pure virtual (abstract class)");
    static_assert(Polymorphic<WithVirtualDtor>, "virtual destructor only");
    static_assert(Polymorphic<DerivedSilent>, "inherits virtual, re-declares nothing");
    static_assert(Polymorphic<DerivedOverride>, "overrides inherited virtual");
    static_assert(Polymorphic<GrandChild>, "virtual survives two inheritance levels");
    static_assert(Polymorphic<MixedBases>, "one polymorphic base among plain ones");
    static_assert(Polymorphic<VirtuallyInherited>, "virtually-inherited polymorphic base");
    static_assert(Polymorphic<ConstPoly>, "const qualification is transparent");
    static_assert(Polymorphic<VolatilePoly>, "volatile qualification is transparent");

    // ─── Negative assertions: must not satisfy Polymorphic ───────────────────────

    static_assert(not Polymorphic<Empty>, "empty class");
    static_assert(not Polymorphic<OnlyData>, "data and non-virtual methods only");
    static_assert(not Polymorphic<NonVirtualDtor>, "non-virtual destructor");
    static_assert(not Polymorphic<SomeUnion>, "union — excluded by contract");
    static_assert(not Polymorphic<int>, "built-in int");
    static_assert(not Polymorphic<float>, "built-in float");
    static_assert(not Polymorphic<bool>, "built-in bool");
    static_assert(not Polymorphic<int*>, "pointer to scalar");
    static_assert(not Polymorphic<WithVirtualMethod*>,
    "pointer to polymorphic type is not itself polymorphic");
    static_assert(not Polymorphic<PlainEnum>, "unscoped enum");
    static_assert(not Polymorphic<ScopedEnum>, "scoped enum");

    struct Incomplete;
    return not Polymorphic<Incomplete>;
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