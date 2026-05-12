// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyCopyAssignable.hpp"

using Alice::Trait::TriviallyCopyAssignable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Positive cases: should satisfy TriviallyCopyAssignable ---

    // Primitive scalar types

    static_assert(TriviallyCopyAssignable<int>);
    static_assert(TriviallyCopyAssignable<float>);
    static_assert(TriviallyCopyAssignable<double>);
    static_assert(TriviallyCopyAssignable<char>);
    static_assert(TriviallyCopyAssignable<bool>);
    static_assert(TriviallyCopyAssignable<unsigned long long>);

    // Raw pointer (pointer itself is trivially copy-assignable)

    static_assert(TriviallyCopyAssignable<int*>);
    static_assert(TriviallyCopyAssignable<const int*>);

    // References are trivially copy-assignable
    
    static_assert(TriviallyCopyAssignable<int&>);
    static_assert(TriviallyCopyAssignable<int&&>);

    // Implicitly defaulted copy assignment (compiler-generated trivial one)

    struct Empty{};

    static_assert(TriviallyCopyAssignable<Empty>);

    struct TrivialScalars
    {
        int x;
        
        float y;
        
        char z;
    };

    static_assert(TriviallyCopyAssignable<TrivialScalars>);

    struct TrivialNested
    {
        TrivialScalars inner;
        
        int n;
    };
    
    static_assert(TriviallyCopyAssignable<TrivialNested>);

    // Explicitly defaulted copy assignment is still trivial

    struct ExplicitDefault
    {
        ExplicitDefault& operator=(const ExplicitDefault&) = default;

        int value;
    };

    static_assert(TriviallyCopyAssignable<ExplicitDefault>);

    // --- Negative cases: must NOT satisfy TriviallyCopyAssignable ---

    // User-provided (non-trivial) copy assignment operator

    struct UserProvidedCopyAssign
    {
        UserProvidedCopyAssign& operator=(const UserProvidedCopyAssign&)
        {
            return *this;
        }
    };

    static_assert(not TriviallyCopyAssignable<UserProvidedCopyAssign>);

    // Deleted copy assignment

    struct DeletedCopyAssign
    {
        DeletedCopyAssign& operator=(const DeletedCopyAssign&) = delete;
    };

    static_assert(not TriviallyCopyAssignable<DeletedCopyAssign>);

    // A member with a user-provided copy assignment contaminates the aggregate

    struct ContaminatedByMember
    {
        UserProvidedCopyAssign m;
    };

    static_assert(not TriviallyCopyAssignable<ContaminatedByMember>);

    // Virtual function forces a vtable pointer; copy assignment is non-trivial
    
    struct HasVirtual
    {
        virtual void foo(){}
    };
    
    static_assert(not TriviallyCopyAssignable<HasVirtual>);

    // const-qualified objects or references are not copy-assignable
    
    static_assert(not TriviallyCopyAssignable<const int>);
    static_assert(not TriviallyCopyAssignable<const int&>);
    static_assert(not TriviallyCopyAssignable<const Empty>);

    // Arrays are not copy-assignable in C++

    static_assert(not TriviallyCopyAssignable<int[4]>);

    // void is not assignable

    static_assert(not TriviallyCopyAssignable<void>);

    struct Incomplete;
    return not TriviallyCopyAssignable<Incomplete>;
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