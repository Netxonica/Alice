// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Xor.hpp"

using Alice::Operator::Xor;
using Alice::Operator::ReturnXor;

// Non-member overload: must be found the same way a member would be.

struct FreeXor{};

FreeXor operator^(FreeXor const&, FreeXor const&)
{
    return {};
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---- fixtures ---------------------------------------------------------

    // No operator^ at all.

    struct NoXor{};

    // The ordinary case: takes and returns its own type.

    struct SelfXor
    {
        SelfXor operator^(SelfXor const&) const;
    };

    // Takes a type other than itself.

    struct TakesInt
    {
        TakesInt operator^(int) const;
    };

    // Returns a type other than itself.

    struct ReturnsBool
    {
        bool operator^(ReturnsBool const&) const;
    };

    // Has ^= but not ^: a distinct, unrelated overload that must not be
    // mistaken for one.
    
    struct HasXorAssignOnly
    {
        HasXorAssignOnly& operator^=(HasXorAssignOnly const&);
    };

    // Only callable through a mutable lvalue *this.
    
    struct LvalueOnlyXor
    {
        LvalueOnlyXor operator^(LvalueOnlyXor const&) &;
    };

    // Only callable through an rvalue *this.
    
    struct RvalueOnlyXor
    {
        RvalueOnlyXor operator^(RvalueOnlyXor const&) &&;
    };

    // ---- Xor: positive cases ------------------------------------------------

    static_assert(Xor<SelfXor, SelfXor>);
    static_assert(Xor<TakesInt, int>);
    static_assert(Xor<ReturnsBool, ReturnsBool>);  // return type is irrelevant to Xor
    static_assert(Xor<FreeXor, FreeXor>);          // non-member overloads count too
    static_assert(Xor<int, int>);
    static_assert(Xor<bool, bool>);

    // ---- Xor: negative cases --------------------------------------------------

    static_assert(not Xor<NoXor, NoXor>);
    static_assert(not Xor<TakesInt, TakesInt>);                  // wrong Rhs
    static_assert(not Xor<SelfXor, int>);                        // wrong Rhs
    static_assert(not Xor<HasXorAssignOnly, HasXorAssignOnly>);  // ^= is not ^

    // ---- Xor: value-category sensitivity ---------------------------------------
    // Self/Rhs are forwarded exactly as given ($forward), so Self=T, Self=T&
    // and Self=T const& probe the rvalue, mutable-lvalue and const-lvalue
    // overloads respectively.

    static_assert(Xor<LvalueOnlyXor&, LvalueOnlyXor>);
    static_assert(not Xor<LvalueOnlyXor, LvalueOnlyXor>);          // self would be an rvalue
    static_assert(not Xor<LvalueOnlyXor const&, LvalueOnlyXor>);   // self would be const
    static_assert(Xor<RvalueOnlyXor, RvalueOnlyXor>);
    static_assert(not Xor<RvalueOnlyXor&, RvalueOnlyXor>);         // self would be an lvalue

    // ---- ReturnXor: default Return (= Self) -----------------------------------

    static_assert(ReturnXor<SelfXor, SelfXor>);
    static_assert(not ReturnXor<ReturnsBool, ReturnsBool>);    // actually returns bool
    static_assert(ReturnXor<ReturnsBool, ReturnsBool, bool>);  // ... which this confirms
    static_assert(ReturnXor<TakesInt, int>);                   // default Return, Self != Rhs
    static_assert(not ReturnXor<TakesInt, int, int>);          // wrong explicit Return

    // An expression that isn't even valid must fail ReturnXor regardless of
    // what Return is asked for.

    static_assert(not ReturnXor<NoXor, NoXor>);
    static_assert(not ReturnXor<NoXor, NoXor, NoXor>);

    // ---- ReturnXor: built-in integral promotion --------------------------------
    // The built-in ^ promotes bool/short (etc.) operands to int, so e.g.
    // `bool ^ bool` is a valid expression (Xor is satisfied) but its result
    // type is int, not bool. ReturnXor's default Return (= Self) must catch
    // that mismatch, while an explicit Return of int must be satisfied.

    static_assert(Xor<bool, bool>);
    static_assert(not ReturnXor<bool, bool>);
    static_assert(ReturnXor<bool, bool, int>);
    static_assert(Xor<short, short>);
    static_assert(not ReturnXor<short, short>);
    static_assert(ReturnXor<short, short, int>);
    static_assert(ReturnXor<int, int>);  // int has no promotion surprise

    struct Incomplete;
    return not Xor<Incomplete, Incomplete> and not ReturnXor<Incomplete, Incomplete>;
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