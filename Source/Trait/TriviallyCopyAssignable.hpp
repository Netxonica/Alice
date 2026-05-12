// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_trivially_copy_assignable
#define alice_header_guard_trait_trivially_copy_assignable

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self has an accessible trivial copy assignment operator.
     */
    template<class Self> concept TriviallyCopyAssignable = __is_trivially_assignable(Self&, const
    Self&);
}

#endif
#endif