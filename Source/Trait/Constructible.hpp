// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_constructible
#define alice_header_guard_trait_constructible
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is Alice::Marker::Sized and has an accessible constructor with
     * @p Arguments... .
     */
    template<class Self, class... Arguments> concept Constructible = Marker::Sized<Self> and
    __is_constructible(Self, Arguments...);
}

#endif
#endif