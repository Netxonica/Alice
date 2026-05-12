// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyCopyConstructible.hpp"

using Alice::Trait::TriviallyCopyConstructible;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Types under test ---

    struct TrivialStruct{};

    struct TrivialWithMembers
    {
        int x;

        float y;
    };

    struct UserDefinedCopyCtor
    {
        UserDefinedCopyCtor(const UserDefinedCopyCtor&){}
    };

    struct DeletedCopyCtor
    {
        DeletedCopyCtor(const DeletedCopyCtor&) = delete;
    };

    struct ExplicitlyDefaultedCopyCtor
    {
        ExplicitlyDefaultedCopyCtor(const ExplicitlyDefaultedCopyCtor&) = default;
    };

    struct MoveOnlyType
    {
        MoveOnlyType(const MoveOnlyType&) = delete;

        MoveOnlyType(MoveOnlyType&&) = default;

        MoveOnlyType& operator=(const MoveOnlyType&) = delete;

        MoveOnlyType& operator=(MoveOnlyType&&) = default;
    };

    struct ContainsUserDefinedCopyCtor
    {
        UserDefinedCopyCtor member;
    };

    struct ContainsDeletedCopyCtor
    {
        DeletedCopyCtor member;
    };

    struct TrivialDerived : TrivialStruct{};

    struct NonTrivialBase
    {
        NonTrivialBase(const NonTrivialBase&){}
    };

    struct DerivedFromNonTrivialBase : NonTrivialBase{};

    // --- Positive cases (must satisfy TriviallyCopyConstructible) ---

    static_assert(TriviallyCopyConstructible<int>,
    "Fundamental types must be trivially copy constructible.");
    static_assert(TriviallyCopyConstructible<float>,
    "Fundamental types must be trivially copy constructible.");
    static_assert(TriviallyCopyConstructible<bool>,
    "Fundamental types must be trivially copy constructible.");
    static_assert(TriviallyCopyConstructible<char>,
    "Fundamental types must be trivially copy constructible.");
    static_assert(TriviallyCopyConstructible<int*>,
    "Raw pointer types must be trivially copy constructible.");
    static_assert(TriviallyCopyConstructible<const int*>,
    "Pointer-to-const types must be trivially copy constructible.");
    static_assert(TriviallyCopyConstructible<int* const>,
    "Const-qualified pointer types must be trivially copy constructible.");
    static_assert(TriviallyCopyConstructible<int&>,
    "Lvalue reference types are trivially copy constructible.");
    static_assert(TriviallyCopyConstructible<TrivialStruct>,
    "An empty struct with no user-defined special members must be trivially copy constructible.");
    static_assert(TriviallyCopyConstructible<TrivialWithMembers>,
    "A struct whose members are all trivially copy constructible must itself be so.");
    static_assert(TriviallyCopyConstructible<ExplicitlyDefaultedCopyCtor>,
    "An explicitly defaulted copy constructor must count as trivial.");
    static_assert(TriviallyCopyConstructible<TrivialDerived>,
    "A struct that trivially derives from a trivial base must be trivially copy constructible.");

    // --- Negative cases (must NOT satisfy TriviallyCopyConstructible) ---

    static_assert(not TriviallyCopyConstructible<UserDefinedCopyCtor>,
    "A user-defined (non-trivial) copy constructor must not satisfy the concept.");
    static_assert(not TriviallyCopyConstructible<DeletedCopyCtor>,
    "A deleted copy constructor must not satisfy the concept.");
    static_assert(not TriviallyCopyConstructible<MoveOnlyType>,
    "A move-only type must not satisfy the concept.");
    static_assert(not TriviallyCopyConstructible<ContainsUserDefinedCopyCtor>,
    "A struct containing a member with a non-trivial copy constructor must not satisfy the "
    "concept.");
    static_assert(not TriviallyCopyConstructible<ContainsDeletedCopyCtor>,
    "A struct containing a member with a deleted copy constructor must not satisfy the concept.");
    static_assert(not TriviallyCopyConstructible<DerivedFromNonTrivialBase>,
    "Deriving from a non-trivially copy constructible base must prevent the concept from being "
    "satisfied.");

    // Rvalue references and void are not object types and must not satisfy the concept.

    static_assert(not TriviallyCopyConstructible<int&&>,
    "Rvalue reference types are not copy constructible.");
    static_assert(not TriviallyCopyConstructible<void>, "void is not copy constructible.");

    struct Incomplete;
    return not TriviallyCopyConstructible<Incomplete>;
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