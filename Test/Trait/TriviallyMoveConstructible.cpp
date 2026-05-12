// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyMoveConstructible.hpp"

using Alice::Trait::TriviallyMoveConstructible;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Fixtures ─────────────────────────────────────────────────────────────────

    struct Trivial
    {
        int x;
        
        float y;
    };

    struct DefaultedMoveCtor
    {
        int value;
        
        DefaultedMoveCtor(DefaultedMoveCtor&&) = default;
    };

    struct TrivialWithTrivialBase : Trivial
    {
        char z;
    };

    struct UserDefinedMoveCtor
    {
        int* ptr;
        
        UserDefinedMoveCtor(UserDefinedMoveCtor&& other) : ptr(other.ptr)
        {
            other.ptr = nullptr;
        }
    };

    struct DeletedMoveCtor
    {
        DeletedMoveCtor(DeletedMoveCtor&&) = delete;
    };

    struct MemberWithUserDefinedMoveCtor
    {
        UserDefinedMoveCtor member;
    };

    struct MemberWithDeletedMoveCtor
    {
        DeletedMoveCtor member;
    };

    enum PlainEnum
    {
        A,
        B
    };

    enum class ScopedEnum : int
    {
        X,
        Y
    };

    // ── Positive cases ────────────────────────────────────────────────────────────

    // Fundamental arithmetic types are trivially move-constructible and sized.

    static_assert(TriviallyMoveConstructible<bool>);
    static_assert(TriviallyMoveConstructible<char>);
    static_assert(TriviallyMoveConstructible<int>);
    static_assert(TriviallyMoveConstructible<unsigned int>);
    static_assert(TriviallyMoveConstructible<long long>);
    static_assert(TriviallyMoveConstructible<float>);
    static_assert(TriviallyMoveConstructible<double>);

    // Pointer types (typed and void*) are trivially move-constructible.
    
    static_assert(TriviallyMoveConstructible<int*>);
    static_assert(TriviallyMoveConstructible<const int*>);
    static_assert(TriviallyMoveConstructible<void*>);

    // References are trivially move constructible, even when they bind.
    
    static_assert(TriviallyMoveConstructible<int&>);
    static_assert(TriviallyMoveConstructible<int&&>);

    // Enumerations inherit the triviality of their underlying type.
    
    static_assert(TriviallyMoveConstructible<PlainEnum>);
    static_assert(TriviallyMoveConstructible<ScopedEnum>);

    // Aggregate struct with no user-provided special members.
    
    static_assert(TriviallyMoveConstructible<Trivial>);

    // Explicitly defaulted move constructor is still trivial.
    
    static_assert(TriviallyMoveConstructible<DefaultedMoveCtor>);

    // Trivial inheritance should not break triviality.

    static_assert(TriviallyMoveConstructible<TrivialWithTrivialBase>);

    // ── Negative cases ────────────────────────────────────────────────────────────

    // void has no size and is therefore not Sized.
    
    static_assert(not TriviallyMoveConstructible<void>);

    // A user-defined move constructor body makes the type non-trivial.

    static_assert(not TriviallyMoveConstructible<UserDefinedMoveCtor>);

    // A deleted move constructor makes the type non-move-constructible at all.

    static_assert(not TriviallyMoveConstructible<DeletedMoveCtor>);

    // Triviality is not satisfied when a member has a user-defined move constructor.

    static_assert(not TriviallyMoveConstructible<MemberWithUserDefinedMoveCtor>);

    // Triviality is not satisfied when a member has a deleted move constructor.

    static_assert(not TriviallyMoveConstructible<MemberWithDeletedMoveCtor>);

    struct Incomplete;
    return not TriviallyMoveConstructible<Incomplete>;
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