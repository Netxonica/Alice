// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_constructible
#define alice_header_guard_trait_constructible
#include "Core/Safety.hpp"
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and has an accessible
     * constructor with @p Arguments...
     */
    template<class Self, class... Arguments> concept Constructible = Marker::Sized<Self> and
    __is_constructible(Self, Arguments...);

    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and has an accessible unsafe
     * constructor with @p Arguments...
     */
    template<class Self, class... Arguments> concept UnsafeConstructible = Marker::Sized<Self> and
    __is_constructible(Self, const ::Alice::Detail::Safety<false>, Arguments...);
}

#endif
#endif