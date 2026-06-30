// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_standard_layout_base
#define alice_header_guard_trait_standard_layout_base
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when both @p Self and @p Derived satisfy Alice::Marker::Sized, @p Derived
     * is standard-layout, and @p Self is a base class of @p Derived
     */
    template<class Self, class Derived> concept StandardLayoutBase = Marker::Sized<Self> and Marker
    ::Sized<Derived> and __is_pointer_interconvertible_base_of(Self, Derived);
}

#endif
#endif