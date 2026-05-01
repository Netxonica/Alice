// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_reference
#define alice_header_guard_trait_reference
#include "Trait/LvalueReference.hpp"
#include "Trait/RvalueReference.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self satisfies @ref Alice::Trait::LvalueReference or @ref
     * Alice::Trait::RvalueReference.
     */
    template<class Self> concept Reference = LvalueReference<Self> or RvalueReference<Self>;
}

#endif
#endif