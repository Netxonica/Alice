// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_enumeration
#define alice_header_guard_trait_enumeration

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is an unscoped or scoped enumeration.
     */
    template<class Self> concept Enumeration = __is_enum(Self);
}

#endif
#endif