// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/DefaultConstructible.hpp"

using Alice::Trait::DefaultConstructible;

// --- Types that SHOULD satisfy DefaultConstructible ---

struct EmptyStruct{};

struct ExplicitDefaultCtor
{
    ExplicitDefaultCtor() = default;
};

struct TrivialMembers
{
    int x;
    float y;
};

struct UserDefinedDefaultCtor
{
    UserDefinedDefaultCtor(){}
};

struct DefaultAndOtherCtors
{
    DefaultAndOtherCtors() = default;
    
    DefaultAndOtherCtors(int){}
};

// --- Types that should NOT satisfy DefaultConstructible ---

struct DeletedDefaultCtor
{
    DeletedDefaultCtor() = delete;
};

struct UserCtorOnly
{
    UserCtorOnly(int){}
};

struct DeletedDefaultWithOtherCtor
{
    DeletedDefaultWithOtherCtor() = delete;
    
    DeletedDefaultWithOtherCtor(int){}
};

struct PrivateDefaultCtor
{
private:
    PrivateDefaultCtor() = default;
};

struct ProtectedDefaultCtor
{
protected:
    ProtectedDefaultCtor() = default;
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Static assertions: types that SHOULD satisfy ---

    static_assert(DefaultConstructible<int>);
    static_assert(DefaultConstructible<float>);
    static_assert(DefaultConstructible<double>);
    static_assert(DefaultConstructible<bool>);
    static_assert(DefaultConstructible<char>);
    static_assert(DefaultConstructible<unsigned int>);
    static_assert(DefaultConstructible<long long>);

    static_assert(DefaultConstructible<EmptyStruct>);
    static_assert(DefaultConstructible<ExplicitDefaultCtor>);
    static_assert(DefaultConstructible<TrivialMembers>);
    static_assert(DefaultConstructible<UserDefinedDefaultCtor>);
    static_assert(DefaultConstructible<DefaultAndOtherCtors>);

    // Pointers are zero-initializable (default-constructible)

    static_assert(DefaultConstructible<int*>);
    static_assert(DefaultConstructible<void*>);
    static_assert(DefaultConstructible<EmptyStruct*>);

    // --- Static assertions: types that should NOT satisfy ---

    static_assert(not DefaultConstructible<DeletedDefaultCtor>);
    static_assert(not DefaultConstructible<UserCtorOnly>);
    static_assert(not DefaultConstructible<DeletedDefaultWithOtherCtor>);
    static_assert(not DefaultConstructible<PrivateDefaultCtor>);
    static_assert(not DefaultConstructible<ProtectedDefaultCtor>);

    // References are never default-constructible (must bind to something)
    
    static_assert(not DefaultConstructible<int&>);
    static_assert(not DefaultConstructible<const int&>);
    static_assert(not DefaultConstructible<int&&>);

    // void is not default-constructible
    
    static_assert(not DefaultConstructible<void>);

    struct Incomplete;
    return not DefaultConstructible<Incomplete>;
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