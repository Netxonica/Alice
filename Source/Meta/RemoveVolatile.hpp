// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_remove_volatile
#define alice_header_guard_meta_remove_volatile

namespace Alice::Meta
{
    #ifndef __clang__
    namespace Detail
    {
        template<class Self> struct RemoveVolatile final
        {
            constexpr compl RemoveVolatile() noexcept = delete;

            explicit consteval RemoveVolatile() noexcept = delete;

            explicit consteval RemoveVolatile(const RemoveVolatile&) noexcept = delete;

            explicit consteval RemoveVolatile(RemoveVolatile&&) noexcept = delete;

            consteval auto operator=(const RemoveVolatile&) noexcept -> RemoveVolatile& = delete;

            consteval auto operator=(RemoveVolatile&&) noexcept -> RemoveVolatile& = delete;

            [[nodiscard]] consteval auto operator==(const RemoveVolatile&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveVolatile&) const noexcept = delete
            ;

            using Type = Self;
        };

        template<class Self> struct RemoveVolatile<volatile Self> final
        {
            constexpr compl RemoveVolatile() noexcept = delete;

            explicit consteval RemoveVolatile() noexcept = delete;

            explicit consteval RemoveVolatile(const RemoveVolatile&) noexcept = delete;

            explicit consteval RemoveVolatile(RemoveVolatile&&) noexcept = delete;

            consteval auto operator=(const RemoveVolatile&) noexcept -> RemoveVolatile& = delete;

            consteval auto operator=(RemoveVolatile&&) noexcept -> RemoveVolatile& = delete;

            [[nodiscard]] consteval auto operator==(const RemoveVolatile&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveVolatile&) const noexcept = delete
            ;

            using Type = Self;
        };
    }
    #endif

    /**
     * @brief Returns @p Self with the top-most volatile qualifier removed, if any.
     */
    template<class Self> using RemoveVolatile =
    #ifdef __clang__
    __remove_volatile(Self)
    #else
    typename Detail::RemoveVolatile<Self>::Type
    #endif
    ;
}

#endif
#endif