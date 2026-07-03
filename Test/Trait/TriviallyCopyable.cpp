// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyCopyable.hpp"

using Alice::Trait::TriviallyCopyable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------------------
    // Test types
    // ---------------------------------------------------------------------------

    // --- Should satisfy TriviallyCopyable ---

    struct EmptyStruct{};

    struct PodStruct
    {
        int i;

        float f;
    };

    struct NestedPod
    {
        PodStruct inner;

        char c;
    };

    struct PointerMember
    {
        int* p;

        const void* vp;
    };

    union TrivialUnion
    {
        int i;

        float f;
    };

    enum PlainEnum
    {
        A,
        B,
        C
    };

    enum class ScopedEnum : unsigned
    {
        X,
        Y,
        Z
    };

    // --- Should NOT satisfy TriviallyCopyable ---

    struct UserCopyCtor
    {
        UserCopyCtor(int){}

        UserCopyCtor(const UserCopyCtor&){}
    };

    struct UserMoveCtor
    {
        UserMoveCtor(int){}

        UserMoveCtor(UserMoveCtor&&){}
    };

    struct UserCopyAssign
    {
        UserCopyAssign& operator=(const UserCopyAssign&)
        {
            return *this;
        }
    };

    struct UserMoveAssign
    {
        UserMoveAssign& operator=(UserMoveAssign&&)
        {
            return *this;
        }
    };

    struct UserDtor
    {
        ~UserDtor(){}
    };

    struct DeletedCopyCtor
    {
        DeletedCopyCtor(int){}

        DeletedCopyCtor(const DeletedCopyCtor&) = delete;
    };

    // A struct is non-trivially copyable when it contains a non-trivially copyable member.
    struct WrapsUserDtor
    {
        UserDtor member;
    };

    // ---------------------------------------------------------------------------
    // Positive assertions  (concept must be satisfied)
    // ---------------------------------------------------------------------------

    // Fundamental types

    static_assert(TriviallyCopyable<bool>);
    static_assert(TriviallyCopyable<char>);
    static_assert(TriviallyCopyable<signed char>);
    static_assert(TriviallyCopyable<unsigned char>);
    static_assert(TriviallyCopyable<short>);
    static_assert(TriviallyCopyable<int>);
    static_assert(TriviallyCopyable<long>);
    static_assert(TriviallyCopyable<long long>);
    static_assert(TriviallyCopyable<unsigned int>);
    static_assert(TriviallyCopyable<float>);
    static_assert(TriviallyCopyable<double>);
    static_assert(TriviallyCopyable<long double>);

    // cv-qualified fundamentals remain trivially copyable

    static_assert(TriviallyCopyable<const int>);
    static_assert(TriviallyCopyable<volatile int>);
    static_assert(TriviallyCopyable<const volatile double>);

    // Pointer types (always trivially copyable regardless of pointee)

    static_assert(TriviallyCopyable<int*>);
    static_assert(TriviallyCopyable<const int*>);
    static_assert(TriviallyCopyable<void*>);
    static_assert(TriviallyCopyable<const void*>);
    static_assert(TriviallyCopyable<UserDtor*>); // pointer-to-non-trivial is still trivial

    // A deleted copy constructor doesn't make the type non-trivially copyable

    static_assert(TriviallyCopyable<DeletedCopyCtor>);

    // Enumerations

    static_assert(TriviallyCopyable<PlainEnum>);
    static_assert(TriviallyCopyable<ScopedEnum>);

    // User-defined trivial types

    static_assert(TriviallyCopyable<EmptyStruct>);
    static_assert(TriviallyCopyable<PodStruct>);
    static_assert(TriviallyCopyable<NestedPod>);
    static_assert(TriviallyCopyable<PointerMember>);
    static_assert(TriviallyCopyable<TrivialUnion>);

    // Arrays of trivially copyable types are themselves trivially copyable

    static_assert(TriviallyCopyable<int[8]>);
    static_assert(TriviallyCopyable<PodStruct[4]>);

    // ---------------------------------------------------------------------------
    // Negative assertions  (concept must NOT be satisfied)
    // ---------------------------------------------------------------------------

    // Reference types are never trivially copyable

    static_assert(not TriviallyCopyable<int&>);
    static_assert(not TriviallyCopyable<const int&>);
    static_assert(not TriviallyCopyable<int&&>);

    // User-defined special members break trivial copyability
    static_assert(not TriviallyCopyable<UserCopyCtor>);
    static_assert(not TriviallyCopyable<UserMoveCtor>);
    static_assert(not TriviallyCopyable<UserCopyAssign>);
    static_assert(not TriviallyCopyable<UserMoveAssign>);
    static_assert(not TriviallyCopyable<UserDtor>);

    // Transitivity: a struct containing a non-trivial member is non-trivial

    static_assert(not TriviallyCopyable<WrapsUserDtor>);

    struct Incomplete;
    return not TriviallyCopyable<Incomplete>;
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