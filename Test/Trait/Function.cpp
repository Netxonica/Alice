// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Function.hpp"

using Alice::Trait::Function;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Positive cases ────────────────────────────────────────────────────────────

    // Basic arities
    static_assert(Function<void()>);
    static_assert(Function<void(int)>);
    static_assert(Function<void(int, float)>);
    static_assert(Function<int()>);
    static_assert(Function<int(int)>);
    static_assert(Function<int*(int*)>);

    // Variadic
    static_assert(Function<void(...)>);
    static_assert(Function<int(int, ...)>);

    // noexcept
    static_assert(Function<void() noexcept>);
    static_assert(Function<int(int) noexcept>);

    // Ref-qualified (these are function types, not reference types)
    static_assert(Function<void() &>);
    static_assert(Function<void() &&>);
    static_assert(Function<void() const &>);

    // cv-qualified function types
    static_assert(Function<void() const>);
    static_assert(Function<void() volatile>);
    static_assert(Function<void() const volatile>);

    // ── Negative cases ────────────────────────────────────────────────────────────

    // Scalars
    static_assert(not Function<void>);
    static_assert(not Function<int>);
    static_assert(not Function<float>);
    static_assert(not Function<bool>);
    static_assert(not Function<char>);
    static_assert(not Function<decltype(nullptr)>);

    // Pointers (including function pointers — those are plain pointer types)
    static_assert(not Function<int*>);
    static_assert(not Function<void*>);
    static_assert(not Function<void(*)()>);
    static_assert(not Function<int(*)(int)>);

    // References
    static_assert(not Function<int&>);
    static_assert(not Function<int&&>);
    static_assert(not Function<void(&)()>);

    // Arrays
    static_assert(not Function<int[4]>);
    static_assert(not Function<int[]>);

    // Class / struct / union / enum

    struct S{};

    union U{};

    enum E{};

    static_assert(not Function<S>);
    static_assert(not Function<U>);
    static_assert(not Function<E>);

    // Member pointers (member function pointers are not function types)
    static_assert(not Function<int S::*>);
    static_assert(not Function<void(S::*)()>);

    struct Incomplete;
    return not Function<Incomplete>;
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