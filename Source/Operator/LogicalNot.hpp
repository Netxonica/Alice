// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_operator_logical_not
#define alice_header_guard_operator_logical_not
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"

namespace Alice::Operator
{
    /**
     * @brief Satisfied when @p Self overloads a logical not operator.
     */
    template<class Self> concept LogicalNot = requires(Self self)
    {
        not $forward(self);
    };

    /**
     * @brief Satisfied when @p Self overloads a logical not operator returning @p Return
     */
    template<class Self, class Return = bool> concept ReturnLogicalNot = requires(Self self)
    {
        {not $forward(self)} -> Trait::Same<Return>;
    };
}

#endif
#endif