// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/MultiplicationAssignment.hpp"

using Alice::Operator::MultiplicationAssignment;
using Alice::Operator::ReturnMultiplicationAssignment;

template<class Element> struct Box
{
    Element value{};

    Box& operator*=(Element const& factor) noexcept
    {
        value = factor;
        return *this;
    }
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---- Fixtures ------------------------------------------------------

    struct NotMultipliable
    {
        int value{};
    };

    struct Multipliable
    {
        double value{};

        Multipliable& operator*=(double factor) noexcept
        {
            value *= factor;
            return *this;
        }
    };

    // Converts to double, so it should satisfy MultiplyAssignment<Multipliable, _>
    // through an implicit conversion rather than an exact-type match.

    struct ConvertibleToDouble
    {
        operator double() const noexcept
        {
            return 2.0;
        }
    };

    // Overload resolution finds this operator, but calling it is ill-formed,
    // so the concept must reject it rather than treat "found by overload
    // resolution" as sufficient.

    struct DeletedMultiplyAssignment
    {
        DeletedMultiplyAssignment& operator*=(DeletedMultiplyAssignment const&) = delete;
    };

    // Same idea, but ill-formed because of access control instead of deletion.

    struct PrivateMultiplyAssignment
    {
    private:
        PrivateMultiplyAssignment& operator*=(PrivateMultiplyAssignment const&) noexcept
        {
            return *this;
        }
    };

    // Only binds an rvalue.

    struct RvalueOnly
    {
        RvalueOnly& operator*=(RvalueOnly&&) noexcept
        {
            return *this;
        }
    };

    // Only binds a (non-const) lvalue.

    struct LvalueOnly
    {
        LvalueOnly& operator*=(LvalueOnly&) noexcept
        {
            return *this;
        }
    };

    // Binds lvalues and rvalues alike.

    struct ConstRefEither
    {
        ConstRefEither& operator*=(ConstRefEither const&) noexcept
        {
            return *this;
        }
    };

    struct ReturnsVoid
    {
        void operator*=(ReturnsVoid const&) noexcept{}
    };

    struct ReturnsByValue
    {
        ReturnsByValue operator*=(ReturnsByValue const&) noexcept
        {
            return *this;
        }
    };

    struct ReturnsUnrelatedType
    {
        int operator*=(ReturnsUnrelatedType const&) noexcept
        {
            return 0;
        }
    };

    // -------------------------------------------------------------------------
    // MultiplyAssignment: fundamental types
    // -------------------------------------------------------------------------

    static_assert(MultiplicationAssignment<int, int>);
    static_assert(MultiplicationAssignment<int, double>);    // usual arithmetic conversion
    static_assert(MultiplicationAssignment<double, int>);
    static_assert(not MultiplicationAssignment<int, int*>);
    static_assert(not MultiplicationAssignment<int*, int>);

    // -------------------------------------------------------------------------
    // MultiplyAssignment: presence/absence and correctness of the operator
    // -------------------------------------------------------------------------

    static_assert(MultiplicationAssignment<Multipliable, double>);
    static_assert(MultiplicationAssignment<Multipliable, ConvertibleToDouble>);
    static_assert(not MultiplicationAssignment<Multipliable, Multipliable>);    // no such overload
    static_assert(not MultiplicationAssignment<NotMultipliable, int>);
    static_assert(not MultiplicationAssignment<NotMultipliable, NotMultipliable>);

    // A non-const operator*= cannot be invoked through a const Self.

    static_assert(not MultiplicationAssignment<const Multipliable, double>);

    // Deleted/inaccessible operators must not satisfy the concept.

    static_assert(not MultiplicationAssignment<DeletedMultiplyAssignment, DeletedMultiplyAssignment
    >);
    static_assert(not MultiplicationAssignment<PrivateMultiplyAssignment, PrivateMultiplyAssignment
    >);

    // Works through a template instantiation just as well as a concrete type.

    static_assert(MultiplicationAssignment<Box<int>, int>);
    static_assert(MultiplicationAssignment<Box<double>, double>);
    static_assert(not MultiplicationAssignment<Box<int>, Box<int>>);

    // -------------------------------------------------------------------------
    // MultiplyAssignment: $forward must preserve the value category implied by
    // Rhs, not merely the value category of the expression `rhs` itself.
    // -------------------------------------------------------------------------

    static_assert(not MultiplicationAssignment<RvalueOnly, RvalueOnly&>);    // forwards as an lvalue
    static_assert(MultiplicationAssignment<RvalueOnly, RvalueOnly>);      // forwards as an rvalue
    static_assert(MultiplicationAssignment<RvalueOnly, RvalueOnly&&>);    // forwards as an rvalue
    static_assert(MultiplicationAssignment<LvalueOnly, LvalueOnly&>);     // forwards as an lvalue
    static_assert(not MultiplicationAssignment<LvalueOnly, LvalueOnly>);     // forwards as an rvalue
    static_assert(not MultiplicationAssignment<LvalueOnly, LvalueOnly&&>);   // forwards as an rvalue
    static_assert(MultiplicationAssignment<ConstRefEither, ConstRefEither&>);
    static_assert(MultiplicationAssignment<ConstRefEither, ConstRefEither const&>);
    static_assert(MultiplicationAssignment<ConstRefEither, ConstRefEither>);
    static_assert(MultiplicationAssignment<ConstRefEither, ConstRefEither&&>);

    // -------------------------------------------------------------------------
    // ReturnMultiplyAssignment: the default Return matches the conventional
    // `Self&` signature, and the check is an exact type match rather than mere
    // convertibility.
    // -------------------------------------------------------------------------

    static_assert(ReturnMultiplicationAssignment<Multipliable, double>);                    // Return defaults to Self&
    static_assert(ReturnMultiplicationAssignment<Multipliable, double, Multipliable&>);      // same, spelled out
    static_assert(not ReturnMultiplicationAssignment<Multipliable, double, Multipliable>);      // by value != by reference
    static_assert(not ReturnMultiplicationAssignment<Multipliable, double, void>);
    static_assert(not ReturnMultiplicationAssignment<ReturnsVoid, ReturnsVoid>);                // default wants Self&, got void
    static_assert(ReturnMultiplicationAssignment<ReturnsVoid, ReturnsVoid, void>);
    static_assert(not ReturnMultiplicationAssignment<ReturnsByValue, ReturnsByValue>);          // default wants Self&
    static_assert(ReturnMultiplicationAssignment<ReturnsByValue, ReturnsByValue, ReturnsByValue>);
    static_assert(not ReturnMultiplicationAssignment<ReturnsUnrelatedType, ReturnsUnrelatedType>);
    static_assert(ReturnMultiplicationAssignment<ReturnsUnrelatedType, ReturnsUnrelatedType, int>);

    // If the base expression cannot even be formed, no Return can satisfy it.

    static_assert(not ReturnMultiplicationAssignment<NotMultipliable, int>);
    static_assert(not ReturnMultiplicationAssignment<NotMultipliable, int, void>);

    // Fundamental types: built-in *= yields an lvalue of the left operand's type.
    
    static_assert(ReturnMultiplicationAssignment<int, int>);
    static_assert(ReturnMultiplicationAssignment<int, double>);
    static_assert(not ReturnMultiplicationAssignment<int, int, int>);

    struct Incomplete;
    return not MultiplicationAssignment<Incomplete, Incomplete> and not
    ReturnMultiplicationAssignment<Incomplete, Incomplete>;
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