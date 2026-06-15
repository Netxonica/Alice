// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_callable
#define alice_header_guard_trait_callable
#include "Core/Forward.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self can be called with @p Arguments...
     */
    template<class Self, class... Arguments> concept Callable = requires(Self self, Arguments...
    arguments)
    {
        $forward(self)($forward(arguments)...);
    };
}

#endif
#endif