// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Indirection.hpp"

using Alice::Operator::Indirection;
using Alice::Operator::ReturnIndirection;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // =====================================================================
    // Test types
    // =====================================================================

    // Non-const operator* → int&
    
    struct PointerLike
    {
        int m_value{};

        int& operator*() noexcept
        {
            return m_value;
        }
    };

    // const-only operator* → const int&

    struct ConstPointerLike
    {
        int m_value{};

        const int& operator*() const noexcept
        {
            return m_value;
        }
    };

    // operator* → void

    struct VoidDereference
    {
        void operator*() noexcept{}
    };

    // operator* → Self&; the only fixture that satisfies ReturnIndirection with the
    // default Return = Self&, since every other fixture returns something unrelated to Self.

    struct SelfDereference
    {
        SelfDereference& operator*() noexcept
        {
            return *this;
        }
    };

    struct NoDereference{};

    struct DeletedDereference
    {
        int& operator*() = delete;
    };

    // &-qualified: only callable on lvalues.
    //   Indirection<LvalueOnlyDereference>   — Self forwarded as T&&  → NOT satisfied.
    //   Indirection<LvalueOnlyDereference&>  — Self forwarded as T&   → IS  satisfied.

    struct LvalueOnlyDereference
    {
        int m_value{};

        int& operator*() & noexcept
        {
            return m_value;
        }
    };

    // &&-qualified: symmetric counterpart of LvalueOnlyDereference.
    //   Indirection<RvalueOnlyDereference>   — Self forwarded as T&&  → IS  satisfied.
    //   Indirection<RvalueOnlyDereference&>  — Self forwarded as T&   → NOT satisfied.

    struct RvalueOnlyDereference
    {
        int m_value{};

        int& operator*() && noexcept
        {
            return m_value;
        }
    };

    // =====================================================================
    // Indirection
    // =====================================================================

    // Has a usable operator*

    static_assert(Indirection<PointerLike>);
    static_assert(Indirection<ConstPointerLike>);
    static_assert(Indirection<VoidDereference>);
    static_assert(Indirection<SelfDereference>);
    static_assert(Indirection<int*>);
    static_assert(Indirection<const int*>);

    // No operator*, deleted, fundamental, or void pointer (no built-in deref)
    
    static_assert(not Indirection<NoDereference>);
    static_assert(not Indirection<int>);
    static_assert(not Indirection<void*>);
    static_assert(not Indirection<DeletedDereference>);

    // Ref-qualifier / value category edge cases
    
    static_assert(not Indirection<LvalueOnlyDereference>);      // rvalue-forwarded Self, & overload unreachable
    static_assert(Indirection<LvalueOnlyDereference&>);     // lvalue-forwarded Self, & overload reachable
    static_assert(Indirection<RvalueOnlyDereference>);      // rvalue-forwarded Self, && overload reachable
    static_assert(not Indirection<RvalueOnlyDereference&>);     // lvalue-forwarded Self, && overload unreachable

    // =====================================================================
    // ReturnIndirection
    // =====================================================================

    // PointerLike → int&

    static_assert(ReturnIndirection<PointerLike, int&>);
    static_assert(not ReturnIndirection<PointerLike, int>);         // int& ≠ int
    static_assert(not ReturnIndirection<PointerLike, float&>);      // wrong value type
    static_assert(not ReturnIndirection<PointerLike>);              // default Return = PointerLike&; actual int&

    // ConstPointerLike → const int&

    static_assert(ReturnIndirection<ConstPointerLike, const int&>);
    static_assert(not ReturnIndirection<ConstPointerLike, int&>);   // cv-mismatch
    static_assert(not ReturnIndirection<ConstPointerLike>);         // default Return = ConstPointerLike&; actual const int&

    // SelfDereference → Self& (only type that satisfies the default Return = Self&)

    static_assert(ReturnIndirection<SelfDereference>);
    static_assert(ReturnIndirection<SelfDereference, SelfDereference&>);
    static_assert(not ReturnIndirection<SelfDereference, int&>);

    // VoidDereference → void

    static_assert(ReturnIndirection<VoidDereference, void>);
    static_assert(not ReturnIndirection<VoidDereference, int&>);

    // No operator* at all

    static_assert(not ReturnIndirection<NoDereference>);
    static_assert(not ReturnIndirection<NoDereference, int&>);
    static_assert(not ReturnIndirection<int>);

    // Raw pointers — built-in dereference yields element reference

    static_assert(ReturnIndirection<int*, int&>);
    static_assert(not ReturnIndirection<int*, int>);                // int& ≠ int
    static_assert(not ReturnIndirection<int*>);                     // default Return = int*&; actual int&
    static_assert(ReturnIndirection<const int*, const int&>);
    static_assert(not ReturnIndirection<const int*, int&>);         // cv-mismatch

    struct Incomplete;
    return not Indirection<Incomplete> and not ReturnIndirection<Incomplete>;
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