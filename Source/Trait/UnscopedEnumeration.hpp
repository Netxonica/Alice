// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_unscoped_enumeration
#define alice_header_guard_trait_unscoped_enumeration
#include "Trait/Enumeration.hpp"
#include "Trait/ScopedEnumeration.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is an unscoped enumeration.
     */
    template<class Self> concept UnscopedEnumeration = Enumeration<Self> and not ScopedEnumeration<
    Self>;
}

#endif
#endif