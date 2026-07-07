// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_operator_less_equal
#define alice_header_guard_operator_less_equal
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"

namespace Alice::Operator
{
    /**
     * @brief Satisfied when @p Self overloads a less or equal operator by taking an argument of
     * type @p Rhs
     */
    template<class Self, class Rhs> concept LessEqual = requires(Self self, Rhs rhs)
    {
        $forward(self) <= $forward(rhs);
    };

    /**
     * @brief Satisfied when @p Self overloads a less or equal operator by taking an argument of
     * type @p Rhs and returning @p Return
     */
    template<class Self, class Rhs, class Return = bool> concept ReturnLessEqual = requires(Self
    self, Rhs rhs)
    {
        {$forward(self) <= $forward(rhs)} -> Trait::Same<Return>;
    };
}

#endif
#endif