// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_unbounded_array
#define alice_header_guard_trait_unbounded_array

namespace Alice::Trait
{
    namespace Detail
    {
        template<class> struct [[nodiscard]] UnboundedArray final
        {
            constexpr ~UnboundedArray() noexcept = delete;

            explicit consteval UnboundedArray() noexcept = delete;

            explicit consteval UnboundedArray(const UnboundedArray&) noexcept = delete;

            explicit consteval UnboundedArray(UnboundedArray&&) noexcept = delete;

            consteval auto operator=(const UnboundedArray&) noexcept -> UnboundedArray& = delete;

            consteval auto operator=(UnboundedArray&&) noexcept -> UnboundedArray& = delete;

            [[nodiscard]] consteval auto operator==(const UnboundedArray&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const UnboundedArray&) const noexcept = delete
            ;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };
        
        template<class Self> struct [[nodiscard]] UnboundedArray<Self[]> final
        {
            constexpr ~UnboundedArray() noexcept = delete;

            explicit consteval UnboundedArray() noexcept = delete;

            explicit consteval UnboundedArray(const UnboundedArray&) noexcept = delete;

            explicit consteval UnboundedArray(UnboundedArray&&) noexcept = delete;

            consteval auto operator=(const UnboundedArray&) noexcept -> UnboundedArray& = delete;

            consteval auto operator=(UnboundedArray&&) noexcept -> UnboundedArray& = delete;

            [[nodiscard]] consteval auto operator==(const UnboundedArray&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const UnboundedArray&) const noexcept = delete
            ;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }

    template<class Self> concept UnboundedArray = Detail::UnboundedArray<Self>::Value();
}

#endif
#endif