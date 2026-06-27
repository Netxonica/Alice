// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_operator_logical_and
#define alice_header_guard_operator_logical_and
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"

namespace Alice::Operator
{
    /**
     * @brief Satisfied when @p Self overloads a logical and operator by taking an argument of type
     * @p Rhs
     */
    template<class Self, class Rhs> concept LogicalAnd = requires(Self self, Rhs rhs)
    {
        $forward(self) and $forward(rhs);
    };

    /**
     * @brief Satisfied when @p Self overloads a logical not operator by taking an argument of type
     * @p Rhs and returning @p Return
     */
    template<class Self, class Rhs, class Return = bool> concept ReturnLogicalAnd = requires(Self
    self, Rhs rhs)
    {
        {$forward(self) and $forward(rhs)} -> Trait::Same<Return>;
    };
}

#endif
#endif