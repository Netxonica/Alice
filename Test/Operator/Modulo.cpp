// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Modulo.hpp"

using Alice::Operator::Modulo;
using Alice::Operator::ReturnModulo;

struct Angle{};

Angle operator%(Angle const&, Angle const&);

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------
    // Section 1 - fundamental types: sanity checks with no user code
    // ---------------------------------------------------------------

    static_assert(Modulo<int, int>, "int has a built-in operator% and must satisfy Modulo");
    static_assert(ReturnModulo<int, int>,
    "int % int returns int, matching the default Return = Self");
    static_assert(ReturnModulo<int, int, int>,
    "int % int returns int, matching an explicit Return = int");
    static_assert(not Modulo<float, float>,
    "there is no built-in operator% for floating-point types");
    static_assert(not Modulo<double, double>,
    "there is no built-in operator% for floating-point types");

    // ---------------------------------------------------------------
    // Section 2 - member operator%, Self and Rhs identical
    // ---------------------------------------------------------------
    
    struct Duration
    {
        Duration operator%(Duration const&) const;
    };

    static_assert(Modulo<Duration, Duration>, "Duration has a member operator% taking a Duration");
    static_assert(ReturnModulo<Duration, Duration>,
    "default Return = Self = Duration matches the actual return type");
    static_assert(ReturnModulo<Duration, Duration, Duration>,
    "explicit Return = Duration matches the actual return type");
    static_assert(not ReturnModulo<Duration, Duration, int>, "operator% returns Duration, not int")
    ;

    // ---------------------------------------------------------------
    // Section 3 - non-member (free function) operator%
    // ---------------------------------------------------------------

    static_assert(Modulo<Angle, Angle>, "Modulo must find operator% via ADL, not just as a member")
    ;
    static_assert(ReturnModulo<Angle, Angle>,
    "the free function returns Angle, matching the default Return");

    // ---------------------------------------------------------------
    // Section 4 - asymmetric Self / Rhs
    // ---------------------------------------------------------------
    
    struct Meters
    {
        Meters operator%(int) const;
    };

    static_assert(Modulo<Meters, int>, "Meters::operator% accepts an int Rhs");
    static_assert(not Modulo<int, Meters>, "int has no operator% overload accepting a Meters Rhs");
    static_assert(not Modulo<Meters, Meters>,
    "Meters::operator% only accepts int, not Meters, and Meters has no conversion to int");
    static_assert(ReturnModulo<Meters, int, Meters>, "Meters::operator%(int) returns Meters");
    static_assert(not ReturnModulo<Meters, int, int>,
    "Meters::operator%(int) returns Meters, not int");

    // ---------------------------------------------------------------
    // Section 5 - no operator% at all (negative baseline)
    // ---------------------------------------------------------------
    
    struct Empty{};

    static_assert(not Modulo<Empty, Empty>, "Empty declares no operator%, member or free");
    static_assert(not ReturnModulo<Empty, Empty>, "Empty declares no operator%, member or free");

    // ---------------------------------------------------------------
    // Section 6 - operator% exists but returns the "wrong" type
    // ---------------------------------------------------------------

    struct Weird
    {
        int operator%(Weird const&) const;
    };

    static_assert(Modulo<Weird, Weird>,
    "Modulo only cares that operator% exists, not what it returns");
    static_assert(not ReturnModulo<Weird, Weird>,
    "default Return = Self = Weird, but operator% actually returns int");
    static_assert(ReturnModulo<Weird, Weird, int>,
    "with an explicit Return = int this matches the actual return type");

    // ---------------------------------------------------------------
    // Section 7 - const-qualification of the implicit object parameter
    // ---------------------------------------------------------------
    
    struct MutableOnly
    {
        MutableOnly operator%(MutableOnly const&);   // not const-qualified
    };

    static_assert(Modulo<MutableOnly, MutableOnly>,
    "a non-const operator% can be called on a non-const Self");
    static_assert(not Modulo<MutableOnly const, MutableOnly>,
    "a non-const operator% cannot be called on a const Self");

    // ---------------------------------------------------------------
    // Section 8 - value-category correctness (this is what $forward buys
    // you over a plain `self % rhs`; these checks fail immediately if a
    // future change drops the forwarding).
    // ---------------------------------------------------------------
    
    struct RvalueOnly
    {
        RvalueOnly operator%(RvalueOnly const&) &&;
    };

    static_assert(Modulo<RvalueOnly, RvalueOnly>,
    "Self=RvalueOnly is forwarded as an rvalue, matching the && overload");
    static_assert(not Modulo<RvalueOnly&, RvalueOnly>,
    "Self=RvalueOnly& is forwarded as an lvalue, which the && overload rejects");
    static_assert(ReturnModulo<RvalueOnly, RvalueOnly>,
    "ReturnModulo must forward Self exactly like Modulo does");

    struct LvalueOnly
    {
        LvalueOnly operator%(LvalueOnly const&) &;
    };

    static_assert(not Modulo<LvalueOnly, LvalueOnly>,
    "Self=LvalueOnly is forwarded as an rvalue, which the & overload rejects");
    static_assert(Modulo<LvalueOnly&, LvalueOnly>,
    "Self=LvalueOnly& is forwarded as an lvalue, matching the & overload");

    struct TakesRvalueRhsOnly
    {
        TakesRvalueRhsOnly operator%(TakesRvalueRhsOnly&&) const;
    };

    static_assert(Modulo<TakesRvalueRhsOnly, TakesRvalueRhsOnly>,
    "Rhs=TakesRvalueRhsOnly is forwarded as an rvalue, binding to T&&");
    static_assert(not Modulo<TakesRvalueRhsOnly, TakesRvalueRhsOnly&>,
    "Rhs=TakesRvalueRhsOnly& is forwarded as an lvalue, which cannot bind to T&&");

    struct TakesLvalueRhsOnly
    {
        TakesLvalueRhsOnly operator%(TakesLvalueRhsOnly&) const;
    };

    static_assert(not Modulo<TakesLvalueRhsOnly, TakesLvalueRhsOnly>,
    "Rhs=TakesLvalueRhsOnly is forwarded as an rvalue, which cannot bind to T&");
    static_assert(Modulo<TakesLvalueRhsOnly, TakesLvalueRhsOnly&>,
    "Rhs=TakesLvalueRhsOnly& is forwarded as an lvalue, binding to T&");

    struct Incomplete;
    return not Modulo<Incomplete, Incomplete> and not ReturnModulo<Incomplete, Incomplete>;
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