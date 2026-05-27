// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemovePointer.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemovePointer;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Non-pointer: type is preserved ───────────────────────────────────────────

    static_assert(Same<RemovePointer<int>, int>);
    static_assert(Same<RemovePointer<const int>, const int>);
    static_assert(Same<RemovePointer<volatile int>, volatile int>);
    static_assert(Same<RemovePointer<const volatile int>, const volatile int>);

    // ── Plain pointer: one level stripped ────────────────────────────────────────

    static_assert(Same<RemovePointer<int*>, int>);
    static_assert(Same<RemovePointer<const int*>, const int>);   // ptr-to-const
    static_assert(Same<RemovePointer<volatile int*>, volatile int>);

    // ── cv-qualified pointer itself: cv on the pointer is stripped with it ────────

    static_assert(Same<RemovePointer<int* const>, int>);
    static_assert(Same<RemovePointer<int* volatile>, int>);
    static_assert(Same<RemovePointer<int* const volatile>, int>);

    // ── Only the *top-most* pointer is removed ───────────────────────────────────

    static_assert(Same<RemovePointer<int**>, int*>);
    static_assert(Same<RemovePointer<int** const>, int*>);
    static_assert(Same<RemovePointer<int* const*>, int* const>); // inner const survives
    static_assert(Same<RemovePointer<int***>, int**>);

    // ── Non-scalar types ─────────────────────────────────────────────────────────

    struct S{};

    static_assert(Same<RemovePointer<S>, S>);
    static_assert(Same<RemovePointer<S*>, S>);

    // ── void pointer ─────────────────────────────────────────────────────────────

    static_assert(Same<RemovePointer<void*>, void>);
    static_assert(Same<RemovePointer<void* const>, void>);
    static_assert(Same<RemovePointer<void* volatile>, void>);
    static_assert(Same<RemovePointer<void* const volatile>, void>);
    static_assert(Same<RemovePointer<void>, void>);

    struct Incomplete;
    return Same<Incomplete, RemovePointer<Incomplete*>>;
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