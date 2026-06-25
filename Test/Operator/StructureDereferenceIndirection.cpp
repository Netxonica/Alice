// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/StructureDereferenceIndirection.hpp"

using Alice::Operator::StructureDereferenceIndirection;
using Alice::Operator::ReturnStructureDereferenceIndirection;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // =========================================================================
    // Test support types
    // =========================================================================

    struct MemberA{};

    struct MemberB{};

    struct Target
    {
        MemberA a;
 
        MemberB b;
 
        int i;
    };

    // Unqualified operator->* — callable on both lvalue and rvalue Self.
    // Overloaded for every member type of Target to verify the Rhs parameter
    // is not conflated.

    struct BasicPtr
    {
        Target* raw;

        MemberA& operator->*(MemberA Target::* m)
        {
            return raw->*m;
        }

        MemberB& operator->*(MemberB Target::* m)
        {
            return raw->*m;
        }
        int& operator->*(int Target::* m)
        {
            return raw->*m;
        }
    };

    // operator->* that returns *this, so its return type is exactly Self&.
    // This is the key fixture for exercising the default Return = Self& parameter.

    struct ChainPtr
    {
        Target* raw;

        ChainPtr& operator->*(MemberA Target::*)
        {
            return *this;
        }
    };

    // Lvalue-ref-qualified operator->* — only callable when Self is forwarded
    // as an lvalue (i.e. Self = LvalPtr&).

    struct LvalPtr
    {
        Target* raw;

        MemberA& operator->*(MemberA Target::* m) &
        {
            return raw->*m;
        }
    };

    // Rvalue-ref-qualified operator->* — only callable when Self is forwarded
    // as an rvalue (i.e. Self = RvalPtr, which $forward casts to RvalPtr&&).

    struct RvalPtr
    {
        Target* raw;

        MemberA& operator->*(MemberA Target::* m) &&
        {
            return raw->*m;
        }
    };

    // Const-qualified operator->*, returns a const reference because raw points
    // to const Target.
    
    struct ConstPtr
    {
        const Target* raw;

        const MemberA& operator->*(MemberA Target::* m) const
        {
            return raw->*m;
        }
    };

    // operator->* that returns void — legal, and the concept must accept it.

    struct VoidPtr
    {
        Target* raw;
        void operator->*(MemberA Target::*){}
    };

    // No operator->* at all.
    
    struct Plain{};

    // =========================================================================
    // StructureDereferenceIndirection
    // =========================================================================

    // --- Positive: unqualified operator->*, lvalue Self, multiple Rhs types ---
    
    static_assert(StructureDereferenceIndirection<BasicPtr&, MemberA Target::*&>);
    static_assert(StructureDereferenceIndirection<BasicPtr&, MemberB Target::*&>);
    static_assert(StructureDereferenceIndirection<BasicPtr&, int Target::*&>);

    // --- Positive: unqualified operator->*, non-ref Self ($forward gives rvalue) ---
    
    static_assert(StructureDereferenceIndirection<BasicPtr, MemberA Target::*>);

    // --- Positive: built-in ->* for raw pointers ---
    
    static_assert(StructureDereferenceIndirection<Target*&, MemberA Target::*&>);
    static_assert(StructureDereferenceIndirection<Target*&, int Target::*&>);
    static_assert(StructureDereferenceIndirection<Target*, MemberA Target::*>); // non-ref → rvalue

    // --- Positive: const operator->* reachable from both const and non-const Self ---
    
    static_assert(StructureDereferenceIndirection<ConstPtr&, MemberA Target::*&>);
    static_assert(StructureDereferenceIndirection<const ConstPtr&, MemberA Target::*&>);

    // --- Positive: lvalue-qualified operator->* on lvalue Self ---

    static_assert(StructureDereferenceIndirection<LvalPtr&, MemberA Target::*&>);

    // --- Positive: rvalue-qualified operator->*, non-ref Self (forwarded as rvalue) ---

    static_assert(StructureDereferenceIndirection<RvalPtr, MemberA Target::*>);

    // --- Positive: void-returning operator->* is still a valid expression ---

    static_assert(StructureDereferenceIndirection<VoidPtr&, MemberA Target::*&>);

    // --- Negative: no operator->* defined at all ---

    static_assert(not StructureDereferenceIndirection<Plain&, int Plain::*&>);
    static_assert(not StructureDereferenceIndirection<Plain, int Plain::*>);

    // --- Negative: non-const operator->* not accessible on const Self ---

    static_assert(not StructureDereferenceIndirection<const BasicPtr&, MemberA Target::*&>);

    // --- Negative: value-category mismatch — lvalue-qualified op, rvalue Self ---

    static_assert(not StructureDereferenceIndirection<LvalPtr, MemberA Target::*>);

    // --- Negative: value-category mismatch — rvalue-qualified op, lvalue Self ---

    static_assert(not StructureDereferenceIndirection<RvalPtr&, MemberA Target::*&>);

    // --- Negative: pointer-to-member from an unrelated class ---

    static_assert(not StructureDereferenceIndirection<Target*&, int Plain::*&>);

    // --- Negative: scalars have no ->* operator ---

    static_assert(not StructureDereferenceIndirection<int, int>);
    static_assert(not StructureDereferenceIndirection<int&, int&>);

    // =========================================================================
    // ReturnStructureDereferenceIndirection
    // =========================================================================

    // --- Positive: correct explicit return types ---

    static_assert(ReturnStructureDereferenceIndirection<BasicPtr&, MemberA Target::*&, MemberA&>);
    static_assert(ReturnStructureDereferenceIndirection<BasicPtr&, MemberB Target::*&, MemberB&>);
    static_assert(ReturnStructureDereferenceIndirection<BasicPtr&, int Target::*&, int&>);

    // --- Positive: non-ref Self, explicit return type ---

    static_assert(ReturnStructureDereferenceIndirection<BasicPtr, MemberA Target::*, MemberA&>);

    // --- Negative: wrong explicit return type ---

    static_assert(not ReturnStructureDereferenceIndirection<BasicPtr&, MemberA Target::*&, MemberB&
    >); // wrong member type
    static_assert(not ReturnStructureDereferenceIndirection<BasicPtr&, MemberA Target::*&, int&>); // wrong type entirely
    static_assert(not ReturnStructureDereferenceIndirection<BasicPtr&, MemberA Target::*&, MemberA>
    ); // reference stripped

    // --- Default Return = Self&: BasicPtr& → Self& = BasicPtr&, actual MemberA& → mismatch ---
    
    static_assert(not ReturnStructureDereferenceIndirection<BasicPtr&, MemberA Target::*&>);

    // --- Default Return = Self&: ChainPtr& → Self& = ChainPtr&, actual ChainPtr& → match ---

    static_assert(ReturnStructureDereferenceIndirection<ChainPtr&, MemberA Target::*&>);

    // --- Default Return = Self&: ChainPtr (non-ref) → Self& = ChainPtr&, actual ChainPtr& → match ---

    static_assert(ReturnStructureDereferenceIndirection<ChainPtr, MemberA Target::*>);

    // --- Explicit return type for ChainPtr ---

    static_assert(ReturnStructureDereferenceIndirection<ChainPtr&, MemberA Target::*&, ChainPtr&>);
    static_assert(not ReturnStructureDereferenceIndirection<ChainPtr&, MemberA Target::*&, MemberA&
    >);

    // --- Void-returning operator->* ---

    static_assert(ReturnStructureDereferenceIndirection<VoidPtr&, MemberA Target::*&, void>);
    static_assert(not ReturnStructureDereferenceIndirection<VoidPtr&, MemberA Target::*&, MemberA&>
    );

    // --- Built-in pointer return types ---

    static_assert(ReturnStructureDereferenceIndirection<Target*&, MemberA Target::*&, MemberA&>);
    static_assert(ReturnStructureDereferenceIndirection<Target*&, int Target::*&, int&>);
    static_assert(not ReturnStructureDereferenceIndirection<Target*&, MemberA Target::*&, MemberA>)
    ; // reference stripped

    // --- Const correctness via const member operator->* ---

    static_assert(ReturnStructureDereferenceIndirection<const ConstPtr&, MemberA Target::*&, const
    MemberA&>);
    static_assert(not ReturnStructureDereferenceIndirection<const ConstPtr&, MemberA Target::*&,
    MemberA&>); // const missing

    // --- Const correctness via raw const pointer ---
    
    static_assert(ReturnStructureDereferenceIndirection<const Target*&, MemberA Target::*&, const
    MemberA&>);
    static_assert(not ReturnStructureDereferenceIndirection<const Target*&, MemberA Target::*&,
    MemberA&>); // const missing

    // --- Negative: no operator->* defined ---
    
    static_assert(not ReturnStructureDereferenceIndirection<Plain&, int Plain::*&, int&>);

    // --- Value-category sensitivity: rvalue-qualified operator ---
    static_assert(ReturnStructureDereferenceIndirection<RvalPtr, MemberA Target::*, MemberA&>); // non-ref → rvalue → valid
    static_assert(not ReturnStructureDereferenceIndirection<RvalPtr&, MemberA Target::*&, MemberA&>
    ); // lvalue → not callable

    struct Incomplete;
    return not StructureDereferenceIndirection<Incomplete, Incomplete> and not
    ReturnStructureDereferenceIndirection<Incomplete, Incomplete>;
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