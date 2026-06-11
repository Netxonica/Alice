// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_unique_object
#define alice_header_guard_trait_unique_object
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and has a unique object
     * representation.
     */
    template<class Self> concept UniqueObject = Marker::Sized<Self> and
    __has_unique_object_representations(Self);
}

#endif
#endif