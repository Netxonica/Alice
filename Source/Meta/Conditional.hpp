// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_conditional
#define alice_header_guard_meta_conditional

namespace Alice::Meta
{
    namespace Detail
    {
        template<bool, class Self, class> struct Conditional final
        {
            constexpr compl Conditional() noexcept = delete;

            explicit consteval Conditional() noexcept = delete;

            explicit consteval Conditional(const Conditional&) noexcept = delete;

            explicit consteval Conditional(Conditional&&) noexcept = delete;

            consteval auto operator=(const Conditional&) noexcept -> Conditional& = delete;

            consteval auto operator=(Conditional&&) noexcept -> Conditional& = delete;

            [[nodiscard]] consteval auto operator==(const Conditional&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Conditional&) const noexcept = delete;

            using Type = Self;
        };

        template<class Other, class Self> struct Conditional<false, Other, Self> final
        {
            constexpr compl Conditional() noexcept = delete;

            explicit consteval Conditional() noexcept = delete;

            explicit consteval Conditional(const Conditional&) noexcept = delete;

            explicit consteval Conditional(Conditional&&) noexcept = delete;

            consteval auto operator=(const Conditional&) noexcept -> Conditional& = delete;

            consteval auto operator=(Conditional&&) noexcept -> Conditional& = delete;

            [[nodiscard]] consteval auto operator==(const Conditional&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Conditional&) const noexcept = delete;

            using Type = Self;
        };
    }

    /**
     * @brief Returns @p True when @p Condition is true, or @p False when @p Condition is false.
     */
    template<bool Condition, class True, class False> using Conditional = typename Detail::
    Conditional<Condition, True, False>::Type;
}

#endif
#endif