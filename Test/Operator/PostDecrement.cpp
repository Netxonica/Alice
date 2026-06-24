// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/PostDecrement.hpp"

using Alice::Operator::PostDecrement;
using Alice::Operator::ReturnPostDecrement;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // operator--(int) with no ref-qualifier → callable on both lvalues and rvalues
    struct Decrementable
    {
        Decrementable operator--(int)
        {
            return *this;
        }
    };

    // operator--(int) is lvalue-ref-qualified → only callable on lvalues
    struct LvalueDecrementable
    {
        LvalueDecrementable operator--(int) &
        {
            return *this;
        }
    };

    // Only pre-decrement; no post-decrement overload
    struct PreDecrementOnly
    {
        PreDecrementOnly& operator--()
        {
            return *this;
        }
    };

    struct NotDecrementable{};

    // Post-decrement returns a type other than Self
    struct ReturnsIntOnDecrement
    {
        int operator--(int)
        {
            return 0;
        }
    };

    // Post-decrement returns void
    struct ReturnsVoidOnDecrement
    {
        void operator--(int){}
    };

    // ─── PostDecrement ───────────────────────────────────────────────────────────

    // Basic positive cases

    static_assert(PostDecrement<Decrementable>);
    static_assert(PostDecrement<Decrementable&>);

    // Lvalue-ref-qualified operator:
    //   $forward<T>(self)  → xvalue → ill-formed (& method cannot bind to rvalue)
    //   $forward<T&>(self) → lvalue → well-formed

    static_assert(not PostDecrement<LvalueDecrementable>);
    static_assert(PostDecrement<LvalueDecrementable&>);

    // Pre-decrement only → no operator--(int) → concept never satisfied

    static_assert(not PostDecrement<PreDecrementOnly>);
    static_assert(not PostDecrement<PreDecrementOnly&>);

    // No operator at all

    static_assert(not PostDecrement<NotDecrementable>);
    static_assert(not PostDecrement<NotDecrementable&>);

    // Built-in integers: $forward<int> yields rvalue, which cannot be post-decremented
    // $forward<int&> yields an lvalue, which can

    static_assert(not PostDecrement<int>);
    static_assert(PostDecrement<int&>);

    // Built-in pointers: same value-category rule applies

    static_assert(not PostDecrement<int*>);
    static_assert(PostDecrement<int*&>);

    // Return type is irrelevant for PostDecrement

    static_assert(PostDecrement<ReturnsIntOnDecrement>);
    static_assert(PostDecrement<ReturnsVoidOnDecrement>);

    // ─── ReturnPostDecrement ─────────────────────────────────────────────────────

    // Default Return = Self; operator returns Decrementable by value → matches

    static_assert(ReturnPostDecrement<Decrementable>);
    static_assert(ReturnPostDecrement<Decrementable, Decrementable>);

    // Explicit type mismatches against Decrementable's actual return type

    static_assert(not ReturnPostDecrement<Decrementable, int>);
    static_assert(not ReturnPostDecrement<Decrementable, void>);

    // When Self = T&, default Return = T& but operator returns T (prvalue) → mismatch

    static_assert(not ReturnPostDecrement<Decrementable&>);
    static_assert(ReturnPostDecrement<Decrementable&, Decrementable>);

    // Operator returns int; default Return = Self = ReturnsIntOnDecrement → mismatch

    static_assert(not ReturnPostDecrement<ReturnsIntOnDecrement>);
    static_assert(ReturnPostDecrement<ReturnsIntOnDecrement, int>);
    static_assert(not ReturnPostDecrement<ReturnsIntOnDecrement, ReturnsIntOnDecrement>);

    // Operator returns void; default Return = Self = ReturnsVoidOnDecrement → mismatch

    static_assert(not ReturnPostDecrement<ReturnsVoidOnDecrement>);
    static_assert(ReturnPostDecrement<ReturnsVoidOnDecrement, void>);
    static_assert(not ReturnPostDecrement<ReturnsVoidOnDecrement, ReturnsVoidOnDecrement>);

    // Built-in int&: post-decrement yields int (prvalue copy), not int&

    static_assert(not ReturnPostDecrement<int&>);
    static_assert(ReturnPostDecrement<int&, int>);

    // No operator → never satisfied, regardless of the expected Return

    static_assert(not ReturnPostDecrement<NotDecrementable>);
    static_assert(not ReturnPostDecrement<NotDecrementable, NotDecrementable>);
    static_assert(not ReturnPostDecrement<NotDecrementable, int>);

    struct Incomplete;
    return not PostDecrement<Incomplete> and not ReturnPostDecrement<Incomplete>;
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