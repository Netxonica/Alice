// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_union
#define alice_header_guard_trait_union

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is an untagged union.
     */
    template<class Self> concept Union = __is_union(Self);
}

#endif
#endif