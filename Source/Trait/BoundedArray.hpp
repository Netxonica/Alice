// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_bounded_array
#define alice_header_guard_trait_bounded_array
#ifdef _MSC_VER
#include "Core/Size.hpp"
#endif

namespace Alice::Trait
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class> struct BoundedArray final
        {
            constexpr compl BoundedArray() noexcept = delete;

            explicit consteval BoundedArray() noexcept = delete;

            explicit consteval BoundedArray(const BoundedArray&) noexcept = delete;

            explicit consteval BoundedArray(BoundedArray&&) noexcept = delete;

            consteval auto operator=(const BoundedArray&) noexcept -> BoundedArray& = delete;

            consteval auto operator=(BoundedArray&&) noexcept -> BoundedArray& = delete;

            [[nodiscard]] consteval auto operator==(const BoundedArray&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const BoundedArray&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self, Size::Native size> struct BoundedArray<Self[size]> final
        {
            constexpr compl BoundedArray() noexcept = delete;

            explicit consteval BoundedArray() noexcept = delete;

            explicit consteval BoundedArray(const BoundedArray&) noexcept = delete;

            explicit consteval BoundedArray(BoundedArray&&) noexcept = delete;

            consteval auto operator=(const BoundedArray&) noexcept -> BoundedArray& = delete;

            consteval auto operator=(BoundedArray&&) noexcept -> BoundedArray& = delete;

            [[nodiscard]] consteval auto operator==(const BoundedArray&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const BoundedArray&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }
    #endif

    /**
     * @brief Satisfied when @p Self is a bounded array type.
     */
    template<class Self> concept BoundedArray =
    #ifdef _MSC_VER
    Detail::BoundedArray<Self>::Value()
    #else
    __is_bounded_array(Self)
    #endif
    ;
}

#endif
#endif