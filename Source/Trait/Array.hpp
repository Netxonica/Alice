// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_array
#define alice_header_guard_trait_array
#include "Trait/BoundedArray.hpp"
#include "Trait/UnboundedArray.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies @ref Alice::Trait::BoundedArray or @ref
     * Alice::Trait::UnboundedArray.
     */
    template<class Self> concept Array = BoundedArray<Self> or UnboundedArray<Self>;
}

#endif
#endif