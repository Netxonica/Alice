// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/ModuloAssignment.hpp"

using Alice::Operator::ModuloAssignment;
using Alice::Operator::ReturnModuloAssignment;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ---------------------------------------------------------------------
    // Fixtures
    // ---------------------------------------------------------------------

    struct Unrelated{};

    struct NoModulo{};

    struct Counter
    {
        int value{};

        Counter& operator%=(int rhs) noexcept
        {
            value %= rhs;
            return *this;
        }
    };

    struct VoidModulo
    {
        void operator%=(int) noexcept{}
    };

    struct ByValueModulo
    {
        ByValueModulo operator%=(int) noexcept
        {
            return *this;
        }
    };

    struct Status{};

    struct CustomReturnModulo
    {
        Status operator%=(int) noexcept
        {
            return {};
        }
    };

    struct RvalueOnlyModulo
    {
        RvalueOnlyModulo& operator%=(RvalueOnlyModulo&&) noexcept
        {
            return *this;
        }
    };

    struct LvalueOnlyModulo
    {
        LvalueOnlyModulo& operator%=(LvalueOnlyModulo&) noexcept
        {
            return *this;
        }
    };

    // ---------------------------------------------------------------------
    // Alice::Operator::ModuloAssignment
    // ---------------------------------------------------------------------

    // Built-in arithmetic types.

    static_assert(ModuloAssignment<int, int>);
    static_assert(ModuloAssignment<int, short>);
    static_assert(ModuloAssignment<int, int&>);
    static_assert(ModuloAssignment<int, int&&>);
    static_assert(not ModuloAssignment<double, double>);
    static_assert(not ModuloAssignment<const int, int>);

    // User-defined types: presence/absence of a matching operator%=.
    
    static_assert(ModuloAssignment<Counter, int>);
    static_assert(not ModuloAssignment<Counter, Unrelated>);
    static_assert(not ModuloAssignment<NoModulo, int>);
    static_assert(not ModuloAssignment<const Counter, int>);

    // Value-category sensitivity, exercised through $forward.
    
    static_assert(ModuloAssignment<RvalueOnlyModulo, RvalueOnlyModulo>);
    static_assert(ModuloAssignment<RvalueOnlyModulo, RvalueOnlyModulo&&>);
    static_assert(not ModuloAssignment<RvalueOnlyModulo, RvalueOnlyModulo&>);
    static_assert(ModuloAssignment<LvalueOnlyModulo, LvalueOnlyModulo&>);
    static_assert(not ModuloAssignment<LvalueOnlyModulo, LvalueOnlyModulo>);
    static_assert(not ModuloAssignment<LvalueOnlyModulo, LvalueOnlyModulo&&>);

    // ---------------------------------------------------------------------
    // Alice::Operator::ReturnModuloAssignment
    // ---------------------------------------------------------------------

    // Built-in types: %= yields an lvalue naming the left-hand operand.

    static_assert(ReturnModuloAssignment<int, int>);
    static_assert(ReturnModuloAssignment<int, int, int&>);
    static_assert(not ReturnModuloAssignment<int, int, int>);

    // Default Return = Self&.
    
    static_assert(ReturnModuloAssignment<Counter, int>);
    static_assert(not ReturnModuloAssignment<VoidModulo, int>);
    static_assert(ReturnModuloAssignment<VoidModulo, int, void>);
    static_assert(not ReturnModuloAssignment<ByValueModulo, int>);
    static_assert(ReturnModuloAssignment<ByValueModulo, int, ByValueModulo>);

    // Custom Return type unrelated to Self.
    
    static_assert(not ReturnModuloAssignment<CustomReturnModulo, int>);
    static_assert(ReturnModuloAssignment<CustomReturnModulo, int, Status>);

    // A satisfied ReturnModuloAssignment always implies ModuloAssignment.
    
    static_assert(ModuloAssignment<VoidModulo, int>);
    static_assert(ModuloAssignment<ByValueModulo, int>);
    static_assert(ModuloAssignment<CustomReturnModulo, int>);
    static_assert(ReturnModuloAssignment<RvalueOnlyModulo, RvalueOnlyModulo>);
    static_assert(not ReturnModuloAssignment<RvalueOnlyModulo, RvalueOnlyModulo&>);

    struct Incomplete;
    return not ModuloAssignment<Incomplete, Incomplete> and not ReturnModuloAssignment<Incomplete,
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