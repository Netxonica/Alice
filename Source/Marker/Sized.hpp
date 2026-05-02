// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_marker_sized
#define alice_header_guard_marker_sized
#include "Trait/Function.hpp"
#include "Meta/RemoveExtents.hpp"
#include "Trait/UnboundedArray.hpp"

namespace Alice::Marker
{
    /**
     * @brief Satisfied when @p Self has an static size known at compile-time, meaning it's a
     * complete type.
     */
    template<class Self> concept Sized = not Trait::Function<Self> and not Trait::UnboundedArray<
    Self> and requires(Meta::RemoveExtents<Self> self)
    {
        sizeof(self);
    };
}

#endif
#endif