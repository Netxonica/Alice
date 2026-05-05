// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_default_constructible
#define alice_header_guard_trait_default_constructible
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and has a non-deleted
     * accessible default constructor.
     */
    template<class Self> concept DefaultConstructible = Marker::Sized<Self> and __is_constructible(
    Self);
}

#endif
#endif