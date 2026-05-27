// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_member_pointer
#define alice_header_guard_trait_member_pointer
#ifdef _MSC_VER
#include "Trait/MemberObjectPointer.hpp"
#include "Trait/MemberFunctionPointer.hpp"
#endif

namespace Alice::Trait
{
    /**
     * @brief Satisfied when @p Self is a pointer to a non-static member function or non-static
     * data member.
     */
    template<class Self> concept MemberPointer =
    #ifdef _MSC_VER
    MemberObjectPointer<Self> or MemberFunctionPointer<Self>
    #else
    __is_member_pointer(Self)
    #endif
    ;
}

#endif
#endif