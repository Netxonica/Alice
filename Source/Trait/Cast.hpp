// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_cast
#define alice_header_guard_trait_cast
#include "Marker/Sized.hpp"

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self can be static casted to @p To and both @p Self and @p To
     * satisfy Alice::Marker::Sized.
     */
    template<class Self, class To> concept Cast = Marker::Sized<Self> and Marker::Sized<To> and
    requires(Self self)
    {
        static_cast<To>($forward(self));
    };
}

#endif
#endif