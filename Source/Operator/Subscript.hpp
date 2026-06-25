// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_operator_subscript
#define alice_header_guard_operator_subscript
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"

namespace Alice::Operator
{
    /**
     * @brief Satisfied when @p Self overloads a subscript operator by taking an arbitrary number
     * of arguments given by @p Arguments
     */
    template<class Self, class... Arguments> concept Subscript = requires(Self self, Arguments...
    arguments)
    {
        $forward(self)[$forward(arguments)...];
    };

    /**
     * @brief Satisfied when @p Self overloads a subscript operator by taking an arbitrary number
     * of arguments given by @p Arguments returning @p Return
     */
    template<class Self, class Return, class... Arguments> concept ReturnSubscript = requires(Self
    self, Arguments... arguments)
    {
        {$forward(self)[$forward(arguments)...]} -> Trait::Same<Return>;
    };
}

#endif
#endif