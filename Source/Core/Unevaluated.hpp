// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_unevaluated
#define alice_header_guard_core_unevaluated

namespace Alice
{
    /**
     * @brief Meant only to be used in unevaluated contexts. It represent an unevaluated object of
     * type Self&&.
     */
    template<class Self> [[nodiscard]] consteval auto Unevaluated() noexcept -> Self&&;
}

#endif
#endif