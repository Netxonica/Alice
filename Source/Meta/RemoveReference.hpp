// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_remove_reference
#define alice_header_guard_meta_remove_reference
#include "Meta/RemoveLvalueReference.hpp"
#include "Meta/RemoveRvalueReference.hpp"

namespace Alice::Meta
{
    /**
     * @brief Returns @p Self without lvalue or rvalue references, if any.
     */
    template<class Self> using RemoveReference = RemoveRvalueReference<RemoveLvalueReference<Self>>
    ;
}

#endif
#endif