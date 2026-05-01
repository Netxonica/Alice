// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_unbounded_array
#define alice_header_guard_trait_unbounded_array

namespace Alice::Trait
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class> struct UnboundedArray final
        {
            constexpr compl UnboundedArray() noexcept = delete;

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

        template<class Self> struct UnboundedArray<Self[]> final
        {
            constexpr compl UnboundedArray() noexcept = delete;

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
    #endif

    /**
     * @brief Satisfied when @p Self is an unbounded array type.
     */
    template<class Self> concept UnboundedArray =
    #ifdef _MSC_VER
    Detail::UnboundedArray<Self>::Value()
    #else
    __is_unbounded_array(Self)
    #endif
    ;
}

#endif
#endif