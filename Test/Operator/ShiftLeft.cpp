// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/ShiftLeft.hpp"

using Alice::Operator::ShiftLeft;
using Alice::Operator::ReturnShiftLeft;

// ---------------------------------------------------------------
// Non-member operator<< (found via ADL) must be detected too --
// the concept has no bias toward member functions.
// ---------------------------------------------------------------

struct NonMemberShift{};

NonMemberShift operator<<(NonMemberShift lhs, int)
{
    return lhs;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------
    // Fundamental types: builtin << must satisfy ShiftLeft.
    // ---------------------------------------------------------------

    static_assert(ShiftLeft<int, int>);
    static_assert(ShiftLeft<unsigned, int>);

    // ---------------------------------------------------------------
    // A type with no operator<< at all satisfies neither concept, for
    // any requested Return.
    // ---------------------------------------------------------------

    struct NoShift{};

    static_assert(not ShiftLeft<NoShift, int>);
    static_assert(not ReturnShiftLeft<NoShift, int>);
    static_assert(not ReturnShiftLeft<NoShift, int, void>);

    // ---------------------------------------------------------------
    // A plain member operator<< returning Self by value: the common
    // case, where the default Return template argument (Return = Self)
    // should just work without being spelled out.
    // ---------------------------------------------------------------

    struct ValueReturnShift
    {
        ValueReturnShift operator<<(int) const
        {
            return *this;
        }
    };

    static_assert(ShiftLeft<ValueReturnShift, int>);
    static_assert(ShiftLeft<ValueReturnShift&, int>);
    static_assert(ShiftLeft<const ValueReturnShift&, int>);
    static_assert(ReturnShiftLeft<ValueReturnShift, int>);
    static_assert(ReturnShiftLeft<ValueReturnShift, int, ValueReturnShift>);
    static_assert(not ReturnShiftLeft<ValueReturnShift, int, int>);

    // ---------------------------------------------------------------
    // ShiftLeft does not care what operator<< returns; ReturnShiftLeft
    // does, and the match is *exact* (Trait::Same), not merely
    // convertible. A void-returning operator<< shows both halves of
    // that at once.
    // ---------------------------------------------------------------

    struct VoidShift
    {
        void operator<<(int){}
    };

    static_assert(ShiftLeft<VoidShift, int>);
    static_assert(not ReturnShiftLeft<VoidShift, int>);        // default Return = VoidShift, actual = void
    static_assert(ReturnShiftLeft<VoidShift, int, void>);

    // ---------------------------------------------------------------
    // The classic "fluent" operator<< returns Self&, not Self. Because
    // the compound requirement checks decltype((expr)) -- which is a
    // reference for a reference-returning call -- this only satisfies
    // ReturnShiftLeft when Return is explicitly the reference type.
    // The default (Return = Self, by value) must fail here: this is
    // the easiest mistake to make when using this concept.
    // ---------------------------------------------------------------

    struct ChainableShift
    {
        ChainableShift& operator<<(int)
        {
            return *this;
        }
    };

    static_assert(ShiftLeft<ChainableShift, int>);
    static_assert(ReturnShiftLeft<ChainableShift, int, ChainableShift&>);
    static_assert(not ReturnShiftLeft<ChainableShift, int>);
    static_assert(not ReturnShiftLeft<ChainableShift, int, ChainableShift>);

    // ---------------------------------------------------------------
    // Self's value category is not fixed by the concept -- $forward
    // propagates whatever Self is instantiated with -- so ref-qualified
    // overloads of operator<< are visible to (and distinguished by)
    // both concepts.
    // ---------------------------------------------------------------

    struct LvalueOnlyShift
    {
        void operator<<(int) &{}
    };

    static_assert(ShiftLeft<LvalueOnlyShift&, int>);
    static_assert(not ShiftLeft<LvalueOnlyShift, int>);

    struct RvalueOnlyShift
    {
        void operator<<(int) &&{}
    };

    static_assert(ShiftLeft<RvalueOnlyShift, int>);
    static_assert(not ShiftLeft<RvalueOnlyShift&, int>);

    // ---------------------------------------------------------------
    // The same holds for Rhs: an operator<< that only accepts an
    // lvalue (or only an rvalue) is only detected for a matching Rhs
    // value category.
    // ---------------------------------------------------------------

    struct Token{};

    struct AcceptsLvalueToken
    {
        void operator<<(Token&){}
    };

    struct AcceptsRvalueToken
    {
        void operator<<(Token&&){}
    };

    static_assert(ShiftLeft<AcceptsLvalueToken, Token&>);
    static_assert(not ShiftLeft<AcceptsLvalueToken, Token>);
    static_assert(ShiftLeft<AcceptsRvalueToken, Token>);
    static_assert(not ShiftLeft<AcceptsRvalueToken, Token&>);

    // ---------------------------------------------------------------
    // An operator<< that exists but can never actually be called --
    // deleted, or inaccessible from outside the class -- must not
    // satisfy the concept. A naive detection idiom could get either of
    // these wrong; a requires-expression should not.
    // ---------------------------------------------------------------

    struct DeletedShift
    {
        void operator<<(int) = delete;
    };

    static_assert(not ShiftLeft<DeletedShift, int>);

    class InaccessibleShift
    {
        void operator<<(int){}
    };

    static_assert(not ShiftLeft<InaccessibleShift, int>);
    static_assert(ShiftLeft<NonMemberShift, int>);

    // ---------------------------------------------------------------
    // Rhs matters as much as Self: an operator<< accepting one type
    // must not be satisfied for an unrelated Rhs with no conversion.
    // ---------------------------------------------------------------

    struct OnlyAcceptsInt
    {
        void operator<<(int){}
    };

    struct Unrelated{};

    static_assert(ShiftLeft<OnlyAcceptsInt, int>);
    static_assert(not ShiftLeft<OnlyAcceptsInt, Unrelated>);

    struct Incomplete;
    return not ShiftLeft<Incomplete, Incomplete> and not ReturnShiftLeft<Incomplete, Incomplete>;
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