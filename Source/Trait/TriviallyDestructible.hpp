// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_trivially_destructible
#define alice_header_guard_trait_trivially_destructible
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and has an accessible trivial
     * destructor.
     */
    template<class Self> concept TriviallyDestructible = Marker::Sized<Self> and
    __is_trivially_destructible(Self);
}

#endif
#endif