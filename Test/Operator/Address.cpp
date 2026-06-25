// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/Address.hpp"

using Alice::Operator::Address;
using Alice::Operator::ReturnAddress;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Test types ────────────────────────────────────────────────────────────────

    // No operator& overload at all.  The built-in address-of operator only
    // accepts lvalues, so $forward(self) (an rvalue) cannot satisfy Address.
    
    struct Plain{};

    // Unqualified operator&: callable on lvalues *and* rvalues.

    struct UnqualAddr
    {
        UnqualAddr* operator&() noexcept
        {
            return this;
        }
    };

    // rvalue-ref-qualified operator&: callable only on rvalues — exactly what
    // $forward(self) produces, so this must satisfy Address.

    struct RvalAddr
    {
        RvalAddr* operator&() && noexcept
        {
            return this;
        }
    };

    // lvalue-ref-qualified operator&: callable only on lvalues.
    // $forward(self) yields an rvalue, so this must NOT satisfy Address.

    struct LvalAddr
    {
        LvalAddr* operator&() & noexcept
        {
            return this;
        }
    };

    // Deleted operator& (unqualified): any call is ill-formed.

    struct DeletedAddr
    {
        DeletedAddr* operator&() = delete;
    };

    // operator& returns a type other than Self*.  This has a valid overload so
    // it satisfies Address, but must not satisfy ReturnAddress<Self> (default
    // Return = Self*).

    struct Tag{};

    struct ProxyAddr
    {
        Tag* operator&() noexcept
        {
            return nullptr;
        }
    };

    // ── Address ───────────────────────────────────────────────────────────────────

    // Positive: overloads that accept rvalues

    static_assert(Address<UnqualAddr>, "An unqualified operator& must satisfy Address.");
    static_assert(Address<RvalAddr>, "An rvalue-ref-qualified operator& must satisfy Address.");
    static_assert(Address<ProxyAddr>,
    "An operator& with a non-Self* return type must still satisfy Address.");

    // Negative: no overload, lvalue-only overload, or deleted overload
    
    #ifndef _MSC_VER
    static_assert(not Address<LvalAddr>,
    "A lvalue-only operator& must not satisfy Address: $forward(self) is an rvalue.");
    static_assert(not Address<Plain>, "Absence of an operator& overload must not satisfy Address.")
    ;
    #endif
    static_assert(not Address<DeletedAddr>, "A deleted operator& must not satisfy Address.");

    // ── ReturnAddress — default Return (= Self*) ─────────────────────────────────

    static_assert(ReturnAddress<UnqualAddr>,
    "operator& returning Self* (unqualified) must satisfy ReturnAddress<Self>.");
    static_assert(ReturnAddress<RvalAddr>,
    "operator& returning Self* (rvalue-qualified) must satisfy ReturnAddress<Self>.");
    #ifndef _MSC_VER
    static_assert(not ReturnAddress<LvalAddr>,
    "A lvalue-only operator& must not satisfy ReturnAddress.");
    static_assert(not ReturnAddress<Plain>,
    "Absence of an operator& overload must not satisfy ReturnAddress.");
    #endif
    static_assert(not ReturnAddress<DeletedAddr>,
    "A deleted operator& must not satisfy ReturnAddress.");
    static_assert(not ReturnAddress<ProxyAddr>,
    "operator& returning Tag* must not satisfy ReturnAddress<ProxyAddr> (Tag* != ProxyAddr*).");

    // ── ReturnAddress — explicit Return type ─────────────────────────────────────

    static_assert(ReturnAddress<UnqualAddr, UnqualAddr*>,
    "Explicit Self* must satisfy ReturnAddress.");
    static_assert(not ReturnAddress<UnqualAddr, int*>,
    "operator& returns UnqualAddr*, not int*: must not satisfy ReturnAddress.");
    static_assert(ReturnAddress<RvalAddr, RvalAddr*>,
    "Explicit Self* must satisfy ReturnAddress for an rvalue-qualified overload.");
    static_assert(not ReturnAddress<RvalAddr, void*>,
    "operator& returns RvalAddr*, not void*: must not satisfy ReturnAddress.");
    static_assert(ReturnAddress<ProxyAddr, Tag*>,
    "Explicit Tag* must match ProxyAddr::operator& return type.");
    static_assert(not ReturnAddress<ProxyAddr, ProxyAddr*>,
    "ProxyAddr::operator& returns Tag*, not ProxyAddr*: must not satisfy ReturnAddress<ProxyAddr, "
    "ProxyAddr*>.");
    #ifndef _MSC_VER
    static_assert(not ReturnAddress<Plain, Plain*>,
    "Absence of an operator& overload must not satisfy ReturnAddress even when the explicit Return"
    " type would match the built-in address-of result.");
    #endif

    struct Incomplete;
    return not Address<Incomplete> and not ReturnAddress<Incomplete>;
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