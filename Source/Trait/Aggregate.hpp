// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_aggregate
#define alice_header_guard_trait_aggregate
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and is an aggregate type.
     */
    template<class Self> concept Aggregate = Marker::Sized<Self> and __is_aggregate(Self);
}

#endif
#endif