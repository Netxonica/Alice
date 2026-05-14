// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_convert_into
#define alice_header_guard_convert_into
#include "Trait/Same.hpp"
#include "Marker/Sized.hpp"

namespace Alice::Convert
{
    /**
     * @brief Satisfied when both @p Self and @p To satisfy Alice::Marker::Sized and @p Self
     * implements a non-static member function named @b Into , which returns a @p Self instance
     * converted to @p To, without failing.
     */
    template<class Self, class To> concept Into = Marker::Sized<Self> and Marker::Sized<To> and
    requires(Self self)
    {
        {$forward(self).Into()} -> Trait::Same<To>;
    } and not requires
    {
        {Self::Into()} -> Trait::Same<To>;
    };
}

#endif
#endif