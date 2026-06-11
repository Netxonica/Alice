// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_polymorphic
#define alice_header_guard_trait_polymorphic
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and is a non-union class that
     * declares or inherits at least one virtual function.
     */
    template<class Self> concept Polymorphic = Marker::Sized<Self> and __is_polymorphic(Self);
}

#endif
#endif