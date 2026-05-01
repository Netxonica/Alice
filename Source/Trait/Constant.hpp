// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_constant
#define alice_header_guard_trait_constant

namespace Alice::Trait
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class> struct Constant final
        {
            constexpr compl Constant() noexcept = delete;

            explicit consteval Constant() noexcept = delete;

            explicit consteval Constant(const Constant&) noexcept = delete;

            explicit consteval Constant(Constant&&) noexcept = delete;

            consteval auto operator=(const Constant&) noexcept -> Constant& = delete;

            consteval auto operator=(Constant&&) noexcept -> Constant& = delete;

            [[nodiscard]] consteval auto operator==(const Constant&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Constant&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self> struct Constant<const Self> final
        {
            constexpr compl Constant() noexcept = delete;

            explicit consteval Constant() noexcept = delete;

            explicit consteval Constant(const Constant&) noexcept = delete;

            explicit consteval Constant(Constant&&) noexcept = delete;

            consteval auto operator=(const Constant&) noexcept -> Constant& = delete;

            consteval auto operator=(Constant&&) noexcept -> Constant& = delete;

            [[nodiscard]] consteval auto operator==(const Constant&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Constant&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }
    #endif

    /**
     * @brief Satisfied when @p Self is a const-qualified type.
     */
    template<class Self> concept Constant =
    #ifdef _MSC_VER
    Detail::Constant<Self>::Value()
    #else
    __is_const(Self)
    #endif
    ;
}

#endif
#endif