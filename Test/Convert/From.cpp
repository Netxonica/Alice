// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Convert/From.hpp"

using Alice::Convert::From;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ===========================================================================
    // Fixtures
    // ===========================================================================

    // --- Happy-path types -------------------------------------------------------

    // Converts itself from itself.
    struct IntWrapper
    {
        int value;

        [[nodiscard]] static IntWrapper From(IntWrapper v) noexcept
        {
            return v;
        }
    };

    // Converts from a different (also Sized) type.
    struct DoubleWrapper
    {
        double value;

        [[nodiscard]] static DoubleWrapper From(IntWrapper v) noexcept
        {
            return {static_cast<double>(v.value)};
        }

        [[nodiscard]] static DoubleWrapper From(DoubleWrapper v) noexcept
        {
            return v;
        }
    };

    // Trivially empty type that still satisfies Sized.
    struct Empty
    {
        [[nodiscard]] static Empty From(Empty) noexcept
        {
            return {};
        }
    };

    // --- Negative-case types ----------------------------------------------------

    // No From method at all.
    struct NoFrom
    {
        int x;
    };

    // From is an instance method, not a static one  →  Self::From(t) is ill-formed.
    struct InstanceFrom
    {
        [[nodiscard]] InstanceFrom From(InstanceFrom) const noexcept
        {
            return *this;
        }
    };

    // From exists but returns the wrong type.
    struct BadReturn
    {
        [[nodiscard]] static NoFrom From(BadReturn) noexcept
        {
            return {};
        }
    };

    // From exists and returns Self, but accepts the wrong parameter type.
    struct WrongParam
    {
        [[nodiscard]] static WrongParam From(int) noexcept
        {
            return {};
        }
    };

    // From is private  →  the call expression in the concept is ill-formed.
    struct PrivateFrom
    {
    private:
        [[nodiscard]] static PrivateFrom From(PrivateFrom) noexcept
        {
            return {};
        }
    };

    // Incomplete type: violates Alice::Marker::Sized for both Self and T positions.
    struct Incomplete;

    // ===========================================================================
    // Static assertions
    // ===========================================================================

    // --- Positive cases ---------------------------------------------------------

    // A type that converts from itself must satisfy the concept.

    static_assert(From<IntWrapper, IntWrapper>,
    "IntWrapper -> IntWrapper: same-type self-conversion must satisfy From");

    // A type may convert from a different Sized type.

    static_assert(From<DoubleWrapper, IntWrapper>,
    "DoubleWrapper <- IntWrapper: cross-type conversion must satisfy From");

    // A type that converts from itself must also satisfy when Self == T trivially.

    static_assert(From<DoubleWrapper, DoubleWrapper>,
    "DoubleWrapper -> DoubleWrapper: self-conversion must satisfy From");

    // Trivially empty types still satisfy Sized and may expose From.

    static_assert(From<Empty, Empty>, "Empty -> Empty: zero-size complete type must satisfy From");

    // --- Negative cases ---------------------------------------------------------

    // Self has no From method at all.

    static_assert(not From<NoFrom, IntWrapper>,
    "NoFrom: absence of From method must not satisfy concept");

    // T has no From method, but here T is the source—that's fine only if Self has
    // From(T).  IntWrapper::From takes IntWrapper, not NoFrom, so this must fail.
    
    static_assert(not From<IntWrapper, NoFrom>,
    "IntWrapper <- NoFrom: IntWrapper has no From(NoFrom) overload");

    // From is an instance member; Self::From(t) must be ill-formed.
    
    static_assert(not From<InstanceFrom, InstanceFrom>,
    "InstanceFrom: non-static From must not satisfy concept");

    // From returns the wrong type (NoFrom instead of BadReturn).

    static_assert(not From<BadReturn, BadReturn>,
    "BadReturn: From returning wrong type must not satisfy concept");

    // From exists but does not accept the source type.

    static_assert(not From<WrongParam, IntWrapper>,
    "WrongParam: From(int) does not accept IntWrapper");

    // From is inaccessible (private linkage).

    static_assert(not From<PrivateFrom, PrivateFrom>,
    "PrivateFrom: private From must not satisfy concept");

    // Incomplete Self violates Marker::Sized even if T is fine.

    static_assert(not From<Incomplete, IntWrapper>,
    "Incomplete Self: unsized Self must not satisfy concept");

    // Incomplete T violates Marker::Sized even if Self is fine.

    static_assert(not From<IntWrapper, Incomplete>,
    "Incomplete T: unsized T must not satisfy concept");

    // Both positions incomplete.

    static_assert(not From<Incomplete, Incomplete>, "Both incomplete: must not satisfy concept");

    return not From<Incomplete, Incomplete>;
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