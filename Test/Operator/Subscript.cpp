// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Subscript.hpp"

using Alice::Operator::Subscript;
using Alice::Operator::ReturnSubscript;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─── Fixtures ─────────────────────────────────────────────────────────────────

    struct WithIntSubscript
    {
        int operator[](int)
        {
            return 0;
        }
    };

    struct WithConstSubscript
    {
        int operator[](int) const
        {
            return 0;
        }
    };

    struct WithRefReturnSubscript
    {
        int value{};

        int& operator[](int)
        {
            return value;
        }
    };

    struct WithMultiArgSubscript
    {
        double operator[](int, float)
        {
            return 0.0;
        }
    };

    struct WithLvalueQualifiedSubscript
    {
        int operator[](int) &
        {
            return 0;
        }
    };

    struct WithRvalueQualifiedSubscript
    {
        int operator[](int) &&
        {
            return 0;
        }
    };

    struct Opaque{};

    struct WithOpaqueSubscript
    {
        int operator[](Opaque)
        {
            return 0;
        }
    };

    struct WithNoSubscript{};

    // ─── Subscript: satisfied ─────────────────────────────────────────────────────

    static_assert(Subscript<WithIntSubscript, int>);
    static_assert(Subscript<WithIntSubscript&, int>);
    static_assert(Subscript<WithIntSubscript, double>);                // double→int: implicit conversion
    static_assert(Subscript<WithConstSubscript, int>);
    static_assert(Subscript<const WithConstSubscript, int>);
    static_assert(Subscript<const WithConstSubscript&, int>);
    static_assert(Subscript<WithRefReturnSubscript, int>);
    static_assert(Subscript<WithMultiArgSubscript, int, float>);
    static_assert(Subscript<WithLvalueQualifiedSubscript&, int>);     // &-qualified op: lvalue ref Self works
    static_assert(Subscript<WithRvalueQualifiedSubscript, int>);     // &&-qualified op: rvalue Self works
    static_assert(Subscript<int*, int>);     // built-in pointer subscript

    // ─── Subscript: not satisfied ─────────────────────────────────────────────────

    static_assert(not Subscript<WithNoSubscript, int>);    // no operator[]
    static_assert(not Subscript<WithIntSubscript>);                        // no arg provided; no op[]()
    static_assert(not Subscript<const WithIntSubscript, int>);    // non-const op on const Self
    static_assert(not Subscript<WithLvalueQualifiedSubscript, int>);    // &-qualified op: rvalue Self fails
    static_assert(not Subscript<WithRvalueQualifiedSubscript&, int>);    // &&-qualified op: lvalue Self fails
    static_assert(not Subscript<WithOpaqueSubscript, int>);    // int not convertible to Opaque

    // ─── ReturnSubscript: satisfied ───────────────────────────────────────────────

    static_assert(ReturnSubscript<WithIntSubscript, int, int>);
    static_assert(ReturnSubscript<WithConstSubscript, int, int>);
    static_assert(ReturnSubscript<WithRefReturnSubscript, int&, int>);     // op returns int&
    static_assert(ReturnSubscript<WithMultiArgSubscript, double, int, float>);
    static_assert(ReturnSubscript<int*, int&, int>);     // ptr[i] is lvalue → int&

    // ─── ReturnSubscript: not satisfied ───────────────────────────────────────────

    static_assert(not ReturnSubscript<WithIntSubscript, double, int>);          // int ≠ double
    static_assert(not ReturnSubscript<WithRefReturnSubscript, int, int>);          // int& ≠ int
    static_assert(not ReturnSubscript<WithMultiArgSubscript, float, int, float>);  // double ≠ float
    static_assert(not ReturnSubscript<WithNoSubscript, int, int>);

    struct Incomplete;
    return not Subscript<Incomplete, Incomplete> and not ReturnSubscript<Incomplete, Incomplete,
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