// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Forward.hpp"
#include "Trait/Constant.hpp"
#include "Meta/RemoveReference.hpp"
#include "Trait/LvalueReference.hpp"
#include "Trait/RvalueReference.hpp"

using Alice::Trait::Constant;
using Alice::Meta::RemoveReference;
using Alice::Trait::LvalueReference;
using Alice::Trait::RvalueReference;

struct CallLog
{
    int lvalue = 0, rvalue = 0;

    void sink(int&) noexcept
    {
        ++lvalue;
    }

    void sink(int&&) noexcept
    {
        ++rvalue;
    }
};

// Simulates the canonical perfect-forwarding wrapper; T&& is a forwarding ref.
template<typename T> auto forward_to(CallLog& log, T&& val) noexcept -> void
{
    log.sink($forward(val));
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─── Compile-time tests ───────────────────────────────────────────────────────
    // These are checked entirely by the compiler; a build failure IS a test failure.
    //
    // Key rule: for a name N,  decltype(N)  is its *declared* type, so reference
    // collapsing in the cast encodes the forwarding semantics:
    //
    //   declared T    →  cast target T&&  →  result category
    //   ──────────────────────────────────────────────────────
    //   int           →  int&&            →  xvalue  (like std::move)
    //   int&          →  int& &&  = int&  →  lvalue
    //   int&&         →  int&& && = int&& →  xvalue
    //
    // For non-name expressions, decltype uses expression value-category rules
    // (lvalue → T&, xvalue/prvalue → T or T&&), so lvalue sub-expressions are
    // preserved and prvalues become xvalues (as documented).

    // 1. lvalue-reference declared type → result is lvalue reference
    
    int g_val = 0;
    
    int& g_lref = g_val;
    
    static_assert(LvalueReference<decltype($forward(g_lref))>,
    "forwarding a T& name must yield T& (lvalue)");

    // 2. rvalue-reference declared type → result is rvalue reference (xvalue)
    
    int&& g_rref = static_cast<int&&>(g_val);
    
    static_assert(RvalueReference<decltype($forward(g_rref))>,
    "forwarding a T&& name must yield T&& (xvalue)");

    // 3. Non-reference declared type → result is rvalue reference (acts like move)

    static_assert(RvalueReference<decltype($forward(g_val))>,
    "forwarding a plain T name must yield T&& (xvalue)");

    // 4. prvalue expression → xvalue (prvalue materialisation, as documented)
    
    static_assert(RvalueReference<decltype($forward(0))>,
    "forwarding an int prvalue must yield int&&");
    static_assert(RvalueReference<decltype($forward(int{}))>,
    "forwarding a value-init prvalue must yield int&&");

    // 5. lvalue sub-expression (array subscript) → lvalue reference preserved
    
    int g_arr[2] = {1, 2};

    static_assert(LvalueReference<decltype($forward(g_arr[0]))>,
    "forwarding an array-subscript lvalue expression must yield lvalue reference");

    // 6. const lvalue-reference → const lvalue reference (const preserved)
    
    const int g_cval = 0;
    
    const int& g_clref = g_cval;
    
    static_assert(LvalueReference<decltype($forward(g_clref))>,
    "forwarding a const T& name must yield lvalue reference");
    static_assert(Constant<RemoveReference<decltype($forward(g_clref))>>,
    "forwarding a const T& name must preserve const");

    // 7. const rvalue-reference → const rvalue reference (const preserved)
    
    const int&& g_crref = static_cast<const int&&>(g_cval);
    
    static_assert(RvalueReference<decltype($forward(g_crref))>,
    "forwarding a const T&& name must yield rvalue reference");
    static_assert(Constant<RemoveReference<decltype($forward(g_crref))>>,
    "forwarding a const T&& name must preserve const");

    // 8. Macro can forward multiple tokens (variadic), e.g. a comma-free expression
    //    – tested implicitly by all uses above; explicitly check a cast expression:
    
    static_assert(RvalueReference<decltype($forward(static_cast<int&&>(g_val)))>,
    "forwarding a cast-expression must yield rvalue reference");

    // ─── Runtime infrastructure ───────────────────────────────────────────────────

    int f = 0;   // failure counter

    // R1: lvalue-ref name → lvalue overload selected
    {
        CallLog log;

        int x = 1;

        int& lr = x;

        log.sink($forward(lr));

        if(log.lvalue not_eq 1 or log.rvalue not_eq 0)
            ++f;
    }

    // R2: rvalue-ref name → rvalue overload selected
    {
        CallLog log;

        int x = 2;

        int&& rr = static_cast<int&&>(x);

        log.sink($forward(rr));

        if(log.lvalue not_eq 0 or log.rvalue not_eq 1)
            ++f;
    }

    // R3: prvalue expression → rvalue overload selected
    {
        CallLog log;
        
        log.sink($forward(42));
        
        if(log.lvalue not_eq 0 or log.rvalue not_eq 1)
            ++f;
    }

    // R4: lvalue sub-expression (array subscript) → lvalue overload selected
    {
        CallLog log;

        int arr[2] = {10, 20};

        log.sink($forward(arr[0]));

        if(log.lvalue not_eq 1 or log.rvalue not_eq 0)
            ++f;
    }

    // R5: template forwarding reference, lvalue argument
    //     T deduced as int& → val has declared type int& → $forward yields int&
    {
        CallLog log;

        int x = 5;

        forward_to(log, x);

        if(log.lvalue not_eq 1 or log.rvalue not_eq 0)
            ++f;
    }

    // R6: template forwarding reference, rvalue argument
    //     T deduced as int → val has declared type int&& → $forward yields int&&
    {
        CallLog log;
        
        forward_to(log, 5);
        
        if(log.lvalue not_eq 0 or log.rvalue not_eq 1)
            ++f;
    }

    // R7: identity of forwarded lvalue is preserved (no copy/move of address)
    {
        int x = 7;

        int& lr = x;

        int* p = &($forward(lr));   // $forward(lr) is an lvalue; & is valid

        if(p not_eq &x)
            ++f;
    }

    // R8: forwarding through two layers preserves category
    //     outer wrapper calls inner wrapper; lvalue must stay lvalue end-to-end
    {
        CallLog log;

        int x = 8;

        int& lr = x;

        auto inner = [&](int& v) noexcept
        {
            log.sink($forward(v));
        };

        inner($forward(lr));

        if(log.lvalue not_eq 1 or log.rvalue not_eq 0)
            ++f;
    }

    return f == 0;
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