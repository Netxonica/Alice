// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_layoutable
#define alice_header_guard_trait_layoutable
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when both @p Self and @p Type satisfy Alice::Marker::Sized, and @p Self is
     * layout-compatible with @p Type
     */
    template<class Self, class Type> concept Layoutable = Marker::Sized<Self> and Marker::Sized<
    Type> and __is_layout_compatible(Self, Type);
}

#endif
#endif