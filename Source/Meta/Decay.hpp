// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_decay
#define alice_header_guard_meta_decay
#ifdef _MSC_VER
#include "Trait/Function.hpp"
#include "Meta/Conditional.hpp"
#include "Meta/RemoveConstant.hpp"
#include "Meta/RemoveVolatile.hpp"
#endif

namespace Alice::Meta
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class Self> struct Decay final
        {
            constexpr compl Decay() noexcept = delete;

            explicit consteval Decay() noexcept = delete;

            explicit consteval Decay(const Decay&) noexcept = delete;

            explicit consteval Decay(Decay&&) noexcept = delete;

            consteval auto operator=(const Decay&) noexcept -> Decay& = delete;

            consteval auto operator=(Decay&&) noexcept -> Decay& = delete;

            [[nodiscard]] consteval auto operator==(const Decay&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Decay&) const noexcept = delete;

            using Type = ::Alice::Meta::Conditional<Trait::Function<Self>, Self*, ::Alice::Meta::
            RemoveConstant<::Alice::Meta::RemoveVolatile<Self>>>;
        };

        template<class Self> struct Decay<Self&> final
        {
            constexpr compl Decay() noexcept = delete;

            explicit consteval Decay() noexcept = delete;

            explicit consteval Decay(const Decay&) noexcept = delete;

            explicit consteval Decay(Decay&&) noexcept = delete;

            consteval auto operator=(const Decay&) noexcept -> Decay& = delete;

            consteval auto operator=(Decay&&) noexcept -> Decay& = delete;

            [[nodiscard]] consteval auto operator==(const Decay&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Decay&) const noexcept = delete;

            using Type = typename Decay<Self>::Type;
        };

        template<class Self> struct Decay<Self&&> final
        {
            constexpr compl Decay() noexcept = delete;

            explicit consteval Decay() noexcept = delete;

            explicit consteval Decay(const Decay&) noexcept = delete;

            explicit consteval Decay(Decay&&) noexcept = delete;

            consteval auto operator=(const Decay&) noexcept -> Decay& = delete;

            consteval auto operator=(Decay&&) noexcept -> Decay& = delete;

            [[nodiscard]] consteval auto operator==(const Decay&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Decay&) const noexcept = delete;

            using Type = typename Decay<Self>::Type;
        };

        template<class Self, decltype(sizeof(bool)) size> struct Decay<Self[size]> final
        {
            constexpr compl Decay() noexcept = delete;

            explicit consteval Decay() noexcept = delete;

            explicit consteval Decay(const Decay&) noexcept = delete;

            explicit consteval Decay(Decay&&) noexcept = delete;

            consteval auto operator=(const Decay&) noexcept -> Decay& = delete;

            consteval auto operator=(Decay&&) noexcept -> Decay& = delete;

            [[nodiscard]] consteval auto operator==(const Decay&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Decay&) const noexcept = delete;

            using Type = Self*;
        };

        template<class Self> struct Decay<Self[]> final
        {
            constexpr compl Decay() noexcept = delete;

            explicit consteval Decay() noexcept = delete;

            explicit consteval Decay(const Decay&) noexcept = delete;

            explicit consteval Decay(Decay&&) noexcept = delete;

            consteval auto operator=(const Decay&) noexcept -> Decay& = delete;

            consteval auto operator=(Decay&&) noexcept -> Decay& = delete;

            [[nodiscard]] consteval auto operator==(const Decay&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Decay&) const noexcept = delete;

            using Type = Self*;
        };
    }
    #endif

    /**
     * @brief Returns @p Self with the type conversions equivalent to the ones performed when
     * passing it as a function argument by value.
     */
    template<class Self> using Decay =
    #ifdef _MSC_VER
    typename Detail::Decay<Self>::Type
    #else
    __decay(Self)
    #endif
    ;
}

#endif
#endif