// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/MemberFunctionPointer.hpp"

using Alice::Trait::MemberFunctionPointer;

auto FreeFunction() -> void{}

auto FreeFunctionWithArgs(int, float) -> int
{
    return 0;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    struct Foo
    {
        auto Plain() -> void{}

        auto WithArgs(int, float) -> int
        {
            return 0;
        }

        auto Noexcept() noexcept -> void{}

        auto NoexceptWithArgs(int) noexcept -> int
        {
            return 0;
        }

        auto Const() const -> void{}

        auto ConstNoexcept() const noexcept -> void{}

        auto Volatile() volatile -> void{}

        auto VolatileNoexcept() volatile noexcept -> void{}

        auto ConstVolatile() const volatile -> void{}

        auto ConstVolatileNoexcept() const volatile noexcept -> void{}

        int DataMember;
    };

    // --- Positive cases: member function pointers ---

    static_assert(MemberFunctionPointer<decltype(&Foo::Plain)>);
    static_assert(MemberFunctionPointer<decltype(&Foo::WithArgs)>);
    static_assert(MemberFunctionPointer<decltype(&Foo::Noexcept)>);
    static_assert(MemberFunctionPointer<decltype(&Foo::NoexceptWithArgs)>);
    static_assert(MemberFunctionPointer<decltype(&Foo::Const)>);
    static_assert(MemberFunctionPointer<decltype(&Foo::ConstNoexcept)>);
    static_assert(MemberFunctionPointer<decltype(&Foo::Volatile)>);
    static_assert(MemberFunctionPointer<decltype(&Foo::VolatileNoexcept)>);
    static_assert(MemberFunctionPointer<decltype(&Foo::ConstVolatile)>);
    static_assert(MemberFunctionPointer<decltype(&Foo::ConstVolatileNoexcept)>);

    // Explicit pointer types

    static_assert(MemberFunctionPointer<void (Foo::*)()>);
    static_assert(MemberFunctionPointer<void (Foo::*)() noexcept>);
    static_assert(MemberFunctionPointer<int (Foo::*)(int, float)>);
    static_assert(MemberFunctionPointer<int (Foo::*)(int, float) noexcept>);

    // --- Negative cases: non-member-function-pointer types ---

    // Free function pointers

    static_assert(not MemberFunctionPointer<decltype(&FreeFunction)>);
    static_assert(not MemberFunctionPointer<decltype(&FreeFunctionWithArgs)>);
    static_assert(not MemberFunctionPointer<void (*)()>);
    static_assert(not MemberFunctionPointer<int (*)(int, float)>);

    // Member data pointer

    static_assert(not MemberFunctionPointer<decltype(&Foo::DataMember)>);
    static_assert(not MemberFunctionPointer<int Foo::*>);

    // Scalar types

    static_assert(not MemberFunctionPointer<int>);
    static_assert(not MemberFunctionPointer<float>);
    static_assert(not MemberFunctionPointer<bool>);
    static_assert(not MemberFunctionPointer<void>);

    // Pointer and reference types

    static_assert(not MemberFunctionPointer<int *>);
    static_assert(not MemberFunctionPointer<int &>);
    static_assert(not MemberFunctionPointer<const int *>);
    static_assert(not MemberFunctionPointer<Foo *>);
    static_assert(not MemberFunctionPointer<Foo &>);

    // Class type itself

    static_assert(not MemberFunctionPointer<Foo>);

    struct Incomplete;
    return not MemberFunctionPointer<Incomplete>;
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