// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_implicit_lifetime
#define alice_header_guard_trait_implicit_lifetime
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and is an implicit lifetime
     * type.
     */
    template<class Self> concept ImplicitLifetime = Marker::Sized<Self> and
    __builtin_is_implicit_lifetime(Self);
}

#endif
#endif