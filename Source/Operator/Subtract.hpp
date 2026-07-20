// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_operator_subtract
#define alice_header_guard_operator_subtract
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"

namespace Alice::Operator
{
    /**
     * @brief Satisfied when @p Self overloads the arithmetic subtraction operator by taking an
     * argument of type @p Rhs
     */
    template<class Self, class Rhs> concept Subtract = requires(Self self, Rhs rhs)
    {
        $forward(self) - $forward(rhs);
    };

    /**
     * @brief Satisfied when @p Self overloads the arithmetic subtraction operator by taking an
     * argument of type @p Rhs that returns @p Return
     */
    template<class Self, class Rhs, class Return = Self> concept ReturnSubtract = requires(Self
    self, Rhs rhs)
    {
        {$forward(self) - $forward(rhs)} -> Trait::Same<Return>;
    };
}

#endif
#endif