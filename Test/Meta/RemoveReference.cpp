// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemoveReference.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemoveReference;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------------------
    // 1. Non-reference types are left unchanged.
    // ---------------------------------------------------------------------------

    static_assert(Same<RemoveReference<int>, int>);
    static_assert(Same<RemoveReference<double>, double>);
    static_assert(Same<RemoveReference<const float>, const float>);
    static_assert(Same<RemoveReference<volatile int>, volatile int>);
    static_assert(Same<RemoveReference<int*>, int*>);
    static_assert(Same<RemoveReference<const int*>, const int*>);

    // ---------------------------------------------------------------------------
    // 2. Lvalue references are stripped.
    // ---------------------------------------------------------------------------

    static_assert(Same<RemoveReference<int&>, int>);
    static_assert(Same<RemoveReference<const int&>, const int>);
    static_assert(Same<RemoveReference<volatile int&>, volatile int>);
    static_assert(Same<RemoveReference<const volatile int&>, const volatile int>);
    static_assert(Same<RemoveReference<int*&>, int*>);

    // ---------------------------------------------------------------------------
    // 3. Rvalue references are stripped.
    // ---------------------------------------------------------------------------

    static_assert(Same<RemoveReference<int&&>, int>);
    static_assert(Same<RemoveReference<const int&&>, const int>);
    static_assert(Same<RemoveReference<volatile int&&>, volatile int>);
    static_assert(Same<RemoveReference<const volatile int&&>, const volatile int>);
    static_assert(Same<RemoveReference<int*&&>, int*>);

    // ---------------------------------------------------------------------------
    // 4. Multi-level pointers: only an outermost reference is stripped.
    // ---------------------------------------------------------------------------

    static_assert(Same<RemoveReference<int**>, int**>);
    static_assert(Same<RemoveReference<int**&>, int**>);

    // ---------------------------------------------------------------------------
    // 5. Struct / class types (including cv-qualified variants).
    // ---------------------------------------------------------------------------

    struct Dummy{};

    static_assert(Same<RemoveReference<Dummy>, Dummy>);
    static_assert(Same<RemoveReference<const Dummy>, const Dummy>);
    static_assert(Same<RemoveReference<Dummy&>, Dummy>);
    static_assert(Same<RemoveReference<Dummy&&>, Dummy>);
    static_assert(Same<RemoveReference<const Dummy&>, const Dummy>);

    // ---------------------------------------------------------------------------
    // 6. Array types: references-to-arrays are unwrapped; plain arrays survive.
    // ---------------------------------------------------------------------------

    static_assert(Same<RemoveReference<int[4]>, int[4]>);
    static_assert(Same<RemoveReference<int(&)[4]>, int[4]>);
    static_assert(Same<RemoveReference<int(&&)[4]>, int[4]>);
    static_assert(Same<RemoveReference<const int[4]>, const int[4]>);

    // ---------------------------------------------------------------------------
    // 7. Function types: references to functions are stripped; bare types survive.
    // ---------------------------------------------------------------------------

    static_assert(Same<RemoveReference<void()>, void()>);
    static_assert(Same<RemoveReference<void(&)()>, void()>);
    static_assert(Same<RemoveReference<void(&&)()>, void()>);

    struct Incomplete;
    return Same<RemoveReference<Incomplete&>, Incomplete> and Same<RemoveReference<Incomplete&&>,
    Incomplete>;
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