// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_remove_pointer
#define alice_header_guard_meta_remove_pointer

namespace Alice::Meta
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class Self> struct RemovePointer final
        {
            constexpr compl RemovePointer() noexcept = delete;

            explicit consteval RemovePointer() noexcept = delete;

            explicit consteval RemovePointer(const RemovePointer&) noexcept = delete;

            explicit consteval RemovePointer(RemovePointer&&) noexcept = delete;

            consteval auto operator=(const RemovePointer&) noexcept -> RemovePointer& = delete;

            consteval auto operator=(RemovePointer&&) noexcept -> RemovePointer& = delete;

            [[nodiscard]] consteval auto operator==(const RemovePointer&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemovePointer&) const noexcept = delete;

            using Type = Self;
        };

        template<class Self> struct RemovePointer<Self*> final
        {
            constexpr compl RemovePointer() noexcept = delete;

            explicit consteval RemovePointer() noexcept = delete;

            explicit consteval RemovePointer(const RemovePointer&) noexcept = delete;

            explicit consteval RemovePointer(RemovePointer&&) noexcept = delete;

            consteval auto operator=(const RemovePointer&) noexcept -> RemovePointer& = delete;

            consteval auto operator=(RemovePointer&&) noexcept -> RemovePointer& = delete;

            [[nodiscard]] consteval auto operator==(const RemovePointer&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemovePointer&) const noexcept = delete;

            using Type = Self;
        };

        template<class Self> struct RemovePointer<Self* const> final
        {
            constexpr compl RemovePointer() noexcept = delete;

            explicit consteval RemovePointer() noexcept = delete;

            explicit consteval RemovePointer(const RemovePointer&) noexcept = delete;

            explicit consteval RemovePointer(RemovePointer&&) noexcept = delete;

            consteval auto operator=(const RemovePointer&) noexcept -> RemovePointer& = delete;

            consteval auto operator=(RemovePointer&&) noexcept -> RemovePointer& = delete;

            [[nodiscard]] consteval auto operator==(const RemovePointer&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemovePointer&) const noexcept = delete;

            using Type = Self;
        };

        template<class Self> struct RemovePointer<Self* volatile> final
        {
            constexpr compl RemovePointer() noexcept = delete;

            explicit consteval RemovePointer() noexcept = delete;

            explicit consteval RemovePointer(const RemovePointer&) noexcept = delete;

            explicit consteval RemovePointer(RemovePointer&&) noexcept = delete;

            consteval auto operator=(const RemovePointer&) noexcept -> RemovePointer& = delete;

            consteval auto operator=(RemovePointer&&) noexcept -> RemovePointer& = delete;

            [[nodiscard]] consteval auto operator==(const RemovePointer&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemovePointer&) const noexcept = delete;

            using Type = Self;
        };

        template<class Self> struct RemovePointer<Self* const volatile> final
        {
            constexpr compl RemovePointer() noexcept = delete;

            explicit consteval RemovePointer() noexcept = delete;

            explicit consteval RemovePointer(const RemovePointer&) noexcept = delete;

            explicit consteval RemovePointer(RemovePointer&&) noexcept = delete;

            consteval auto operator=(const RemovePointer&) noexcept -> RemovePointer& = delete;

            consteval auto operator=(RemovePointer&&) noexcept -> RemovePointer& = delete;

            [[nodiscard]] consteval auto operator==(const RemovePointer&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemovePointer&) const noexcept = delete;

            using Type = Self;
        };
    }
    #endif

    /**
     * @brief Returns @p Self without the top-most pointer, if any.
     */
    template<class Self> using RemovePointer =
    #ifdef _MSC_VER
    typename Detail::RemovePointer<Self>::Type
    #else
    __remove_pointer(Self)
    #endif
    ;
}

#endif
#endif