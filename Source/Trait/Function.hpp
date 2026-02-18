// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_function
#define alice_header_guard_trait_function

namespace Alice::Trait
{
    template<class Self> concept Function = __is_function(Self);
}

#endif
#endif