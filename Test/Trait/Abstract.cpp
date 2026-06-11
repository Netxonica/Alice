// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Abstract.hpp"

using Alice::Trait::Abstract;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Fixture types ─────────────────────────────────────────────────────────────

    struct SinglePureVirtual
    {
        virtual void Foo() = 0;
    };

    struct TwoPureVirtuals
    {
        virtual void Foo() = 0;
        
        virtual void Bar() = 0;
    };

    struct PureVirtualDtor
    {
        virtual ~PureVirtualDtor() = 0;
    };

    struct MixedVirtuals
    {
        virtual void Foo() = 0;
        
        virtual void Bar(){}
    };

    struct InheritedAbstract : SinglePureVirtual{};
    struct ExtendedAbstract : SinglePureVirtual
    {
        virtual void Baz() = 0;
    };

    struct PartialOverride : TwoPureVirtuals
    {
        void Foo() override{}
    };

    struct ConcreteImpl : SinglePureVirtual
    {
        void Foo() override{}
    };

    struct PlainClass{};

    struct NonPureVirtualOnly
    {
        virtual void Foo(){}
    };

    union PlainUnion
    {
        int X;
        
        float Y;
    };

    enum PlainEnum
    {
        EnumA,
        EnumB
    };

    enum class ScopedEnum
    {
        X,
        Y
    };

    // ── True: concept must hold ───────────────────────────────────────────────────

    static_assert(Abstract<SinglePureVirtual>); // single pure virtual
    static_assert(Abstract<TwoPureVirtuals>); // multiple pure virtuals
    static_assert(Abstract<PureVirtualDtor>); // pure virtual destructor
    static_assert(Abstract<MixedVirtuals>); // at least one pure virtual
    static_assert(Abstract<InheritedAbstract>); // inherited, never overridden
    static_assert(Abstract<ExtendedAbstract>); // inherited + more declared
    static_assert(Abstract<PartialOverride>); // some, not all, overridden
    static_assert(Abstract<const SinglePureVirtual>); // const-qualified
    static_assert(Abstract<volatile TwoPureVirtuals>); // volatile-qualified

    // ── False: concept must not hold ─────────────────────────────────────────────

    // class types that are not abstract

    static_assert(not Abstract<ConcreteImpl>); // every pure virtual overridden
    static_assert(not Abstract<PlainClass>); // no virtual functions at all
    static_assert(not Abstract<NonPureVirtualOnly>); // no pure virtual

    // non-class types
    
    static_assert(not Abstract<PlainUnion>); // union
    static_assert(not Abstract<PlainEnum>); // unscoped enum
    static_assert(not Abstract<ScopedEnum>); // scoped enum

    // fundamental types

    static_assert(not Abstract<void>);
    static_assert(not Abstract<bool>);
    static_assert(not Abstract<int>);
    static_assert(not Abstract<float>);
    static_assert(not Abstract<double>);

    // derived types

    static_assert(not Abstract<SinglePureVirtual*>); // pointer to abstract class
    static_assert(not Abstract<SinglePureVirtual&>); // reference to abstract class
    static_assert(not Abstract<int*>); // pointer to fundamental
    static_assert(not Abstract<int[4]>); // array of fundamental

    struct Incomplete;
    return not Abstract<Incomplete>;
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