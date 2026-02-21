// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_reference
#define alice_header_guard_trait_reference

namespace Alice::Trait
{
    template<class Self> concept Reference = __is_reference(Self);
}

#endif
#endif