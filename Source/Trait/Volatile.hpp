// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_volatile
#define alice_header_guard_trait_volatile

namespace Alice::Trait
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class> struct Volatile final
        {
            constexpr compl Volatile() noexcept = delete;

            explicit consteval Volatile() noexcept = delete;

            explicit consteval Volatile(const Volatile&) noexcept = delete;

            explicit consteval Volatile(Volatile&&) noexcept = delete;

            consteval auto operator=(const Volatile&) noexcept -> Volatile& = delete;

            consteval auto operator=(Volatile&&) noexcept -> Volatile& = delete;

            [[nodiscard]] consteval auto operator==(const Volatile&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Volatile&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self> struct Volatile<volatile Self> final
        {
            constexpr compl Volatile() noexcept = delete;

            explicit consteval Volatile() noexcept = delete;

            explicit consteval Volatile(const Volatile&) noexcept = delete;

            explicit consteval Volatile(Volatile&&) noexcept = delete;

            consteval auto operator=(const Volatile&) noexcept -> Volatile& = delete;

            consteval auto operator=(Volatile&&) noexcept -> Volatile& = delete;

            [[nodiscard]] consteval auto operator==(const Volatile&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const Volatile&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }
    #endif

    /**
     * @brief Satisfied when @p Self is a volatile-qualified type.
     */
    template<class Self> concept Volatile =
    #ifdef _MSC_VER
    Detail::Volatile<Self>::Value()
    #else
    __is_volatile(Self)
    #endif
    ;
}

#endif
#endif