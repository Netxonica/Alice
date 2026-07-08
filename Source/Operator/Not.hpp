// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_operator_not
#define alice_header_guard_operator_not
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"

namespace Alice::Operator
{
    /**
     * @brief Satisfied when @p Self overloads a bitwise not operator.
     */
    template<class Self> concept Not = requires(Self self)
    {
        compl $forward(self);
    };

    /**
     * @brief Satisfied when @p Self overloads a bitwise not operator that returns @p Return
     */
    template<class Self, class Return = Self> concept ReturnNot = requires(Self self)
    {
        {compl $forward(self)} -> Trait::Same<Return>;
    };
}

#endif
#endif