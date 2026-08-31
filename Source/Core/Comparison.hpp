// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_comparison
#define alice_header_guard_core_comparison

namespace Alice
{
    /**
     * @brief The resulting type of the three-way operator.
     */
    enum class [[nodiscard]] Comparison : unsigned char
    {
        Less = 0u,
        Equal = 1u,
        Greater = 2u
    };
}

#endif
#endif