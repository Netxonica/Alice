// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_void
#define alice_header_guard_trait_void

namespace Alice::Trait
{
    namespace Detail
    {
        template<class> struct [[nodiscard]] Void final
        {
            constexpr ~Void() noexcept = delete;

            explicit consteval Void() noexcept = delete;

            explicit consteval Void(const Void&) noexcept = delete;

            explicit consteval Void(Void&&) noexcept = delete;

            consteval auto operator=(const Void&) noexcept -> Void& = delete;

            consteval auto operator=(Void&&) noexcept -> Void& = delete;

            [[nodiscard]] consteval auto operator==(const Void&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Void&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<> struct [[nodiscard]] Void<void> final
        {
            constexpr ~Void() noexcept = delete;

            explicit consteval Void() noexcept = delete;

            explicit consteval Void(const Void&) noexcept = delete;

            explicit consteval Void(Void&&) noexcept = delete;

            consteval auto operator=(const Void&) noexcept -> Void& = delete;

            consteval auto operator=(Void&&) noexcept -> Void& = delete;

            [[nodiscard]] consteval auto operator==(const Void&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Void&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<> struct [[nodiscard]] Void<const void> final
        {
            constexpr ~Void() noexcept = delete;

            explicit consteval Void() noexcept = delete;

            explicit consteval Void(const Void&) noexcept = delete;

            explicit consteval Void(Void&&) noexcept = delete;

            consteval auto operator=(const Void&) noexcept -> Void& = delete;

            consteval auto operator=(Void&&) noexcept -> Void& = delete;

            [[nodiscard]] consteval auto operator==(const Void&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Void&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<> struct [[nodiscard]] Void<volatile void> final
        {
            constexpr ~Void() noexcept = delete;

            explicit consteval Void() noexcept = delete;

            explicit consteval Void(const Void&) noexcept = delete;

            explicit consteval Void(Void&&) noexcept = delete;

            consteval auto operator=(const Void&) noexcept -> Void& = delete;

            consteval auto operator=(Void&&) noexcept -> Void& = delete;

            [[nodiscard]] consteval auto operator==(const Void&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Void&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<> struct [[nodiscard]] Void<volatile const void> final
        {
            constexpr ~Void() noexcept = delete;

            explicit consteval Void() noexcept = delete;

            explicit consteval Void(const Void&) noexcept = delete;

            explicit consteval Void(Void&&) noexcept = delete;

            consteval auto operator=(const Void&) noexcept -> Void& = delete;

            consteval auto operator=(Void&&) noexcept -> Void& = delete;

            [[nodiscard]] consteval auto operator==(const Void&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Void&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }

    template<class Self> concept Void = Detail::Void<Self>::Value();
}

#endif
#endif