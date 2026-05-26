// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/MemberPointer.hpp"

using Alice::Trait::MemberPointer;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    struct Base{};
    struct Derived : Base{};

    // --- Data members ---
    struct S
    {
        int x;

        const int cx;

        float y;

        int* p;

        S* self;
    };

    // Pointer-to-member-data

    static_assert(MemberPointer<int S::*>);
    static_assert(MemberPointer<const int S::*>);
    static_assert(MemberPointer<float S::*>);
    static_assert(MemberPointer<int* S::*>);  // pointer-to-pointer member
    static_assert(MemberPointer<S* S::*>);  // self-referential
    static_assert(MemberPointer<decltype(&S::x)>);
    static_assert(MemberPointer<decltype(&S::cx)>);
    static_assert(MemberPointer<decltype(&S::y)>);
    static_assert(MemberPointer<decltype(&S::p)>);
    static_assert(MemberPointer<decltype(&S::self)>);

    // Inherited member (pointer type is still Base::*)

    static_assert(MemberPointer<int Base::*>);

    // --- Member functions: non-cv, cv, ref-qualified ---

    static_assert(MemberPointer<void (S::*)()>);
    static_assert(MemberPointer<void (S::*)() const>);
    static_assert(MemberPointer<void (S::*)() volatile>);
    static_assert(MemberPointer<void (S::*)() const volatile>);
    static_assert(MemberPointer<void (S::*)() &>);
    static_assert(MemberPointer<void (S::*)() const &>);
    static_assert(MemberPointer<void (S::*)() &&>);
    static_assert(MemberPointer<void (S::*)() const &&>);
    static_assert(MemberPointer<void (S::*)() noexcept>);
    static_assert(MemberPointer<void (S::*)() const noexcept>);

    // --- Member functions: various arities and return types ---

    static_assert(MemberPointer<int (S::*)(int)>);
    static_assert(MemberPointer<S& (S::*)(float, double)>);
    static_assert(MemberPointer<S* (S::*)(int, int, int)>);
    static_assert(MemberPointer<void (S::*)(...)>);  // variadic

    // --- Pointer-to-member of derived class ---

    static_assert(MemberPointer<int (Derived::*)>);

    struct Rich : Base
    {
        int val;

        void fn();
    };

    static_assert(MemberPointer<int Rich::*>);
    static_assert(MemberPointer<void (Rich::*)()>);
    static_assert(MemberPointer<decltype(&Rich::val)>);
    static_assert(MemberPointer<decltype(&Rich::fn)>);

    // --- Types that must NOT satisfy ---

    static_assert(not MemberPointer<int>);   // fundamental
    static_assert(not MemberPointer<int*>);   // raw pointer
    static_assert(not MemberPointer<int**>);   // pointer-to-pointer
    static_assert(not MemberPointer<int&>);   // lvalue reference
    static_assert(not MemberPointer<int&&>);   // rvalue reference
    static_assert(not MemberPointer<void()>);   // free function type (not pointer)
    static_assert(not MemberPointer<void(*)()>);   // free function pointer
    static_assert(not MemberPointer<S>);   // class type
    static_assert(not MemberPointer<S*>);   // pointer-to-class
    static_assert(not MemberPointer<void>);   // void
    static_assert(not MemberPointer<decltype(nullptr)>);  // nullptr_t

    // --- cv-qualified pointer-to-member (the pointer itself is cv, not the pointee) ---

    static_assert(MemberPointer<int S::* const>);   // const ptr-to-member
    static_assert(MemberPointer<int S::* volatile>);
    static_assert(MemberPointer<int S::* const volatile>);

    struct Incomplete;
    return not MemberPointer<Incomplete>;
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