// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_layoutable
#define alice_header_guard_trait_layoutable

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is layout-compatible with @p Type
     */
    template<class Self, class Type> concept Layoutable = __is_layout_compatible(Self, Type);
}

#endif
#endif