// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_invocable
#define alice_header_guard_trait_invocable
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self can be called with @p Arguments... and returns @p Return
     */
    template<class Self, class Return, class... Arguments> concept Invocable = requires(Self self,
    Arguments... arguments)
    {
        {$forward(self)($forward(arguments)...)} -> Same<Return>;
    };
}

#endif
#endif