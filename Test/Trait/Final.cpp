// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Final.hpp"

using Alice::Trait::Final;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Fixtures ─────────────────────────────────────────────────────────────────

    struct NonFinalStruct{};

    struct FinalStruct final{};

    class NonFinalClass{};

    class FinalClass final{};

    class Base{};

    class DerivedFinal final : public Base{};

    class NonFinalDerived : public Base{};

    struct FinalDerivedStruct final : public NonFinalStruct{};

    // ── Final types must satisfy Final ───────────────────────────────────────────

    static_assert(Final<FinalStruct>, "FinalStruct must satisfy Final");
    static_assert(Final<FinalClass>, "FinalClass must satisfy Final");
    static_assert(Final<DerivedFinal>, "A final derived class must satisfy Final");
    static_assert(Final<FinalDerivedStruct>, "A final derived struct must satisfy Final");

    // ── Non-final types must not satisfy Final ───────────────────────────────────

    static_assert(not Final<NonFinalStruct>, "NonFinalStruct must not satisfy Final");
    static_assert(not Final<NonFinalClass>, "NonFinalClass must not satisfy Final");
    static_assert(not Final<Base>, "A non-final base class must not satisfy Final");
    static_assert(not Final<NonFinalDerived>, "A non-final derived class must not satisfy Final");

    // ── Non-class types are never final ──────────────────────────────────────────

    static_assert(not Final<int>, "int must not satisfy Final");
    static_assert(not Final<double>, "double must not satisfy Final");
    static_assert(not Final<int*>, "A raw pointer must not satisfy Final");
    static_assert(not Final<int[]>, "An array type must not satisfy Final");

    struct Incomplete;
    return not Final<Incomplete>;
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