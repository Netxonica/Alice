// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Greater.hpp"

using Alice::Operator::Greater;
using Alice::Operator::ReturnGreater;

// ---- free-function operator>, found via ADL ----------------------------

struct FreeFunctionCompared{};

bool operator>(FreeFunctionCompared const&, FreeFunctionCompared const&)
{
    return false;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---- exact and heterogeneous matches -----------------------------------

    struct Threshold{};

    struct Comparable
    {
        bool operator>(Comparable const&) const;
    };

    struct Sensor
    {
        bool operator>(Threshold const&) const;
    };

    // ---- absence or mismatch of operator> ----------------------------------

    struct Incomparable{};

    struct OnlyComparesToInt
    {
        bool operator>(int) const;
    };

    struct ConvertsToInt
    {
        operator int() const;
    };

    // ---- return-type edge cases --------------------------------------------

    struct ReturnsInt
    {
        int operator>(ReturnsInt const&) const;
    };

    struct ReturnsVoid
    {
        void operator>(ReturnsVoid const&) const;
    };

    struct ReturnsBoolReference
    {
        bool& operator>(ReturnsBoolReference const&) const;
    };

    // ---- ref-qualification: self/rhs reach operator> as rvalues ------------

    struct LvalueQualifiedComparable
    {
        bool operator>(LvalueQualifiedComparable const&) &;
    };

    struct RvalueQualifiedComparable
    {
        bool operator>(RvalueQualifiedComparable const&) &&;
    };

    // =========================================================================
    // Greater
    // =========================================================================

    static_assert(Greater<int, int>,
    "The built-in operator> for a fundamental type should satisfy Greater.");
    static_assert(Greater<Comparable, Comparable>,
    "A member operator> taking Self itself should satisfy Greater.");
    static_assert(Greater<Sensor, Threshold>,
    "A member operator> taking an unrelated Rhs should satisfy Greater<Self, Rhs>.");
    static_assert(Greater<FreeFunctionCompared, FreeFunctionCompared>,
    "A free operator> found via ADL should satisfy Greater just like a member.");
    static_assert(Greater<OnlyComparesToInt, int>,
    "operator>(int) should satisfy Greater<Self, int>.");
    static_assert(Greater<OnlyComparesToInt, ConvertsToInt>,
    "A Rhs implicitly convertible to the required parameter should still satisfy Greater.");
    static_assert(Greater<ReturnsInt, ReturnsInt>,
    "Greater only requires the expression to be well-formed, regardless of what it returns.");
    static_assert(Greater<ReturnsVoid, ReturnsVoid>,
    "Greater is satisfied even when operator> returns void.");
    static_assert(Greater<RvalueQualifiedComparable, RvalueQualifiedComparable>,
    "self and rhs reach operator> as rvalues, so an && qualified overload is usable.");
    static_assert(not Greater<Incomparable, Incomparable>,
    "A type with no operator> at all must not satisfy Greater.");
    static_assert(not Greater<Sensor, Sensor>,
    "Greater must be checked against the exact Rhs requested, not any overload of Self.");
    static_assert(not Greater<OnlyComparesToInt, OnlyComparesToInt>,
    "There is no conversion from OnlyComparesToInt to int, so this must fail.");
    static_assert(not Greater<LvalueQualifiedComparable, LvalueQualifiedComparable>,
    "self reaches operator> as an rvalue, so an & qualified overload is not usable.");

    // =========================================================================
    // ReturnGreater
    // =========================================================================

    static_assert(ReturnGreater<int, int>,
    "The built-in operator> for a fundamental type returns bool, satisfying the default Return.");
    static_assert(ReturnGreater<Comparable, Comparable>,
    "operator> returning bool by value should satisfy ReturnGreater's default Return.");
    static_assert(ReturnGreater<Sensor, Threshold, bool>,
    "The same holds with Return spelled out explicitly as bool.");
    static_assert(ReturnGreater<FreeFunctionCompared, FreeFunctionCompared>,
    "A free operator> returning bool should satisfy ReturnGreater's default Return.");
    static_assert(ReturnGreater<ReturnsInt, ReturnsInt, int>,
    "operator> returning int should satisfy ReturnGreater when Return is int.");
    static_assert(ReturnGreater<ReturnsVoid, ReturnsVoid, void>,
    "operator> returning void should satisfy ReturnGreater when Return is void.");
    static_assert(ReturnGreater<ReturnsBoolReference, ReturnsBoolReference, bool&>,
    "operator> returning bool& should satisfy ReturnGreater when Return matches the reference "
    "exactly.");
    static_assert(not ReturnGreater<Incomparable, Incomparable>,
    "A type with no operator> at all must not satisfy ReturnGreater either.");
    static_assert(not ReturnGreater<ReturnsInt, ReturnsInt>,
    "operator> returning int must not satisfy ReturnGreater's default Return of bool.");
    static_assert(not ReturnGreater<ReturnsVoid, ReturnsVoid>,
    "operator> returning void must not satisfy ReturnGreater's default Return of bool.");
    static_assert(not ReturnGreater<ReturnsBoolReference, ReturnsBoolReference, bool>,
    "operator> returning bool& is a different type from bool, so this must fail.");

    struct Incomplete;
    return not Greater<Incomplete, Incomplete> and not ReturnGreater<Incomplete, Incomplete>;
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