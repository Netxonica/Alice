// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/CopyAssignable.hpp"

using Alice::Trait::CopyAssignable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Types under test ---

    struct WithDefaultCopyAssign
    {
        int value;
    };

    struct WithExplicitCopyAssign
    {
        int value;

        WithExplicitCopyAssign& operator=(const WithExplicitCopyAssign&)
        {
            return *this;
        }
    };

    struct WithDeletedCopyAssign
    {
        WithDeletedCopyAssign& operator=(const WithDeletedCopyAssign&) = delete;
    };

    struct MoveOnlyAssign
    {
        MoveOnlyAssign& operator=(MoveOnlyAssign&&) = default;

        MoveOnlyAssign& operator=(const MoveOnlyAssign&) = delete;
    };

    struct PrivateCopyAssign
    {
        void foo(){}
    private:
        PrivateCopyAssign& operator=(const PrivateCopyAssign&) = default;
    };

    struct WithNonConstCopyAssign
    {
        // Takes by non-const ref — not a real copy assignment per the concept
        WithNonConstCopyAssign& operator=(WithNonConstCopyAssign&)
        {
            return *this;
        }
    };

    struct Base
    {
        virtual ~Base() = default;
    };

    struct Derived : Base{};

    // --- Positive cases (must satisfy CopyAssignable) ---

    static_assert(CopyAssignable<int>, "Primitive int must be copy-assignable.");
    static_assert(CopyAssignable<double>, "Primitive double must be copy-assignable.");
    static_assert(CopyAssignable<char>, "Primitive char must be copy-assignable.");
    static_assert(CopyAssignable<int*>, "Raw pointer must be copy-assignable.");
    static_assert(CopyAssignable<WithDefaultCopyAssign>,
    "Struct with compiler-generated copy assignment must be copy-assignable.");
    static_assert(CopyAssignable<WithExplicitCopyAssign>,
    "Struct with explicit copy assignment operator must be copy-assignable.");
    static_assert(CopyAssignable<Base>,
    "Base class with virtual destructor must be copy-assignable.");
    static_assert(CopyAssignable<Derived>,
    "Derived class inheriting copy assignment must be copy-assignable.");

    // --- Negative cases (must NOT satisfy CopyAssignable) ---

    static_assert(not CopyAssignable<const int>,
    "const-qualified type must not be copy-assignable (assignment to const is ill-formed).");
    static_assert(not CopyAssignable<WithDeletedCopyAssign>,
    "Struct with deleted copy assignment must not be copy-assignable.");
    static_assert(not CopyAssignable<MoveOnlyAssign>,
    "Move-only struct (deleted copy assignment) must not be copy-assignable.");
    static_assert(not CopyAssignable<PrivateCopyAssign>,
    "Struct with private copy assignment must not be copy-assignable.");
    static_assert(not CopyAssignable<WithNonConstCopyAssign>,
    "Struct whose only assignment takes non-const ref must not satisfy CopyAssignable (concept "
    "requires assignability from 'const Self&', not 'Self&').");
    static_assert(not CopyAssignable<int[4]>, "Raw arrays must not be copy-assignable.");

    struct Incomplete;
    return not CopyAssignable<Incomplete>;
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