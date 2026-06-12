// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_base
#define alice_header_guard_trait_base
#include "Trait/Same.hpp"
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self and @p Derived satisfy Alice::Marker::Sized and do not satisfy
     * Alice::Trait::Same, and @p Self is a base class of @p Derived
     */
    template<class Self, class Derived> concept Base = Marker::Sized<Self> and Marker::Sized<
    Derived> and not Same<Self, Derived> and __is_base_of(Self, Derived);
}

#endif
#endif