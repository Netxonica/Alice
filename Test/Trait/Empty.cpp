// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Empty.hpp"

using Alice::Trait::Empty;

struct StaticMembersOnly
{
    static int value;

    static void helper();
};

template<class> struct EmptyTemplate{};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Types expected to satisfy Empty ─────────────────────────────────────────

    struct PlainEmpty{};

    struct SingleInheritedEmpty : PlainEmpty{};

    struct MultipleInheritedEmpty : PlainEmpty, StaticMembersOnly{};

    // ── Types expected NOT to satisfy Empty ─────────────────────────────────────

    struct WithDataMember
    {
        int x;
    };

    struct WithVirtualFunction
    {
        virtual void f();
    };

    struct WithVirtualBase : virtual PlainEmpty{};

    union EmptyUnion{};

    union NonEmptyUnion
    {
        int i;
        
        float f;
    };

    // ── Positive cases ───────────────────────────────────────────────────────────

    static_assert(Empty<PlainEmpty>, "A struct with no members must satisfy Empty.");
    static_assert(Empty<const PlainEmpty>, "CV-qualification must not affect the Empty trait.");
    static_assert(Empty<StaticMembersOnly>,
    "Static members alone must not disqualify a class from Empty.");
    static_assert(Empty<SingleInheritedEmpty>,
    "A struct inheriting from one empty base must satisfy Empty.");
    static_assert(Empty<MultipleInheritedEmpty>,
    "A struct inheriting from multiple empty bases must satisfy Empty.");
    static_assert(Empty<EmptyTemplate<int>>,
    "An empty class template instantiation must satisfy Empty.");

    // ── Negative cases ───────────────────────────────────────────────────────────

    static_assert(not Empty<WithDataMember>,
    "A non-static data member must disqualify a class from Empty.");
    static_assert(not Empty<WithVirtualFunction>,
    "A virtual function must disqualify a class from Empty.");
    static_assert(not Empty<WithVirtualBase>,
    "A virtual base class must disqualify a class from Empty.");
    static_assert(not Empty<EmptyUnion>, "A union must not satisfy Empty, even with no members.");
    static_assert(not Empty<NonEmptyUnion>, "A non-empty union must not satisfy Empty.");
    static_assert(not Empty<int>, "Fundamental integer types must not satisfy Empty.");
    static_assert(not Empty<float>, "Fundamental floating-point types must not satisfy Empty.");
    static_assert(not Empty<int*>, "Pointer types must not satisfy Empty.");

    struct Incomplete;
    return not Empty<Incomplete>;
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