// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/ObserverFunction.hpp"

using Alice::Trait::ObserverFunction;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    struct TestClass
    {
        // ── Zero-argument const methods (explicit-arg specializations, empty Arguments...) ──

        auto ZeroArgConst() const -> void{}

        auto ZeroArgConstNoexcept() const noexcept -> void{}

        auto ZeroArgConstLRef() const& -> void{}

        auto ZeroArgConstLRefNoexcept() const& noexcept -> void{}

        auto ZeroArgConstRRef() const&& -> void{}

        auto ZeroArgConstRRefNoexcept() const&& noexcept -> void{}

        auto ZeroArgConstVolatile() const volatile -> void{}

        auto ZeroArgConstVolatileNoexcept() const volatile noexcept -> void{}

        auto ZeroArgConstVolatileLRef() const volatile& -> void{}

        auto ZeroArgConstVolatileLRefNoexcept() const volatile& noexcept -> void{}

        auto ZeroArgConstVolatileRRef() const volatile&& -> void{}

        auto ZeroArgConstVolatileRRefNoexcept() const volatile&& noexcept -> void{}

        // ── Multi-argument const methods (explicit-arg specializations, non-empty Arguments...) ──

        auto MultiArgConst(int, float) const -> bool
        {
            return false;
        }

        auto MultiArgConstNoexcept(int, float) const noexcept -> bool
        {
            return false;
        }

        auto MultiArgConstLRef(int, float) const& -> bool
        {
            return false;
        }

        auto MultiArgConstLRefNoexcept(int, float) const& noexcept -> bool
        {
            return false;
        }

        auto MultiArgConstRRef(int, float) const&& -> bool
        {
            return false;
        }

        auto MultiArgConstRRefNoexcept(int, float) const&& noexcept -> bool
        {
            return false;
        }

        auto MultiArgConstVolatile(int, float) const volatile -> bool
        {
            return false;
        }

        auto MultiArgConstVolatileNoexcept(int, float) const volatile noexcept -> bool
        {
            return false;
        }

        auto MultiArgConstVolatileLRef(int, float) const volatile& -> bool
        {
            return false;
        }

        auto MultiArgConstVolatileLRefNoexcept(int, float) const volatile& noexcept -> bool
        {
            return false;
        }

        auto MultiArgConstVolatileRRef(int, float) const volatile&& -> bool
        {
            return false;
        }

        auto MultiArgConstVolatileRRefNoexcept(int, float) const volatile&& noexcept -> bool
        {
            return false;
        }

        // ── C-style variadic const methods (variadic specializations) ──

        auto VariadicConst(...) const -> void{}

        auto VariadicConstNoexcept(...) const noexcept -> void{}

        auto VariadicConstLRef(...) const& -> void{}

        auto VariadicConstLRefNoexcept(...) const& noexcept -> void{}

        auto VariadicConstRRef(...) const&& -> void{}

        auto VariadicConstRRefNoexcept(...) const&& noexcept -> void{}

        auto VariadicConstVolatile(...) const volatile -> void{}

        auto VariadicConstVolatileNoexcept(...) const volatile noexcept -> void{}

        auto VariadicConstVolatileLRef(...) const volatile& -> void{}

        auto VariadicConstVolatileLRefNoexcept(...) const volatile& noexcept -> void{}

        auto VariadicConstVolatileRRef(...) const volatile&& -> void{}

        auto VariadicConstVolatileRRefNoexcept(...) const volatile&& noexcept -> void{}

        // ── Mutable (non-const) methods — must not satisfy the concept ──

        auto MutableNoQual() -> void{}

        auto MutableNoexcept() noexcept -> void{}

        auto MutableLRef() & -> void{}

        auto MutableLRefNoexcept() & noexcept -> void{}

        auto MutableRRef() && -> void{}

        auto MutableRRefNoexcept() && noexcept -> void{}

        auto MutableVolatile() volatile -> void{}

        auto MutableVolatileNoexcept() volatile noexcept -> void{}

        auto MutableVolatileLRef() volatile& -> void{}

        auto MutableVolatileRRef() volatile&& -> void{}

        auto MutableWithArgs(int, float) -> void{}

        auto MutableVariadic(...) -> void{}

        // ── Other non-qualifying entities ──

        static auto StaticMethod() -> void{} // address yields void(*)(), not a member fn ptr

        int DataMember;                     // address yields int TestClass::*, not a fn ptr
    };

    // ════════════════════════════════════════════════════════════════════════════
    // Positive: zero-argument const member functions
    // ════════════════════════════════════════════════════════════════════════════

    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConst)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstLRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstLRefNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstRRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstRRefNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstVolatile)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstVolatileNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstVolatileLRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstVolatileLRefNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstVolatileRRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::ZeroArgConstVolatileRRefNoexcept)>);

    // ════════════════════════════════════════════════════════════════════════════
    // Positive: multi-argument const member functions
    // ════════════════════════════════════════════════════════════════════════════

    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConst)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstLRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstLRefNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstRRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstRRefNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstVolatile)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstVolatileNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstVolatileLRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstVolatileLRefNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstVolatileRRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::MultiArgConstVolatileRRefNoexcept)>);

    // ════════════════════════════════════════════════════════════════════════════
    // Positive: C-style variadic const member functions
    // ════════════════════════════════════════════════════════════════════════════

    static_assert(ObserverFunction<decltype(&TestClass::VariadicConst)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstLRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstLRefNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstRRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstRRefNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstVolatile)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstVolatileNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstVolatileLRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstVolatileLRefNoexcept)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstVolatileRRef)>);
    static_assert(ObserverFunction<decltype(&TestClass::VariadicConstVolatileRRefNoexcept)>);

    // ════════════════════════════════════════════════════════════════════════════
    // Positive: explicit type-spelling (no decltype) — return type is irrelevant
    // ════════════════════════════════════════════════════════════════════════════

    static_assert(ObserverFunction<void (TestClass::*)() const>);
    static_assert(ObserverFunction<int (TestClass::*)(int, float) const noexcept>);
    static_assert(ObserverFunction<void (TestClass::*)(...) const volatile&&>);
    static_assert(ObserverFunction<float* (TestClass::*)() const&>);

    // ════════════════════════════════════════════════════════════════════════════
    // Negative: mutable (non-const) member functions
    // ════════════════════════════════════════════════════════════════════════════

    static_assert(not ObserverFunction<decltype(&TestClass::MutableNoQual)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableNoexcept)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableLRef)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableLRefNoexcept)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableRRef)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableRRefNoexcept)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableVolatile)>);   // volatile but not const
    static_assert(not ObserverFunction<decltype(&TestClass::MutableVolatileNoexcept)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableVolatileLRef)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableVolatileRRef)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableWithArgs)>);
    static_assert(not ObserverFunction<decltype(&TestClass::MutableVariadic)>);

    // ════════════════════════════════════════════════════════════════════════════
    // Negative: explicit type-spelling for mutable variants
    // ════════════════════════════════════════════════════════════════════════════

    static_assert(not ObserverFunction<void (TestClass::*)()>);            // no qualifiers at all
    static_assert(not ObserverFunction<void (TestClass::*)() volatile>);   // volatile-only, missing const
    static_assert(not ObserverFunction<void (TestClass::*)() &>);          // ref-only, missing const
    static_assert(not ObserverFunction<void (TestClass::*)() noexcept>);   // noexcept-only, missing const
    static_assert(not ObserverFunction<void (TestClass::*)(...)>);         // variadic mutable

    // ════════════════════════════════════════════════════════════════════════════
    // Negative: entities that are simply not pointers to member functions
    // ════════════════════════════════════════════════════════════════════════════

    static_assert(not ObserverFunction<decltype(&TestClass::StaticMethod)>); // void(*)()
    static_assert(not ObserverFunction<decltype(&TestClass::DataMember)>);   // int TestClass::*
    static_assert(not ObserverFunction<void(*)()>);                          // free function pointer
    static_assert(not ObserverFunction<void(*)(int, float)>);
    static_assert(not ObserverFunction<int>);
    static_assert(not ObserverFunction<void*>);
    static_assert(not ObserverFunction<TestClass>);

    struct Incomplete;
    return not ObserverFunction<Incomplete>;
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