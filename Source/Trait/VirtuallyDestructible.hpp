// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_virtually_destructible
#define alice_header_guard_trait_virtually_destructible
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and has a virtual destructor.
     */
    template<class Self> concept VirtuallyDestructible = Marker::Sized<Self> and
    __has_virtual_destructor(Self);
}

#endif
#endif