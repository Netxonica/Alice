// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_same
#define alice_header_guard_trait_same

namespace Alice::Trait
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class, class> struct Same final
        {
            constexpr compl Same() noexcept = delete;

            explicit consteval Same() noexcept = delete;

            explicit consteval Same(const Same&) noexcept = delete;

            explicit consteval Same(Same&&) noexcept = delete;

            consteval auto operator=(const Same&) noexcept -> Same& = delete;

            consteval auto operator=(Same&&) noexcept -> Same& = delete;

            [[nodiscard]] consteval auto operator==(const Same&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Same&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self> struct Same<Self, Self> final
        {
            constexpr compl Same() noexcept = delete;

            explicit consteval Same() noexcept = delete;

            explicit consteval Same(const Same&) noexcept = delete;

            explicit consteval Same(Same&&) noexcept = delete;

            consteval auto operator=(const Same&) noexcept -> Same& = delete;

            consteval auto operator=(Same&&) noexcept -> Same& = delete;

            [[nodiscard]] consteval auto operator==(const Same&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Same&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }
    #endif

    /**
     * @brief Satisfied when @p Self and @p T are strictly the same type (cvref qualifiers
     * included).
     */
    template<class Self, class T> concept Same =
    #ifdef _MSC_VER
    Detail::Same<Self, T>::Value()
    #else
    __is_same(Self, T)
    #endif
    ;
}

#endif
#endif