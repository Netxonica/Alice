// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/CopyConstructible.hpp"

using Alice::Trait::CopyConstructible;

/// Trivially copyable scalar — the simplest possible case.
struct Trivial
{
    int value;
};

/// User-defined copy constructor that is accessible.
struct UserCopyCtor
{
    int value;

    UserCopyCtor(const UserCopyCtor&) : value(0){}

    UserCopyCtor& operator=(const UserCopyCtor&) = default;
};

/// Copy constructor explicitly deleted — must NOT satisfy the concept.
struct DeletedCopyCtor
{
    DeletedCopyCtor(const DeletedCopyCtor&) = delete;
};

/// Move-only type (copy deleted implicitly when move is user-declared).
struct MoveOnly
{
    MoveOnly(MoveOnly&&) = default;

    MoveOnly& operator=(MoveOnly&&) = default;
};

/// Copy constructor is private — must NOT satisfy the concept.
struct PrivateCopyCtor
{
private:
    PrivateCopyCtor(const PrivateCopyCtor&) = default;
};

/// Both copy and move deleted — must NOT satisfy the concept.
struct NoCopyNoMove
{
    NoCopyNoMove(const NoCopyNoMove&) = delete;

    NoCopyNoMove(NoCopyNoMove&&) = delete;
};

/// Reference member: copy construction is possible (member is re-bound by
/// the compiler-generated copy ctor), so this SHOULD satisfy the concept.
struct WithRefMember
{
    int& ref;
};

/// cv-qualified wrappers — const and volatile copies of Trivial must still
/// satisfy the concept because const Self& binds to const T.
using ConstTrivial = const Trivial;

using VolatileTrivial = volatile Trivial;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------------------
    // Positive assertions — types that MUST satisfy CopyConstructible
    // ---------------------------------------------------------------------------

    static_assert(CopyConstructible<int>, "Primitive int must be CopyConstructible.");
    static_assert(CopyConstructible<float>, "Primitive float must be CopyConstructible.");
    static_assert(CopyConstructible<int*>, "Raw pointer must be CopyConstructible.");
    static_assert(CopyConstructible<Trivial>,
    "Trivially copyable struct must be CopyConstructible.");
    static_assert(CopyConstructible<UserCopyCtor>,
    "Struct with accessible user-defined copy ctor must be CopyConstructible.");
    static_assert(CopyConstructible<WithRefMember>,
    "Struct with a reference member must be CopyConstructible (compiler-generated copy ctor "
    "re-binds the reference).");

    // cv-qualified scalar (the concept checks 'const Self&', so querying
    // 'const int' is a valid edge case: const int is constructible from
    // const (const int)&, i.e. from 'const int&').
    
    static_assert(CopyConstructible<ConstTrivial>,
    "const-qualified Trivial must be CopyConstructible.");

    // ---------------------------------------------------------------------------
    // Negative assertions — types that must NOT satisfy CopyConstructible
    // ---------------------------------------------------------------------------

    static_assert(not CopyConstructible<DeletedCopyCtor>,
    "Deleted copy ctor must not satisfy CopyConstructible.");
    static_assert(not CopyConstructible<MoveOnly>,
    "Move-only type (implicit copy deletion) must not satisfy CopyConstructible.");
    static_assert(not CopyConstructible<PrivateCopyCtor>,
    "Private copy ctor must not satisfy CopyConstructible.");
    static_assert(not CopyConstructible<NoCopyNoMove>,
    "Type with both copy and move deleted must not satisfy CopyConstructible.");

    // References types test
    
    static_assert(CopyConstructible<int&>, "lvalue reference type must satisfy CopyConstructible.")
    ;
    static_assert(not CopyConstructible<int&&>,
    "rvalue reference type must not satisfy CopyConstructible.");

    // void is not constructible at all.

    static_assert(not CopyConstructible<void>, "void must not satisfy CopyConstructible.");

    struct Incomplete;
    return not CopyConstructible<Incomplete>;
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