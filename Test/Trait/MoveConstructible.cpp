// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/MoveConstructible.hpp"

using Alice::Trait::MoveConstructible;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Positive: trivial aggregate — compiler-generated move ctor
    struct TrivialAggregate{};

    // Positive: explicitly defaulted move ctor
    struct ExplicitMove
    {
        ExplicitMove(ExplicitMove&&) = default;

        ExplicitMove(const ExplicitMove&) = delete;
    };

    // Negative: move ctor deleted
    struct DeletedMoveLivingCopy
    {
        DeletedMoveLivingCopy(DeletedMoveLivingCopy&&) = delete;

        DeletedMoveLivingCopy(const DeletedMoveLivingCopy&) = default;
    };

    // Positive: both ctors present
    struct CopyAndMove
    {
        CopyAndMove(CopyAndMove&&) = default;

        CopyAndMove(const CopyAndMove&) = default;
    };

    // Negative: both move and copy ctors deleted — nothing can construct from &&
    struct ImmovableUncopyable
    {
        ImmovableUncopyable(ImmovableUncopyable&&) = delete;

        ImmovableUncopyable(const ImmovableUncopyable&) = delete;
    };

    // Negative: abstract class — cannot be instantiated even if Sized
    struct AbstractBase
    {
        virtual void f() = 0;
    };

    // ── Positive assertions ──────────────────────────────────────────────────────

    static_assert(MoveConstructible<int>, "int must satisfy MoveConstructible");
    static_assert(MoveConstructible<int*>, "int* must satisfy MoveConstructible");
    static_assert(MoveConstructible<TrivialAggregate>,
    "TrivialAggregate must satisfy MoveConstructible");
    static_assert(MoveConstructible<ExplicitMove>, "ExplicitMove must satisfy MoveConstructible");
    static_assert(MoveConstructible<CopyAndMove>, "CopyAndMove must satisfy MoveConstructible");

    // ── Negative assertions ──────────────────────────────────────────────────────

    static_assert(not MoveConstructible<void>,
    "void must NOT satisfy MoveConstructible (fails Sized)");
    static_assert(not MoveConstructible<ImmovableUncopyable>,
    "ImmovableUncopyable must NOT satisfy MoveConstructible");
    static_assert(not MoveConstructible<AbstractBase>,
    "AbstractBase must NOT satisfy MoveConstructible (not constructible)");
    static_assert(not MoveConstructible<int[4]>,
    "Raw array type must NOT satisfy MoveConstructible (arrays are not constructible)");
    static_assert(not MoveConstructible<DeletedMoveLivingCopy>,
    "DeletedMoveLivingCopy must NOT satisfy MoveConstructible");

    struct Incomplete;
    return not MoveConstructible<Incomplete>;
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