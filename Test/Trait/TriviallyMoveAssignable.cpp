// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyMoveAssignable.hpp"

using Alice::Trait::TriviallyMoveAssignable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Types under test ---

    struct Trivial{};

    struct TrivialWithMembers
    {
        int x;

        float y;
    };

    struct UserDefinedMoveAssign
    {
        UserDefinedMoveAssign& operator=(UserDefinedMoveAssign&&)
        {
            return *this;
        }
    };

    struct DeletedMoveAssign
    {
        DeletedMoveAssign& operator=(DeletedMoveAssign&&) = delete;
    };

    struct VirtualDestructor
    {
        virtual ~VirtualDestructor() = default;
    };

    struct TrivialMoveExplicit
    {
        TrivialMoveExplicit& operator=(TrivialMoveExplicit&&) = default;
    };

    // --- Positive cases: must satisfy TriviallyMoveAssignable ---

    static_assert(TriviallyMoveAssignable<int>, "int must be trivially move assignable");
    static_assert(TriviallyMoveAssignable<float>, "float must be trivially move assignable");
    static_assert(TriviallyMoveAssignable<double>, "double must be trivially move assignable");
    static_assert(TriviallyMoveAssignable<char>, "char must be trivially move assignable");
    static_assert(TriviallyMoveAssignable<int*>, "int* must be trivially move assignable");
    static_assert(TriviallyMoveAssignable<Trivial>,
    "Trivial struct must be trivially move assignable");
    static_assert(TriviallyMoveAssignable<TrivialWithMembers>,
    "Struct with only trivial members must be trivially move assignable");
    static_assert(TriviallyMoveAssignable<TrivialMoveExplicit>,
    "Explicitly defaulted move assignment must be trivially move assignable");

    // --- Negative cases: must NOT satisfy TriviallyMoveAssignable ---

    static_assert(not TriviallyMoveAssignable<UserDefinedMoveAssign>,
    "User-defined move assignment operator must not satisfy the concept");
    static_assert(not TriviallyMoveAssignable<DeletedMoveAssign>,
    "Deleted move assignment operator must not satisfy the concept");
    static_assert(not TriviallyMoveAssignable<VirtualDestructor>,
    "Class with a virtual destructor must not be trivially move assignable");

    // --- References and cv-qualifiers ---

    static_assert(TriviallyMoveAssignable<int>, "int must satisfy the concept");
    static_assert(TriviallyMoveAssignable<int&>, "int& must satisfy the concept");
    static_assert(TriviallyMoveAssignable<int&&>, "int&& must satisfy the concept");
    static_assert(not TriviallyMoveAssignable<const int>,
    "const int must not be trivially move assignable (assignment to const is ill-formed)");
    static_assert(not TriviallyMoveAssignable<const int&>,
    "const int& must not be trivially move assignable (assignment to const ref is ill-formed)");

    // --- Sanity: concept is not accidentally satisfied by unrelated constraint tricks ---

    static_assert(TriviallyMoveAssignable<TrivialWithMembers>,
    "Re-checking TrivialWithMembers for idempotency");
    static_assert(not TriviallyMoveAssignable<UserDefinedMoveAssign>,
    "Re-checking UserDefinedMoveAssign for idempotency");

    struct Incomplete;
    return not TriviallyMoveAssignable<Incomplete>;
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