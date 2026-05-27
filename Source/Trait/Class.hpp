// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_class
#define alice_header_guard_trait_class

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is an structure or class.
     */
    template<class Self> concept Class = __is_class(Self);
}

#endif
#endif