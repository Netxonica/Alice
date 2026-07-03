// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Destructible.hpp"

using Alice::Trait::Destructible;

// ---------------------------------------------------------------------------
// Fixture types
// ---------------------------------------------------------------------------

struct Trivial{};

struct WithUserDtor
{
    ~WithUserDtor(){}
};

struct WithNoexceptDtor
{
    ~WithNoexceptDtor() noexcept{}
};

struct Base
{
    virtual ~Base() noexcept{}
};

struct Derived : Base
{
    ~Derived() noexcept override{}
};

union TrivialUnion
{
    int a;

    float b;
};

struct Empty{};

struct HasDestructibleMember
{
    Trivial m;
};

struct DeletedDtor
{
    ~DeletedDtor() = delete;
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------------------
    // Positive cases
    // ---------------------------------------------------------------------------

    static_assert(Destructible<Trivial>);
    static_assert(Destructible<WithUserDtor>);
    static_assert(Destructible<WithNoexceptDtor>);
    static_assert(Destructible<Base>);
    static_assert(Destructible<Derived>);
    static_assert(Destructible<TrivialUnion>);
    static_assert(Destructible<Empty>);
    static_assert(Destructible<HasDestructibleMember>);

    // Fundamental types
    
    static_assert(Destructible<int>);
    static_assert(Destructible<unsigned long long>);
    static_assert(Destructible<float>);
    static_assert(Destructible<double>);
    static_assert(Destructible<bool>);
    static_assert(Destructible<char>);
    static_assert(Destructible<void*>);
    static_assert(Destructible<int*>);
    static_assert(Destructible<int(*)(int)>);

    // cvref-qualified

    static_assert(Destructible<const int>);
    static_assert(Destructible<volatile int>);
    static_assert(Destructible<const volatile Trivial>);
    static_assert(Destructible<int&>);
    static_assert(Destructible<int&&>);

    // ---------------------------------------------------------------------------
    // Negative cases
    // ---------------------------------------------------------------------------

    static_assert(not Destructible<DeletedDtor>);
    static_assert(not Destructible<void>);
    static_assert(not Destructible<int[]>);

    struct Incomplete;
    return not Destructible<Incomplete>;
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