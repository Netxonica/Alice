// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_null_pointer
#define alice_header_guard_trait_null_pointer

namespace Alice::Trait
{
    template<class Self> concept NullPointer = __is_same(decltype(nullptr), __remove_cv(Self));
}

#endif
#endif