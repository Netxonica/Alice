// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Referenceable.hpp"

using Alice::Trait::Referenceable;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Supporting user-defined types ─────────────────────────────────────────────

    struct S{};

    union U
    {
        int i;
        
        float f;
    };

    enum E
    {
        Ea,
        Eb
    };

    enum class Se
    {
        A,
        B
    };

    // ─────────────────────────────────────────────────────────────────────────────
    // Object types — satisfied via Alice::Trait::Object<Self>
    // ─────────────────────────────────────────────────────────────────────────────

    // Fundamental scalars

    static_assert(Referenceable<bool>);
    static_assert(Referenceable<char>);
    static_assert(Referenceable<char8_t>);
    static_assert(Referenceable<char16_t>);
    static_assert(Referenceable<char32_t>);
    static_assert(Referenceable<wchar_t>);
    static_assert(Referenceable<int>);
    static_assert(Referenceable<unsigned int>);
    static_assert(Referenceable<long>);
    static_assert(Referenceable<long long>);
    static_assert(Referenceable<unsigned long long>);
    static_assert(Referenceable<float>);
    static_assert(Referenceable<double>);
    static_assert(Referenceable<long double>);
    static_assert(Referenceable<decltype(nullptr)>);   // nullptr_t is an object type

    // CV-qualified scalars

    static_assert(Referenceable<const int>);
    static_assert(Referenceable<volatile int>);
    static_assert(Referenceable<const volatile int>);

    // Pointer types (all pointers are objects, including pointer-to-function)

    static_assert(Referenceable<int*>);
    static_assert(Referenceable<int**>);
    static_assert(Referenceable<const int*>);
    static_assert(Referenceable<int* const>);
    static_assert(Referenceable<void*>);
    static_assert(Referenceable<const void*>);
    static_assert(Referenceable<int (*)(int)>);

    // Array types (arrays are objects, including incomplete arrays)

    static_assert(Referenceable<int[5]>);
    static_assert(Referenceable<int[5][3]>);
    static_assert(Referenceable<int[]>);

    // User-defined types

    static_assert(Referenceable<S>);
    static_assert(Referenceable<const S>);
    static_assert(Referenceable<U>);
    static_assert(Referenceable<E>);
    static_assert(Referenceable<Se>);

    // Member pointer types (they are objects regardless of member qualification)

    static_assert(Referenceable<int S::*>);
    static_assert(Referenceable<void (S::*)()>);
    static_assert(Referenceable<void (S::*)() const>);         // ptr-to-const-member is an object
    static_assert(Referenceable<int (S::*)(double) noexcept>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Reference types — satisfied via Alice::Trait::Reference<Self>
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(Referenceable<int&>);
    static_assert(Referenceable<const int&>);
    static_assert(Referenceable<volatile int&>);
    static_assert(Referenceable<const volatile int&>);
    static_assert(Referenceable<int&&>);
    static_assert(Referenceable<const int&&>);
    static_assert(Referenceable<int*&>);
    static_assert(Referenceable<int*&&>);
    static_assert(Referenceable<S&>);
    static_assert(Referenceable<S&&>);
    static_assert(Referenceable<int (&)[5]>);               // reference to array
    static_assert(Referenceable<int (&&)[5]>);              // rvalue reference to array
    static_assert(Referenceable<void (&)()>);               // reference to function
    static_assert(Referenceable<void (&&)()>);              // rvalue reference to function

    // ─────────────────────────────────────────────────────────────────────────────
    // Non-abominable function types — satisfied by the function specialisations
    // ─────────────────────────────────────────────────────────────────────────────

    // Nullary — satisfied by Referenceable<Self(Arguments...)> with an empty pack

    static_assert(Referenceable<void()>);
    static_assert(Referenceable<int()>);
    static_assert(Referenceable<void() noexcept>);
    static_assert(Referenceable<int() noexcept>);

    // With typed parameters

    static_assert(Referenceable<int(int)>);
    static_assert(Referenceable<int(int, double)>);
    static_assert(Referenceable<void(int, double, float)>);
    static_assert(Referenceable<int(int) noexcept>);
    static_assert(Referenceable<int(int, double) noexcept>);

    // Pure C-style variadic — satisfied by Referenceable<Self(...)>

    static_assert(Referenceable<void(...)>);
    static_assert(Referenceable<int(...)>);
    static_assert(Referenceable<void(...) noexcept>);
    static_assert(Referenceable<int(...) noexcept>);

    // ─────────────────────────────────────────────────────────────────────────────
    // void — NOT referenceable (neither Object nor Reference, not a function type)
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(not Referenceable<void>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Abominable function types — NOT referenceable (fall through to the primary
    // template, which returns Object<T> || Reference<T>, both false for these)
    // ─────────────────────────────────────────────────────────────────────────────

    // CV-qualified only

    static_assert(not Referenceable<void() const>);
    static_assert(not Referenceable<void() volatile>);
    static_assert(not Referenceable<void() const volatile>);
    static_assert(not Referenceable<int(int) const>);
    static_assert(not Referenceable<int(int, double) volatile>);

    // Ref-qualified only

    static_assert(not Referenceable<void() &>);
    static_assert(not Referenceable<void() &&>);
    static_assert(not Referenceable<int(int) &>);
    static_assert(not Referenceable<int(int) &&>);

    // CV + ref-qualified

    static_assert(not Referenceable<void() const &>);
    static_assert(not Referenceable<void() const &&>);
    static_assert(not Referenceable<void() volatile &>);
    static_assert(not Referenceable<int(int) const &>);
    static_assert(not Referenceable<int(int) const &&>);

    // noexcept does not rehabilitate an abominable type

    static_assert(not Referenceable<void() const noexcept>);
    static_assert(not Referenceable<void() volatile noexcept>);
    static_assert(not Referenceable<void() & noexcept>);
    static_assert(not Referenceable<void() const & noexcept>);
    static_assert(not Referenceable<int(int) const noexcept>);
    static_assert(not Referenceable<int(int) & noexcept>);
    static_assert(not Referenceable<int(int) const & noexcept>);

    struct Incomplete;
    return Referenceable<Incomplete>;
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