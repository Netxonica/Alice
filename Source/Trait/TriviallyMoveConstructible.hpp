// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_trivially_move_constructible
#define alice_header_guard_trait_trivially_move_constructible
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and has an accessible trivial
     * move constructor.
     */
    template<class Self> concept TriviallyMoveConstructible = Marker::Sized<Self> and
    __is_trivially_constructible(Self, Self&&);
}

#endif
#endif