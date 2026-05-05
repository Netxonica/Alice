// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyDestructible.hpp"

using Alice::Trait::TriviallyDestructible;

// --- Types under test ---

struct Trivial{};

struct TrivialWithMembers
{
    int x;

    float y;
};

struct TrivialBase{};

struct TrivialDerived : TrivialBase
{
    int value;
};

union TrivialUnion
{
    int i;

    float f;
};

struct WithUserDestructor
{
    ~WithUserDestructor(){}
};

struct WithVirtual
{
    virtual ~WithVirtual() = default;
};

struct MemberWithUserDestructor
{
    WithUserDestructor member;
};

struct NonTrivialBase
{
    virtual ~NonTrivialBase() = default;
};

struct DerivedFromNonTrivial : NonTrivialBase{};

struct ExplicitlyTrivialDestructor
{
    ~ExplicitlyTrivialDestructor() = default;
};

struct DeletedDestructor
{
    ~DeletedDestructor() = delete;
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Concept satisfaction assertions ---

    // Trivially destructible: plain struct, no user-defined destructor.
    static_assert(TriviallyDestructible<Trivial>);

    // Trivially destructible: struct with scalar members only.
    static_assert(TriviallyDestructible<TrivialWithMembers>);

    // Trivially destructible: derived struct whose entire hierarchy is trivial.
    static_assert(TriviallyDestructible<TrivialDerived>);

    // Trivially destructible: union of scalar types.
    static_assert(TriviallyDestructible<TrivialUnion>);

    // Trivially destructible: explicitly defaulted destructor is still trivial.
    static_assert(TriviallyDestructible<ExplicitlyTrivialDestructor>);

    // Trivially destructible: scalar types are always trivially destructible.
    static_assert(TriviallyDestructible<int>);
    static_assert(TriviallyDestructible<float>);
    static_assert(TriviallyDestructible<char>);
    static_assert(TriviallyDestructible<bool>);
    static_assert(TriviallyDestructible<int*>);

    // Trivially destructible: raw arrays of trivially destructible elements.
    static_assert(TriviallyDestructible<int[4]>);
    static_assert(TriviallyDestructible<Trivial[4]>);

    // Not trivially destructible: user-defined destructor body.
    static_assert(not TriviallyDestructible<WithUserDestructor>);

    // Not trivially destructible: virtual destructor introduces vtable overhead.
    static_assert(not TriviallyDestructible<WithVirtual>);

    // Not trivially destructible: member whose own destructor is non-trivial.
    static_assert(not TriviallyDestructible<MemberWithUserDestructor>);

    // Not trivially destructible: inheriting a class with a virtual destructor.
    static_assert(not TriviallyDestructible<DerivedFromNonTrivial>);

    // Not trivially destructible: deleted destructor means the type is not
    // destructible at all, which implies it cannot be *trivially* destructible.
    static_assert(not TriviallyDestructible<DeletedDestructor>);

    // --- cv-qualification invariants ---

    // The trivially-destructible property must be consistent across cv-qualifiers.
    static_assert(TriviallyDestructible<const Trivial>);
    static_assert(TriviallyDestructible<volatile Trivial>);
    static_assert(TriviallyDestructible<const volatile Trivial>);

    static_assert(not TriviallyDestructible<const WithUserDestructor>);
    static_assert(not TriviallyDestructible<volatile WithUserDestructor>);
    static_assert(not TriviallyDestructible<const volatile WithUserDestructor>);

    struct Incomplete;
    return not TriviallyDestructible<Incomplete>;
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