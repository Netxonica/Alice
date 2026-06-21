// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_operator_unary_plus
#define alice_header_guard_operator_unary_plus
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"

namespace Alice::Operator
{
    /**
     * @brief Satisfied when @p Self overloads a unary plus operator.
     */
    template<class Self> concept UnaryPlus = requires(Self self)
    {
        +$forward(self);
    };

    /**
     * @brief Satisfied when @p Self overloads a unary plus operator returning @p Return
     */
    template<class Self, class Return = Self> concept ReturnUnaryPlus = requires(Self self)
    {
        {+$forward(self)} -> Trait::Same<Return>;
    };
}

#endif
#endif