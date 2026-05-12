// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_trivially_move_assignable
#define alice_header_guard_trait_trivially_move_assignable

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self has an accessible trivial move assignment operator.
     */
    template<class Self> concept TriviallyMoveAssignable = __is_trivially_assignable(Self&, Self&&)
    ;
}

#endif
#endif