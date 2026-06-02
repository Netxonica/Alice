// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_referenceable
#define alice_header_guard_trait_referenceable
#include "Trait/Object.hpp"
#include "Trait/Reference.hpp"

namespace Alice::Trait
{
    namespace Detail
    {
        template<class Self> struct Referenceable final
        {
            constexpr compl Referenceable() noexcept = delete;

            explicit consteval Referenceable() noexcept = delete;

            explicit consteval Referenceable(const Referenceable&) noexcept = delete;

            explicit consteval Referenceable(Referenceable&&) noexcept = delete;

            consteval auto operator=(const Referenceable&) noexcept -> Referenceable& = delete;

            consteval auto operator=(Referenceable&&) noexcept -> Referenceable& = delete;

            [[nodiscard]] consteval auto operator==(const Referenceable&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Referenceable&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return ::Alice::Trait::Object<Self> or ::Alice::Trait::Reference<Self>;
            }
        };

        template<class Self> struct Referenceable<Self(...)> final
        {
            constexpr compl Referenceable() noexcept = delete;

            explicit consteval Referenceable() noexcept = delete;

            explicit consteval Referenceable(const Referenceable&) noexcept = delete;

            explicit consteval Referenceable(Referenceable&&) noexcept = delete;

            consteval auto operator=(const Referenceable&) noexcept -> Referenceable& = delete;

            consteval auto operator=(Referenceable&&) noexcept -> Referenceable& = delete;

            [[nodiscard]] consteval auto operator==(const Referenceable&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Referenceable&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self> struct Referenceable<Self(...) noexcept> final
        {
            constexpr compl Referenceable() noexcept = delete;

            explicit consteval Referenceable() noexcept = delete;

            explicit consteval Referenceable(const Referenceable&) noexcept = delete;

            explicit consteval Referenceable(Referenceable&&) noexcept = delete;

            consteval auto operator=(const Referenceable&) noexcept -> Referenceable& = delete;

            consteval auto operator=(Referenceable&&) noexcept -> Referenceable& = delete;

            [[nodiscard]] consteval auto operator==(const Referenceable&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Referenceable&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class... Arguments> struct Referenceable<Self(Arguments...)> final
        {
            constexpr compl Referenceable() noexcept = delete;

            explicit consteval Referenceable() noexcept = delete;

            explicit consteval Referenceable(const Referenceable&) noexcept = delete;

            explicit consteval Referenceable(Referenceable&&) noexcept = delete;

            consteval auto operator=(const Referenceable&) noexcept -> Referenceable& = delete;

            consteval auto operator=(Referenceable&&) noexcept -> Referenceable& = delete;

            [[nodiscard]] consteval auto operator==(const Referenceable&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Referenceable&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class... Arguments> struct Referenceable<Self(Arguments...) noexcept>
        final
        {
            constexpr compl Referenceable() noexcept = delete;

            explicit consteval Referenceable() noexcept = delete;

            explicit consteval Referenceable(const Referenceable&) noexcept = delete;

            explicit consteval Referenceable(Referenceable&&) noexcept = delete;

            consteval auto operator=(const Referenceable&) noexcept -> Referenceable& = delete;

            consteval auto operator=(Referenceable&&) noexcept -> Referenceable& = delete;

            [[nodiscard]] consteval auto operator==(const Referenceable&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Referenceable&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }

    /**
     * @brief Satisfied when @p Self is referenceable, meaning you can create a reference type to
     * its type.
     */
    template<class Self> concept Referenceable = Detail::Referenceable<Self>::Value();
}

#endif
#endif