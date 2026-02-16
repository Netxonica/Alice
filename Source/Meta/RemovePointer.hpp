// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_remove_pointer
#define alice_header_guard_meta_remove_pointer

namespace Alice::Meta
{
    template<class Self> using RemovePointer = __remove_pointer(Self);
}

#endif
#endif