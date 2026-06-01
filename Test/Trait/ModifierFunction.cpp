// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/ModifierFunction.hpp"

using Alice::Trait::ModifierFunction;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    struct S{};

    union U{};

    // ─── Not a member-function-pointer type ───────────────────────────────────────

    static_assert(not ModifierFunction<void>);
    static_assert(not ModifierFunction<int>);
    static_assert(not ModifierFunction<S*>);
    static_assert(not ModifierFunction<void (*)()>);       // free function pointer
    static_assert(not ModifierFunction<void (*)(...)>);    // free variadic function pointer
    static_assert(not ModifierFunction<int S::*>);         // pointer to data member, not function

    // ─── const-qualified (cannot modify non-mutable members) ──────────────────────
    // All twelve cv/ref/noexcept combos, no-arg form

    static_assert(not ModifierFunction<void (S::*)() const>);
    static_assert(not ModifierFunction<void (S::*)() const noexcept>);
    static_assert(not ModifierFunction<void (S::*)() const&>);
    static_assert(not ModifierFunction<void (S::*)() const& noexcept>);
    static_assert(not ModifierFunction<void (S::*)() const&&>);
    static_assert(not ModifierFunction<void (S::*)() const&& noexcept>);
    static_assert(not ModifierFunction<void (S::*)() const volatile>);
    static_assert(not ModifierFunction<void (S::*)() const volatile noexcept>);
    static_assert(not ModifierFunction<void (S::*)() const volatile&>);
    static_assert(not ModifierFunction<void (S::*)() const volatile& noexcept>);
    static_assert(not ModifierFunction<void (S::*)() const volatile&&>);
    static_assert(not ModifierFunction<void (S::*)() const volatile&& noexcept>);

    // const with parameters

    static_assert(not ModifierFunction<void (S::*)(int) const>);
    static_assert(not ModifierFunction<int (S::*)(int, double) const volatile&& noexcept>);

    // const variadic

    static_assert(not ModifierFunction<void (S::*)(...) const>);
    static_assert(not ModifierFunction<void (S::*)(...) const noexcept>);
    static_assert(not ModifierFunction<void (S::*)(...) const volatile>);
    static_assert(not ModifierFunction<void (S::*)(...) const volatile&& noexcept>);

    // ─── Non-const, no parameters — all twelve qualifier combinations ──────────────

    static_assert(ModifierFunction<void (S::*)()>);
    static_assert(ModifierFunction<void (S::*)() noexcept>);
    static_assert(ModifierFunction<void (S::*)() &>);
    static_assert(ModifierFunction<void (S::*)() & noexcept>);
    static_assert(ModifierFunction<void (S::*)() &&>);
    static_assert(ModifierFunction<void (S::*)() && noexcept>);
    static_assert(ModifierFunction<void (S::*)() volatile>);
    static_assert(ModifierFunction<void (S::*)() volatile noexcept>);
    static_assert(ModifierFunction<void (S::*)() volatile&>);
    static_assert(ModifierFunction<void (S::*)() volatile& noexcept>);
    static_assert(ModifierFunction<void (S::*)() volatile&&>);
    static_assert(ModifierFunction<void (S::*)() volatile&& noexcept>);

    // ─── Non-const, with parameters — all twelve qualifier combinations ────────────

    static_assert(ModifierFunction<void (S::*)(int)>);
    static_assert(ModifierFunction<void (S::*)(int) noexcept>);
    static_assert(ModifierFunction<void (S::*)(int) &>);
    static_assert(ModifierFunction<void (S::*)(int) & noexcept>);
    static_assert(ModifierFunction<void (S::*)(int) &&>);
    static_assert(ModifierFunction<void (S::*)(int) && noexcept>);
    static_assert(ModifierFunction<void (S::*)(int) volatile>);
    static_assert(ModifierFunction<void (S::*)(int) volatile noexcept>);
    static_assert(ModifierFunction<void (S::*)(int) volatile&>);
    static_assert(ModifierFunction<void (S::*)(int) volatile& noexcept>);
    static_assert(ModifierFunction<void (S::*)(int) volatile&&>);
    static_assert(ModifierFunction<void (S::*)(int) volatile&& noexcept>);

    // multiple parameters

    static_assert(ModifierFunction<int (S::*)(int, double, char) volatile& noexcept>);

    // ─── Non-const C-style variadic — all twelve qualifier combinations ────────────

    static_assert(ModifierFunction<void (S::*)(...)>);
    static_assert(ModifierFunction<void (S::*)(...) noexcept>);
    static_assert(ModifierFunction<void (S::*)(...) &>);
    static_assert(ModifierFunction<void (S::*)(...) & noexcept>);
    static_assert(ModifierFunction<void (S::*)(...) &&>);
    static_assert(ModifierFunction<void (S::*)(...) && noexcept>);
    static_assert(ModifierFunction<void (S::*)(...) volatile>);
    static_assert(ModifierFunction<void (S::*)(...) volatile noexcept>);
    static_assert(ModifierFunction<void (S::*)(...) volatile&>);
    static_assert(ModifierFunction<void (S::*)(...) volatile& noexcept>);
    static_assert(ModifierFunction<void (S::*)(...) volatile&&>);
    static_assert(ModifierFunction<void (S::*)(...) volatile&& noexcept>);

    // ─── Return type is transparent ───────────────────────────────────────────────

    static_assert(ModifierFunction<int (S::*)()>);
    static_assert(ModifierFunction<S* (S::*)(int) noexcept>);
    static_assert(ModifierFunction<int& (S::*)() volatile>);
    static_assert(not ModifierFunction<int (S::*)() const>);

    // ─── Works on unions too ──────────────────────────────────────────────────────

    static_assert(ModifierFunction<void (U::*)()>);
    static_assert(ModifierFunction<void (U::*)(...) volatile&&>);
    static_assert(not ModifierFunction<void (U::*)() const>);

    // ─── Realistic usage via decltype ─────────────────────────────────────────────

    struct Concrete
    {
        void Mutate(){}

        void MutateNoexcept() noexcept{}

        void Observe() const{}

        void ObserveNoexcept() const noexcept{}
    };

    static_assert(ModifierFunction<decltype(&Concrete::Mutate)>);
    static_assert(ModifierFunction<decltype(&Concrete::MutateNoexcept)>);
    static_assert(not ModifierFunction<decltype(&Concrete::Observe)>);
    static_assert(not ModifierFunction<decltype(&Concrete::ObserveNoexcept)>);

    struct Incomplete;
    return not ModifierFunction<Incomplete>;
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