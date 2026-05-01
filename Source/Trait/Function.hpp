// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_function
#define alice_header_guard_trait_function
#ifdef __MSC_VER
#include "Trait/Constant.hpp"
#include "Trait/Reference.hpp"
#endif

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is a free function or an static member function type.
     */
    template<class Self> concept Function =
    #ifdef _MSC_VER
    not Constant<Self> and not Reference<Self>
    #else
    __is_function(Self)
    #endif
    ;
}

#endif
#endif