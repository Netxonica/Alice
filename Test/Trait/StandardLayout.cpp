// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/StandardLayout.hpp"

using Alice::Trait::StandardLayout;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // =========================================================================
    // Standard-layout: scalar types (fundamental, cv-qualified, pointers,
    // nullptr_t, enumerations)
    // =========================================================================

    static_assert(StandardLayout<bool>);
    static_assert(StandardLayout<char>);
    static_assert(StandardLayout<int>);
    static_assert(StandardLayout<long>);
    static_assert(StandardLayout<unsigned int>);
    static_assert(StandardLayout<float>);
    static_assert(StandardLayout<double>);
    static_assert(StandardLayout<const int>);
    static_assert(StandardLayout<volatile float>);
    static_assert(StandardLayout<const volatile double>);
    static_assert(StandardLayout<int*>);
    static_assert(StandardLayout<void*>);
    static_assert(StandardLayout<const char*>);
    static_assert(StandardLayout<int**>);           // pointer-to-pointer is still scalar
    static_assert(StandardLayout<decltype(nullptr)>);

    enum PlainEnum
    {
        PeA,
        PeB
    };

    enum class ScopedEnum : int
    {
        SeA,
        SeB
    };

    static_assert(StandardLayout<PlainEnum>);
    static_assert(StandardLayout<ScopedEnum>);

    // =========================================================================
    // Standard-layout: arrays of standard-layout element types
    // =========================================================================

    static_assert(StandardLayout<int[8]>);
    static_assert(StandardLayout<float[3][3]>);

    // =========================================================================
    // Standard-layout: struct / class types
    // =========================================================================

    // Empty struct — vacuously satisfies every condition.

    struct Empty{};

    static_assert(StandardLayout<Empty>);

    // Trivially POD-like: same access control, no virtual, no references.

    struct Pod
    {
        int x;
        
        float y;
        
        double z;
    };

    static_assert(StandardLayout<Pod>);
    static_assert(StandardLayout<const Pod>);       // cv-qualified struct is still standard-layout

    // 'class' with all-public members — access is uniform.

    class AllPublic
    {
    public:
        int x, y;
    };

    static_assert(StandardLayout<AllPublic>);

    // 'struct' with all-private members — access is uniform.

    struct AllPrivate
    {
    private:
        [[maybe_unused]] int x, y;
    };

    static_assert(StandardLayout<AllPrivate>);

    // Nested standard-layout types.

    struct Inner
    {
        int a;
        
        char b;
    };

    struct Outer
    {
        Inner i;
        
        float f;
    };

    static_assert(StandardLayout<Inner>);
    static_assert(StandardLayout<Outer>);

    // Function-pointer member — function pointers are scalar, so this qualifies.

    struct WithFuncPtr
    {
        void (*callback)(int);
    };

    static_assert(StandardLayout<WithFuncPtr>);

    // Derived class adds members; the (empty) base has none → standard-layout.

    struct EmptyBase{};

    struct DerivedFromEmpty : EmptyBase
    {
        int value;
    };

    static_assert(StandardLayout<DerivedFromEmpty>);

    // Derived class adds no members; exactly one base carries non-static data →
    // satisfies "[at most] one base class with non-static data members".

    struct BaseWithMember
    {
        int x;
    };

    struct DerivedWithNoMembers : BaseWithMember{};

    static_assert(StandardLayout<DerivedWithNoMembers>);

    // =========================================================================
    // NOT standard-layout
    // =========================================================================

    // Virtual member function introduces a vptr.

    struct WithVirtualMethod
    {
        virtual void foo() = 0;

        virtual ~WithVirtualMethod(){}
    };

    static_assert(not StandardLayout<WithVirtualMethod>);

    // Virtual destructor also introduces a vptr.

    struct WithVirtualDtor
    {
        virtual ~WithVirtualDtor() = default;
    };

    static_assert(not StandardLayout<WithVirtualDtor>);

    // Virtual base class.

    struct VBase
    {
        int x;
    };

    struct WithVirtualBase : virtual VBase{};

    static_assert(not StandardLayout<WithVirtualBase>);

    // Mixed access control within the same class.

    struct MixedAccess
    {
        int x;
    private:
        [[maybe_unused]] int y;
    };

    static_assert(not StandardLayout<MixedAccess>);

    // Reference data member — explicitly excluded by [class.prop] in the standard.

    struct WithReference
    {
        int& ref;
    };

    static_assert(not StandardLayout<WithReference>);

    // Two bases both carrying non-static data members violates the
    // "at most one base class with non-static data members" rule.
    struct BasePair1
    {
        int a;
    };

    struct BasePair2
    {
        int b;
    };

    struct MultiBaseWithData : BasePair1, BasePair2{};

    static_assert(not StandardLayout<MultiBaseWithData>);

    // A non-standard-layout base taints the derived class.

    struct DerivedFromNonStd : WithVirtualMethod
    {
        int extra;
    };

    static_assert(not StandardLayout<DerivedFromNonStd>);

    struct Incomplete;
    return not StandardLayout<Incomplete>;
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