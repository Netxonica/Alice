// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/PreDecrement.hpp"

using Alice::Operator::PreDecrement;
using Alice::Operator::ReturnPreDecrement;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─── Test types ──────────────────────────────────────────────────────────────

    struct Decrementable
    {
        Decrementable& operator--()
        {
            return *this;
        }
    };

    struct DecrementableBoth
    {
        DecrementableBoth& operator--()
        {
            return *this;
        }

        DecrementableBoth operator--(int)
        {
            return *this;
        }
    };

    struct DecrementableVoidReturn
    {
        void operator--(){}
    };

    struct DecrementableIntReturn
    {
        int operator--()
        {
            return 0;
        }
    };

    // $forward yields an rvalue; a &&-qualified operator-- can bind to it.
    struct DecrementableRvalueOnly
    {
        DecrementableRvalueOnly& operator--() &&
        {
            return *this;
        }
    };

    // $forward yields an rvalue; a &-qualified operator-- cannot bind to it.
    struct DecrementableLvalueOnly
    {
        DecrementableLvalueOnly& operator--() &
        {
            return *this;
        }
    };

    struct PostDecrementOnly
    {
        PostDecrementOnly operator--(int)
        {
            return *this;
        }
    };

    struct NonDecrementable{};

    // ─── Alice::Operator::PreDecrement ───────────────────────────────────────────

    // Satisfied — pre-decrement is valid; return type is unconstrained.

    static_assert(PreDecrement<Decrementable>);
    static_assert(PreDecrement<DecrementableBoth>);
    static_assert(PreDecrement<DecrementableVoidReturn>);
    static_assert(PreDecrement<DecrementableIntReturn>);
    static_assert(PreDecrement<DecrementableRvalueOnly>);  // && binds to rvalue from $forward

    // Not satisfied — no pre-decrement callable on the forwarded rvalue.

    static_assert(not PreDecrement<NonDecrementable>);
    static_assert(not PreDecrement<PostDecrementOnly>);
    static_assert(not PreDecrement<DecrementableLvalueOnly>);  // & rejects rvalue from $forward
    static_assert(not PreDecrement<const Decrementable>);      // non-const operator-- on const object

    // ─── Alice::Operator::ReturnPreDecrement ─────────────────────────────────────

    // Satisfied — default Return = Self&, operator-- returns Self&.

    static_assert(ReturnPreDecrement<Decrementable>);
    static_assert(ReturnPreDecrement<DecrementableRvalueOnly>);

    // Satisfied — explicit Return matches actual return type exactly.

    static_assert(ReturnPreDecrement<Decrementable, Decrementable&>);
    static_assert(ReturnPreDecrement<DecrementableRvalueOnly, DecrementableRvalueOnly&>);
    static_assert(ReturnPreDecrement<DecrementableIntReturn, int>);
    static_assert(ReturnPreDecrement<DecrementableVoidReturn, void>);

    // Not satisfied — default Return = Self&, but operator-- does not return Self&.

    static_assert(not ReturnPreDecrement<DecrementableVoidReturn>);
    static_assert(not ReturnPreDecrement<DecrementableIntReturn>);

    // Not satisfied — explicit Return does not match the actual return type.

    static_assert(not ReturnPreDecrement<Decrementable, Decrementable>);  // value ≠ reference
    static_assert(not ReturnPreDecrement<Decrementable, int>);            // unrelated type

    // Not satisfied — no callable pre-decrement at all.

    static_assert(not ReturnPreDecrement<NonDecrementable>);
    static_assert(not ReturnPreDecrement<NonDecrementable, void>);
    static_assert(not ReturnPreDecrement<PostDecrementOnly>);
    static_assert(not ReturnPreDecrement<DecrementableLvalueOnly>);
    static_assert(not ReturnPreDecrement<DecrementableLvalueOnly, DecrementableLvalueOnly&>);
    static_assert(not ReturnPreDecrement<const Decrementable>);
    static_assert(not ReturnPreDecrement<const Decrementable, const Decrementable&>);

    struct Incomplete;
    return not PreDecrement<Incomplete> and not ReturnPreDecrement<Incomplete>;
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