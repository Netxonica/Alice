// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/XorAssignment.hpp"

using Alice::Operator::XorAssignment;
using Alice::Operator::ReturnXorAssignment;

// xor-assignment implemented as a free (non-member) function instead of a member.
    
struct FreeFunctionSelf{};

FreeFunctionSelf& operator^=(FreeFunctionSelf& self, int) noexcept
{
    return self;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Fixtures -----------------------------------------------------------

    // The "usual" shape: a member operator^= taking int by value, returning Self&.

    struct Usual
    {
        Usual& operator^=(int) noexcept
        {
            return *this;
        }
    };

    // No xor-assignment operator at all.

    struct Bare{};

    // xor-assignment exists, but returns void instead of Self&.

    struct ReturnsVoid
    {
        void operator^=(int) noexcept{}
    };

    // xor-assignment exists, but returns by value instead of by reference.

    struct ReturnsByValue
    {
        ReturnsByValue operator^=(int) noexcept
        {
            return *this;
        }
    };

    // A non-arithmetic Rhs, to confirm the concept isn't secretly arithmetic-only.

    struct Rhs{};

    struct AcceptsCustomRhs
    {
        AcceptsCustomRhs& operator^=(Rhs const&) noexcept
        {
            return *this;
        }
    };

    // Nothing converts to Rhs, so AcceptsCustomRhs must reject this.
    
    struct Unrelated{};

    // A Self whose operator only accepts an rvalue Rhs, to exercise $forward rather
    // than a plain reference to the requires-expression's rhs parameter.
    
    struct RvalueOnlyRhs{};

    struct AcceptsRvalueOnly
    {
        AcceptsRvalueOnly& operator^=(RvalueOnlyRhs&&) noexcept
        {
            return *this;
        }
    };

    // Has a sibling compound-assignment operator, but not operator^= itself. Guards
    // against a copy-pasted concept accidentally checking xor_eq/or_eq/and_eq et al.

    struct HasOrAssignOnly
    {
        HasOrAssignOnly& operator|=(int) noexcept
        {
            return *this;
        }
    };

    // --- XorAssignment: is `self xor_eq $forward(rhs)` well-formed? -----------------

    // Ordinary member operator, and built-in arithmetic types (which get operator^=
    // for free), both satisfy the concept for the argument type they accept ...

    static_assert(XorAssignment<Usual, int>);
    static_assert(XorAssignment<int, int>);

    // ... regardless of what the operator returns: Self&, void, or by value all count,
    // since XorAssignment only checks that the expression compiles.

    static_assert(XorAssignment<ReturnsVoid, int>);
    static_assert(XorAssignment<ReturnsByValue, int>);

    // A free-function operator^= is found too (ordinary overload resolution/ADL).

    static_assert(XorAssignment<FreeFunctionSelf, int>);

    // Rhs need not be an arithmetic type.

    static_assert(XorAssignment<AcceptsCustomRhs, Rhs>);

    // $forward(rhs) forwards rhs as an rvalue when Rhs is a non-reference type, so a
    // Self that only accepts an rvalue Rhs is satisfied ...

    static_assert(XorAssignment<AcceptsRvalueOnly, RvalueOnlyRhs>);

    // No operator^= at all: never satisfied.

    static_assert(not XorAssignment<Bare, int>);

    // An operator^= exists, but not for a Rhs with no implicit conversion to what it wants.

    static_assert(not XorAssignment<AcceptsCustomRhs, Unrelated>);
    static_assert(not XorAssignment<int, Bare>);

    // ... but when Rhs is an lvalue-reference type, $forward(rhs) forwards rhs as an
    // lvalue, so the rvalue-only overload is correctly rejected.

    static_assert(not XorAssignment<AcceptsRvalueOnly, RvalueOnlyRhs&>);

    // Having operator|= is not the same as having operator^=.

    static_assert(not XorAssignment<HasOrAssignOnly, int>);

    // A const Self can't call a (non-const, mutating) operator^=.

    static_assert(not XorAssignment<const Usual, int>);

    // --- ReturnXorAssignment: same expression, plus its exact result type -----------

    // With the default Return of Self&, ReturnXorAssignment agrees with XorAssignment
    // for types following the usual "return *this by reference" convention.

    static_assert(ReturnXorAssignment<Usual, int>);
    static_assert(ReturnXorAssignment<int, int>);
    static_assert(ReturnXorAssignment<FreeFunctionSelf, int>);

    // It rejects operators that are otherwise well-formed but return something other
    // than Self& -- these all satisfy XorAssignment above, yet fail here.

    static_assert(not ReturnXorAssignment<ReturnsVoid, int>);
    static_assert(not ReturnXorAssignment<ReturnsByValue, int>);
    static_assert(not ReturnXorAssignment<Bare, int>);

    // Supplying the actual return type as Return recovers a match.

    static_assert(ReturnXorAssignment<ReturnsVoid, int, void>);
    static_assert(ReturnXorAssignment<ReturnsByValue, int, ReturnsByValue>);

    // Trait::Same has to match exactly: asking for Self instead of Self& fails even
    // though Usual's operator does return *this.

    static_assert(not ReturnXorAssignment<Usual, int, Usual>);

    struct Incomplete;
    return not XorAssignment<Incomplete, Incomplete> and not ReturnXorAssignment<Incomplete,
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