// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_same
#define alice_header_guard_trait_same

namespace Alice::Trait
{
    template<class Self, class T> concept Same = __is_same(Self, T);
}

#endif
#endif