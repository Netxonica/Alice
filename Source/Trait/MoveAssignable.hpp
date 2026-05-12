// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_move_assignable
#define alice_header_guard_trait_move_assignable

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self has an accessible move assignment operator.
     */
    template<class Self> concept MoveAssignable = __is_assignable(Self&, Self&&);
}

#endif
#endif