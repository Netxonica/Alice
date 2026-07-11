// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/And.hpp"

using Alice::Operator::And;
using Alice::Operator::ReturnAnd;

// `operator&` implemented as a free function instead of a member.

struct FreeFunctionAnd{};

constexpr FreeFunctionAnd operator&(FreeFunctionAnd const&, FreeFunctionAnd const&) noexcept
{
    return FreeFunctionAnd{};
}

// A flags-style scoped enum: the most common real-world user of a bitwise `operator&`.

enum class Flags
{
    None = 0,
    A = 1,
    B = 2,
};

constexpr Flags operator&(Flags lhs, Flags rhs) noexcept
{
    return static_cast<Flags>(static_cast<int>(lhs) & static_cast<int>(rhs));
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // A type with a member `operator&` taking and returning its own type.

    struct Bitset
    {
        constexpr Bitset operator&(Bitset const&) const noexcept
        {
            return Bitset{};
        }
    };

    // A type with no `operator&` at all.
    
    struct Empty{};

    // `operator&` is only defined for a Rhs other than Self.
    
    struct MaskableByInt
    {
        constexpr MaskableByInt operator&(int) const noexcept
        {
            return MaskableByInt{};
        }
    };

    // `operator&` exists but does not return Self.
    
    struct ReturnsBool
    {
        constexpr bool operator&(ReturnsBool const&) const noexcept
        {
            return false;
        }
    };

    // `operator&` is only usable on an rvalue `*this`, to exercise $forward's value-category
    // handling: passing Self by value should forward `self` as an rvalue, while passing Self as
    // `T&` should forward it as an lvalue.
    
    struct RvalueOnlyAnd
    {
        constexpr RvalueOnlyAnd operator&(RvalueOnlyAnd const&) && noexcept
        {
            return RvalueOnlyAnd{};
        }
    };

    // `operator&` returns a type that is merely convertible to Bitset, not Bitset itself.
    
    struct ConvertibleToBitset
    {
        constexpr operator Bitset() const noexcept
        {
            return Bitset{};
        }
    };

    struct ReturnsConvertible
    {
        constexpr ConvertibleToBitset operator&(ReturnsConvertible const&) const noexcept
        {
            return ConvertibleToBitset{};
        }
    };

    // ---------------------------------------------------------------------------------------------
    // And
    // ---------------------------------------------------------------------------------------------

    static_assert(And<Bitset, Bitset>);
    static_assert(And<MaskableByInt, int>);
    static_assert(And<FreeFunctionAnd, FreeFunctionAnd>);
    static_assert(And<Flags, Flags>);
    static_assert(And<int, int>); // built-in bitwise and satisfies the concept too
    static_assert(And<ReturnsBool, ReturnsBool>); // And does not care what is returned
    static_assert(And<ReturnsConvertible, ReturnsConvertible>);
    static_assert(And<RvalueOnlyAnd, RvalueOnlyAnd>); // Self by value is forwarded as an rvalue
    static_assert(not And<Empty, Empty>); // no operator& at all
    static_assert(not And<MaskableByInt, MaskableByInt>); // only `int` is a valid Rhs
    static_assert(not And<int, int*>); // no built-in bitand between int and pointer
    static_assert(not And<RvalueOnlyAnd&, RvalueOnlyAnd>); // lvalue Self can't hit the && overload

    // ---------------------------------------------------------------------------------------------
    // ReturnAnd - default Return (= Self)
    // ---------------------------------------------------------------------------------------------

    static_assert(ReturnAnd<Bitset, Bitset>);
    static_assert(ReturnAnd<FreeFunctionAnd, FreeFunctionAnd>);
    static_assert(ReturnAnd<Flags, Flags>);
    static_assert(ReturnAnd<int, int>);
    static_assert(not ReturnAnd<ReturnsBool, ReturnsBool>); // returns bool, not ReturnsBool
    static_assert(not ReturnAnd<Empty, Empty>); // no operator& at all
    static_assert(not ReturnAnd<ReturnsConvertible, ReturnsConvertible>); // convertible != Same

    // ---------------------------------------------------------------------------------------------
    // ReturnAnd - explicit Return
    // ---------------------------------------------------------------------------------------------

    static_assert(ReturnAnd<ReturnsBool, ReturnsBool, bool>);
    static_assert(not ReturnAnd<ReturnsBool, ReturnsBool, int>);
    static_assert(ReturnAnd<MaskableByInt, int, MaskableByInt>);
    static_assert(not ReturnAnd<MaskableByInt, int, bool>);
    static_assert(not ReturnAnd<ReturnsConvertible, ReturnsConvertible, Bitset>); // exact match only
    
    struct Incomplete;
    return not And<Incomplete, Incomplete> and not ReturnAnd<Incomplete, Incomplete>;
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