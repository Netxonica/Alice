// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_empty
#define alice_header_guard_trait_empty
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and is an empty non-union
     * class.
     */
    template<class Self> concept Empty = Marker::Sized<Self> and __is_empty(Self);
}

#endif
#endif