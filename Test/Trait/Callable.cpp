// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Callable.hpp"

using Alice::Trait::Callable;

// --- Free functions ---

void fn_0(){}

int fn_int(int x)
{
    return x;
}

void fn_two(int, float){}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Callable functors ---

    struct NoArg
    {
        void operator()(){}
    };

    struct ConstNoArg
    {
        void operator()() const{}
    };

    struct OneInt
    {
        void operator()(int){}
    };

    struct OneFloat
    {
        void operator()(float){}
    };

    struct TwoArgs
    {
        void operator()(int, float){}
    };

    struct ReturnsInt
    {
        int operator()(int x)
        {
            return x;
        }
    };

    struct LRefArg
    {
        void operator()(int&){}
    };

    struct RRefArg
    {
        void operator()(int&&){}
    };

    struct ConstRefArg
    {
        void operator()(const int&){}
    };

    struct Overloaded
    {
        void operator()(){}
        
        void operator()(int){}
    };

    // --- Non-callable types ---

    struct NoOp
    {
        int value;
    };

    // ============================================================
    //  Positive tests — concept must be satisfied
    // ============================================================

    // Functor: no arguments

    static_assert(Callable<NoArg>);

    // Functor: const-qualified call operator, no arguments

    static_assert(Callable<ConstNoArg>);

    // Functor: single int argument

    static_assert(Callable<OneInt, int>);

    // Functor: single float argument

    static_assert(Callable<OneFloat, float>);

    // Functor: two arguments

    static_assert(Callable<TwoArgs, int, float>);

    // Non-void return type is orthogonal to callability

    static_assert(Callable<ReturnsInt, int>);

    // Lvalue-reference argument

    static_assert(Callable<LRefArg, int&>);

    // Rvalue-reference argument

    static_assert(Callable<RRefArg, int&&>);

    // const-ref argument, exact match

    static_assert(Callable<ConstRefArg, const int&>);

    // const-ref argument: a plain int (rvalue) must also bind to const int&

    static_assert(Callable<ConstRefArg, int>);

    // Overloaded operator(): both arities must resolve

    static_assert(Callable<Overloaded>);
    static_assert(Callable<Overloaded, int>);

    // Implicit numeric conversions count as callable

    static_assert(Callable<OneInt, float>);   // float → int
    static_assert(Callable<OneFloat, int>);   // int   → float

    // const Self with a const call operator: $forward yields const Self&&,
    // which is still a valid receiver for a const-qualified operator()

    static_assert(Callable<const ConstNoArg>);

    // lvalue-reference Self: $forward collapses to an lvalue reference,
    // so non-const operator() can still be invoked
    
    static_assert(Callable<NoArg&>);
    static_assert(Callable<OneInt&, int>);

    // Function pointers
    
    static_assert(Callable<decltype(&fn_0)>);
    static_assert(Callable<decltype(&fn_int), int>);
    static_assert(Callable<decltype(&fn_two), int, float>);

    // ============================================================
    //  Negative tests — concept must NOT be satisfied
    // ============================================================

    // Fundamental scalar types have no operator()

    static_assert(not Callable<int>);
    static_assert(not Callable<float>);
    static_assert(not Callable<bool>);

    // Pointer-to-data is not callable

    static_assert(not Callable<int*>);
    static_assert(not Callable<void*>);

    // Struct without a call operator

    static_assert(not Callable<NoOp>);
    static_assert(not Callable<NoOp, int>);

    // const Self with a non-const operator(): $forward yields const Self&&,
    // which cannot invoke a non-const operator() without dropping const

    static_assert(not Callable<const NoArg>);
    static_assert(not Callable<const OneInt, int>);

    // Too many arguments

    static_assert(not Callable<NoArg, int>);
    static_assert(not Callable<OneInt, int, int>);
    static_assert(not Callable<TwoArgs, int, float, int>);

    // Too few arguments

    static_assert(not Callable<OneInt>);
    static_assert(not Callable<TwoArgs, int>);
    static_assert(not Callable<TwoArgs>);

    // Incompatible argument type — no implicit conversion from NoOp to any scalar

    static_assert(not Callable<OneInt, NoOp>);
    static_assert(not Callable<OneFloat, NoOp>);

    // Function pointer: missing required argument

    static_assert(not Callable<decltype(&fn_int)>);

    // Function pointer: incompatible argument type

    static_assert(not Callable<decltype(&fn_int), NoOp>);

    // Function pointer: superfluous argument

    static_assert(not Callable<decltype(&fn_0), int>);

    struct Incomplete;
    return not Callable<Incomplete>;
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