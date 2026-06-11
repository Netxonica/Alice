// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_final
#define alice_header_guard_trait_final
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies Alice::Marker::Sized and is a final class.
     */
    template<class Self> concept Final = Marker::Sized<Self> and __is_final(Self);
}

#endif
#endif