// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_pointer
#define alice_header_guard_trait_pointer

namespace Alice::Trait
{
    template<class Self> concept Pointer = __is_pointer(Self);
}

#endif
#endif