// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_convert_from
#define alice_header_guard_convert_from
#include "Trait/Same.hpp"
#include "Marker/Sized.hpp"

namespace Alice::Convert
{
    /**
     * @brief Satisfied when both @p Self and @p T satisfy Alice::Marker::Sized and @p Self
     * implements an static member function named @b From , which returns a converted input
     * parameter of type @p T to @p Self, without failing.
     */
    template<class Self, class T> concept From = Marker::Sized<Self> and Marker::Sized<T> and
    requires(T from)
    {
        {Self::From($forward(from))} -> Trait::Same<Self>;
    };
}

#endif
#endif