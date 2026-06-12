// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_copy_materializable
#define alice_header_guard_trait_copy_materializable
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when both @p Self and @p Temporary satisfy Alice::Marker::Sized, and
     * @p Self can be binded in a copy-initialization expression from the @p Temporary type.
     */
    template<class Self, class Temporary> concept CopyMaterializable = Marker::Sized<Self> and
    Marker::Sized<Temporary> and __reference_converts_from_temporary(Self, Temporary);
}

#endif
#endif