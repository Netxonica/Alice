// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_object
#define alice_header_guard_trait_object
#ifdef _MSC_VER
#include "Trait/Void.hpp"
#include "Trait/Constant.hpp"
#endif

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is an object.
     */
    template<class Self> concept Object =
    #ifdef _MSC_VER
    Constant<const Self> and not Void<Self>
    #else
    __is_object(Self)
    #endif
    ;
}

#endif
#endif