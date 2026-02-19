// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_unbounded_array
#define alice_header_guard_trait_unbounded_array

namespace Alice::Trait
{
    template<class Self> concept UnboundedArray = __is_unbounded_array(Self);
}

#endif
#endif