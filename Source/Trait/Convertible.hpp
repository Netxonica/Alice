// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_convertible
#define alice_header_guard_trait_convertible

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is convertible to @p To .
     */
    template<class Self, class To> concept Convertible =
    #ifdef _MSC_VER
    __is_convertible_to(Self, To)
    #else
    __is_convertible(Self, To)
    #endif
    ;
}

#endif
#endif