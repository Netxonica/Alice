// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_remove_extents
#define alice_header_guard_meta_remove_extents
#ifdef _MSC_VER
#include "Core/Size.hpp"
#endif

namespace Alice::Meta
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class Self> struct RemoveExtents final
        {
            constexpr compl RemoveExtents() noexcept = delete;

            explicit consteval RemoveExtents() noexcept = delete;

            explicit consteval RemoveExtents(const RemoveExtents&) noexcept = delete;

            explicit consteval RemoveExtents(RemoveExtents&&) noexcept = delete;

            consteval auto operator=(const RemoveExtents&) noexcept -> RemoveExtents& = delete;

            consteval auto operator=(RemoveExtents&&) noexcept -> RemoveExtents& = delete;

            [[nodiscard]] consteval auto operator==(const RemoveExtents&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveExtents&) const noexcept = delete;

            using Type = Self;
        };

        template<class Self> struct RemoveExtents<Self[]> final
        {
            constexpr compl RemoveExtents() noexcept = delete;

            explicit consteval RemoveExtents() noexcept = delete;

            explicit consteval RemoveExtents(const RemoveExtents&) noexcept = delete;

            explicit consteval RemoveExtents(RemoveExtents&&) noexcept = delete;

            consteval auto operator=(const RemoveExtents&) noexcept -> RemoveExtents& = delete;

            consteval auto operator=(RemoveExtents&&) noexcept -> RemoveExtents& = delete;

            [[nodiscard]] consteval auto operator==(const RemoveExtents&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveExtents&) const noexcept = delete;

            using Type = typename RemoveExtents<Self>::Type;
        };

        template<class Self, Size::Native size> struct RemoveExtents<Self[size]> final
        {
            constexpr compl RemoveExtents() noexcept = delete;

            explicit consteval RemoveExtents() noexcept = delete;

            explicit consteval RemoveExtents(const RemoveExtents&) noexcept = delete;

            explicit consteval RemoveExtents(RemoveExtents&&) noexcept = delete;

            consteval auto operator=(const RemoveExtents&) noexcept -> RemoveExtents& = delete;

            consteval auto operator=(RemoveExtents&&) noexcept -> RemoveExtents& = delete;

            [[nodiscard]] consteval auto operator==(const RemoveExtents&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveExtents&) const noexcept = delete;

            using Type = typename RemoveExtents<Self>::Type;
        };
    }
    #endif

    /**
     * @brief Returns @p Self with all the top array extensions removed.
     */
    template<class Self> using RemoveExtents =
    #ifdef _MSC_VER
    typename Detail::RemoveExtents<Self>::Type
    #else
    __remove_all_extents(Self)
    #endif
    ;
}

#endif
#endif