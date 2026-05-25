// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_clone_clone
#define alice_header_guard_clone_clone
#include "Trait/Same.hpp"

namespace Alice
{
    /**
     * @brief Satisfied when @p Self has a non-static member function named @ref Clone that returns
     * a deep copy of a @p Self object, which may or may not be expensive.
     */
    template<class Self> concept Clone = requires(const Self& self)
    {
        {self.Clone()} -> Trait::Same<Self>;
    };
}

#endif
#endif