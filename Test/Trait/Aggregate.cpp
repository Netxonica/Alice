// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Aggregate.hpp"

using Alice::Trait::Aggregate;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Positive fixtures (must satisfy Aggregate) ────────────────────────────────

    // Plain struct: all public data members, no special members.
    
    struct PlainStruct
    {
        int x, y;
    };

    // Empty struct.

    struct EmptyStruct{};

    // Struct that inherits from a public, non-virtual base (allowed since C++17).
    struct BaseStruct
    {
        int value;
    };

    struct DerivedStruct : BaseStruct
    {
        int extra;
    };

    // Default member initialiser is fine since C++14.

    struct WithDefaultMember
    {
        int x = 42;
    };

    // Union with no user-declared constructors.

    union SimpleUnion
    {
        int i;
        
        float f;
    };

    // Raw array.

    using IntArray = int[3];

    // ── Negative fixtures (must NOT satisfy Aggregate) ────────────────────────────

    // User-defined (body) constructor.

    struct WithBodyCtor
    {
        WithBodyCtor(){}
    };

    // Explicitly-defaulted constructor counts as user-declared since C++20.

    struct WithDefaultedCtor
    {
        WithDefaultedCtor() = default;
    };

    // Explicitly-deleted constructor also counts as user-declared since C++20.
    
    struct WithDeletedCtor
    {
        WithDeletedCtor() = delete;
    };

    // Inherited constructors disqualify a type as well.
    
    struct BaseWithCtor
    {
        explicit BaseWithCtor(int){}
    };
    
    struct WithInheritedCtor : BaseWithCtor
    {
        using BaseWithCtor::BaseWithCtor;
    };

    // Virtual member function.

    struct WithVirtualFunc
    {
        virtual void fn(){}

        virtual ~WithVirtualFunc(){}
    };

    // Virtual base class.

    struct VirtualBase{};

    struct WithVirtualBase : virtual VirtualBase{};

    // class: data member is private by default.
    
    class ClassWithPrivateMember
    {
        [[maybe_unused]] int x;
    };

    // Explicit protected non-static data member.
    
    struct WithProtectedMember
    {
    protected:
        int x;
    };

    // Scalar types are neither arrays nor class types.
    // Pointers ditto.

    // ── Positive assertions ───────────────────────────────────────────────────────

    static_assert(Aggregate<PlainStruct>, "plain struct must be an aggregate");
    static_assert(Aggregate<EmptyStruct>, "empty struct must be an aggregate");
    static_assert(Aggregate<DerivedStruct>,
    "struct with public non-virtual base must be an aggregate");
    static_assert(Aggregate<WithDefaultMember>,
    "struct with default member initialiser must be an aggregate");
    static_assert(Aggregate<SimpleUnion>,
    "union with no user-declared constructors must be an aggregate");
    static_assert(Aggregate<IntArray>, "raw array must be an aggregate");

    // ── Negative assertions ───────────────────────────────────────────────────────

    static_assert(not Aggregate<WithBodyCtor>,
    "struct with body constructor must not be an aggregate");
    static_assert(not Aggregate<WithDefaultedCtor>,
    "struct with =default constructor must not be an aggregate (C++20 rule)");
    static_assert(not Aggregate<WithDeletedCtor>,
    "struct with =delete constructor must not be an aggregate (C++20 rule)");
    static_assert(not Aggregate<WithInheritedCtor>,
    "struct with inherited constructors must not be an aggregate");
    static_assert(not Aggregate<WithVirtualFunc>,
    "struct with virtual function must not be an aggregate");
    static_assert(not Aggregate<WithVirtualBase>,
    "struct with virtual base class must not be an aggregate");
    static_assert(not Aggregate<ClassWithPrivateMember>,
    "class with private data member must not be an aggregate");
    static_assert(not Aggregate<WithProtectedMember>,
    "struct with protected data member must not be an aggregate");
    static_assert(not Aggregate<int>, "scalar int must not be an aggregate");
    static_assert(not Aggregate<float>, "scalar float must not be an aggregate");
    static_assert(not Aggregate<int*>, "pointer type must not be an aggregate");

    struct Incomplete;
    return not Aggregate<Incomplete>;
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