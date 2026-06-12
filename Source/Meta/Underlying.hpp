// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_underlying
#define alice_header_guard_meta_underlying
#include "Trait/Enumeration.hpp"

namespace Alice::Meta
{
    /**
     * @brief @p Self must satisfy Alice::Trait::Enumeration. Returns the underlying type of
     * @p Self
     */
    template<Trait::Enumeration Self> using Underlying = __underlying_type(Self);
}

#endif
#endif