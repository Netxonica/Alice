// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_operator_or_assignment
#define alice_header_guard_operator_or_assignment
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"

namespace Alice::Operator
{
    /**
     * @brief Satisfied when @p Self overloads a bitwise or assignment operator by taking an
     * argument of type @p Rhs
     */
    template<class Self, class Rhs> concept OrAssignment = requires(Self self, Rhs rhs)
    {
        self or_eq $forward(rhs);
    };

    /**
     * @brief Satisfied when @p Self overloads a bitwise or assignment operator by taking an
     * argument of type @p Rhs that returns @p Return
     */
    template<class Self, class Rhs, class Return = Self&> concept ReturnOrAssignment = requires(
    Self self, Rhs rhs)
    {
        {self or_eq $forward(rhs)} -> Trait::Same<Return>;
    };
}

#endif
#endif