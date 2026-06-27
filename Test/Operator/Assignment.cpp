// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Assignment.hpp"

using Alice::Operator::Assignment;
using Alice::Operator::ReturnAssignment;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // =============================================================================
    // Helper types
    // =============================================================================

    struct Copyable
    {
        Copyable& operator=(const Copyable&)
        {
            return *this;
        }
    };

    struct MoveOnly
    {
        MoveOnly& operator=(MoveOnly&&)
        {
            return *this;
        }

        MoveOnly& operator=(const MoveOnly&) = delete;
    };

    struct FromInt
    {
        FromInt& operator=(int)
        {
            return *this;
        }
    };

    struct ReturnsVoid
    {
        void operator=(const ReturnsVoid&){}
    };

    struct ReturnsInt
    {
        int operator=(const ReturnsInt&)
        {
            return 0;
        }
    };

    struct Unassignable
    {
        Unassignable& operator=(const Unassignable&) = delete;

        Unassignable& operator=(Unassignable&&) = delete;
    };

    struct ImplicitlyConvertibleToInt
    {
        operator int() const
        {
            return 0;
        }
    };

    // =============================================================================
    // Assignment
    // =============================================================================

    // --- Positive: fundamental types in every value category ---

    static_assert(Assignment<int, int>);
    static_assert(Assignment<int, int&>);
    static_assert(Assignment<int, const int&>);
    static_assert(Assignment<int, int&&>);
    static_assert(Assignment<int*, int*>);

    // --- Positive: implicit conversion counts as a valid source ---

    static_assert(Assignment<double, float>);
    static_assert(Assignment<int, ImplicitlyConvertibleToInt>);

    // --- Positive: user-defined operator= ---

    static_assert(Assignment<Copyable, Copyable&>);
    static_assert(Assignment<Copyable, const Copyable&>);
    static_assert(Assignment<MoveOnly, MoveOnly&&>);
    static_assert(Assignment<FromInt, int>);
    static_assert(Assignment<FromInt, const int&>);

    // --- Positive: Assignment does not constrain the return type ---

    static_assert(Assignment<ReturnsVoid, const ReturnsVoid&>);
    static_assert(Assignment<ReturnsInt, const ReturnsInt&>);

    // --- Negative: deleted or absent operator= ---

    static_assert(not Assignment<Unassignable, const Unassignable&>);
    static_assert(not Assignment<Unassignable, Unassignable&&>);
    static_assert(not Assignment<MoveOnly, const MoveOnly&>);   // copy-assign is deleted
    static_assert(not Assignment<Copyable, int>);               // no operator=(int) exists

    // --- Negative: const-qualified Self cannot be assigned to ---

    static_assert(not Assignment<const int, int>);

    // =============================================================================
    // ReturnAssignment
    // =============================================================================

    // --- Positive: default Return = Self&, matching the conventional pattern ---

    static_assert(ReturnAssignment<int, int>);
    static_assert(ReturnAssignment<int, const int&>);
    static_assert(ReturnAssignment<Copyable, const Copyable&>);
    static_assert(ReturnAssignment<MoveOnly, MoveOnly&&>);
    static_assert(ReturnAssignment<FromInt, int>);

    // --- Positive: explicit Return matching the operator's actual return type ---

    static_assert(ReturnAssignment<int, int, int&>);
    static_assert(ReturnAssignment<Copyable, const Copyable&, Copyable&>);
    static_assert(ReturnAssignment<ReturnsVoid, const ReturnsVoid&, void>);
    static_assert(ReturnAssignment<ReturnsInt, const ReturnsInt&, int>);

    // --- Negative: Return type mismatch (wrong explicit type) ---

    static_assert(not ReturnAssignment<Copyable, const Copyable&, void>);
    static_assert(not ReturnAssignment<Copyable, const Copyable&, int>);
    static_assert(not ReturnAssignment<ReturnsInt, const ReturnsInt&, void>);

    // --- Negative: operator returns wrong type for the default Return = Self& ---
    
    static_assert(not ReturnAssignment<ReturnsVoid, const ReturnsVoid&>);   // void != ReturnsVoid&
    static_assert(not ReturnAssignment<ReturnsInt, const ReturnsInt&>);    // int  != ReturnsInt&

    // --- Negative: no valid assignment at all ---
    
    static_assert(not ReturnAssignment<Unassignable, const Unassignable&>);
    static_assert(not ReturnAssignment<Unassignable, const Unassignable&, void>);
    static_assert(not ReturnAssignment<MoveOnly, const MoveOnly&>);

    struct Incomplete;
    return not Assignment<Incomplete, Incomplete> and not ReturnAssignment<Incomplete, Incomplete>;
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