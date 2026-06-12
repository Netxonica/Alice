// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Base.hpp"

using Alice::Trait::Base;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    struct Root{};

    struct Branch : Root{};

    struct Leaf : Branch{};

    struct Unrelated{};

    struct PrivateBranch : private Root{};

    struct VirtualBranch : virtual Root{};

    struct MultiBase : Root, Unrelated{};

    // ── Direct inheritance ─────────────────────────────────────────────────────

    static_assert(Base<Root, Branch>);

    // ── Transitive inheritance ─────────────────────────────────────────────────

    static_assert(Base<Root, Leaf>);
    static_assert(Base<Branch, Leaf>);

    // ── Same type must not satisfy Base ───────────────────────────────────────

    static_assert(not Base<Root, Root>);
    static_assert(not Base<Branch, Branch>);
    static_assert(not Base<Leaf, Leaf>);

    // ── Reversed relationships must not satisfy Base ───────────────────────────

    static_assert(not Base<Branch, Root>);
    static_assert(not Base<Leaf, Root>);
    static_assert(not Base<Leaf, Branch>);

    // ── Unrelated types must not satisfy Base ─────────────────────────────────

    static_assert(not Base<Root, Unrelated>);
    static_assert(not Base<Unrelated, Root>);

    // ── Private inheritance: __is_base_of ignores access specifiers ───────────

    static_assert(Base<Root, PrivateBranch>);

    // ── Virtual inheritance ────────────────────────────────────────────────────

    static_assert(Base<Root, VirtualBranch>);

    // ── Multiple inheritance ───────────────────────────────────────────────────

    static_assert(Base<Root, MultiBase>);
    static_assert(Base<Unrelated, MultiBase>);
    static_assert(not Base<MultiBase, Root>);
    static_assert(not Base<MultiBase, Unrelated>);

    struct Incomplete;
    return not Base<Incomplete, Incomplete>;
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