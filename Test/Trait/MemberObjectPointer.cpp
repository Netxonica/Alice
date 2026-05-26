// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/MemberObjectPointer.hpp"

using Alice::Trait::MemberObjectPointer;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    struct Empty{};

    struct Base
    {
        int baseInt;

        float baseFloat;

        void foo(){}
    };

    struct Derived : Base
    {
        double derivedDouble;

        const int constMember;

        volatile int volatileMember;

        int* pointerMember;

        int arrayMember[4];
    };

    union UnionType
    {
        int i;

        float f;
    };

    // --- Positive: plain member object pointers ---

    static_assert(MemberObjectPointer<int Base::*>);
    static_assert(MemberObjectPointer<float Base::*>);
    static_assert(MemberObjectPointer<double Derived::*>);

    // --- Positive: cv-qualified pointed-to types ---

    static_assert(MemberObjectPointer<const int Base::*>);
    static_assert(MemberObjectPointer<volatile int Base::*>);
    static_assert(MemberObjectPointer<const volatile int Base::*>);

    // --- Positive: pointer-to-member in a union ---
    static_assert(MemberObjectPointer<int   UnionType::*>);
    static_assert(MemberObjectPointer<float UnionType::*>);

    // --- Positive: pointer member and array member ---

    static_assert(MemberObjectPointer<int* Derived::*>);
    static_assert(MemberObjectPointer<int* Base::*>);
    static_assert(MemberObjectPointer<int Derived::*>);

    // --- Negative: pointer to member *function* ---

    static_assert(not MemberObjectPointer<void (Base::*)()>);
    static_assert(not MemberObjectPointer<int (Base::*)(int)>);
    static_assert(not MemberObjectPointer<void (Base::*)() const>);
    static_assert(not MemberObjectPointer<void (Base::*)() noexcept>);
    static_assert(not MemberObjectPointer<void (Base::*)() const noexcept>);

    // --- Negative: ordinary (non-member) pointer types ---

    static_assert(not MemberObjectPointer<int*>);
    static_assert(not MemberObjectPointer<float*>);
    static_assert(not MemberObjectPointer<void*>);
    static_assert(not MemberObjectPointer<int**>);

    // --- Negative: plain non-pointer types ---

    static_assert(not MemberObjectPointer<int>);
    static_assert(not MemberObjectPointer<float>);
    static_assert(not MemberObjectPointer<double>);
    static_assert(not MemberObjectPointer<Base>);
    static_assert(not MemberObjectPointer<Derived>);
    static_assert(not MemberObjectPointer<Empty>);

    // --- Negative: reference types ---

    static_assert(not MemberObjectPointer<int&>);
    static_assert(not MemberObjectPointer<int&&>);

    // --- Positive: non-static data members ---

    static_assert(MemberObjectPointer<decltype(&Base::baseInt)>);
    static_assert(MemberObjectPointer<decltype(&Base::baseFloat)>);
    static_assert(MemberObjectPointer<decltype(&Derived::baseInt)>);
    static_assert(MemberObjectPointer<decltype(&Derived::arrayMember)>);
    static_assert(MemberObjectPointer<decltype(&Derived::constMember)>);
    static_assert(MemberObjectPointer<decltype(&Derived::derivedDouble)>);
    static_assert(MemberObjectPointer<decltype(&Derived::pointerMember)>);
    static_assert(MemberObjectPointer<decltype(&Derived::volatileMember)>);
    static_assert(MemberObjectPointer<decltype(&UnionType::f)>);
    static_assert(MemberObjectPointer<decltype(&UnionType::i)>);

    // --- Negative: non-static member function ---

    static_assert(not MemberObjectPointer<decltype(&Base::foo)>);

    // --- Negative: nullptr_t and void ---

    static_assert(not MemberObjectPointer<decltype(nullptr)>);
    static_assert(not MemberObjectPointer<void>);

    struct Incomplete;
    return not MemberObjectPointer<Incomplete>;
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