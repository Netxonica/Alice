// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyDefaultConstructible.hpp"

using Alice::Trait::TriviallyDefaultConstructible;

struct NonTrivialMember
{
    NonTrivialMember(){}
};

struct HostsNonTrivial
{
    NonTrivialMember m;
};

struct DeletedCtor
{
    DeletedCtor() = delete;
};

struct UserProvidedCtor
{
    UserProvidedCtor(){}
};

struct UserProvidedCtorInit
{
    UserProvidedCtorInit() : x(0){}
    
    int x;
};

struct Empty{};

struct ScalarMembers
{
    int x;
    
    float y;
    
    double z;
};

struct NestedTrivial
{
    Empty e;
    
    ScalarMembers s;
};

struct DefaultedCtor
{
    DefaultedCtor() = default;
    
    int x;
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Positive: scalars

    static_assert(TriviallyDefaultConstructible<bool>);
    static_assert(TriviallyDefaultConstructible<char>);
    static_assert(TriviallyDefaultConstructible<int>);
    static_assert(TriviallyDefaultConstructible<long>);
    static_assert(TriviallyDefaultConstructible<float>);
    static_assert(TriviallyDefaultConstructible<double>);
    static_assert(TriviallyDefaultConstructible<int*>);
    static_assert(TriviallyDefaultConstructible<const int*>);

    // Positive: arrays of trivial types

    static_assert(TriviallyDefaultConstructible<int[8]>);
    static_assert(TriviallyDefaultConstructible<float[4][4]>);

    // Positive: trivial aggregate structs

    static_assert(TriviallyDefaultConstructible<Empty>);
    static_assert(TriviallyDefaultConstructible<ScalarMembers>);
    static_assert(TriviallyDefaultConstructible<NestedTrivial>);
    static_assert(TriviallyDefaultConstructible<DefaultedCtor>);

    // Negative: user-provided default constructor

    static_assert(not TriviallyDefaultConstructible<UserProvidedCtor>);
    static_assert(not TriviallyDefaultConstructible<UserProvidedCtorInit>);

    // Negative: deleted default constructor

    static_assert(not TriviallyDefaultConstructible<DeletedCtor>);

    // Negative: member with non-trivial constructor forces parent to be non-trivial

    static_assert(not TriviallyDefaultConstructible<NonTrivialMember>);
    static_assert(not TriviallyDefaultConstructible<HostsNonTrivial>);

    // Negative: references and void are never default-constructible

    static_assert(not TriviallyDefaultConstructible<int&>);
    static_assert(not TriviallyDefaultConstructible<const int&>);
    static_assert(not TriviallyDefaultConstructible<void>);

    struct Incomplete;
    return not TriviallyDefaultConstructible<Incomplete>;
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