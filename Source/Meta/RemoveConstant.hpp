// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_remove_constant
#define alice_header_guard_meta_remove_constant

namespace Alice::Meta
{
    #ifndef __clang__
    namespace Detail
    {
        template<class Self> struct RemoveConstant final
        {
            constexpr compl RemoveConstant() noexcept = delete;

            explicit consteval RemoveConstant() noexcept = delete;

            explicit consteval RemoveConstant(const RemoveConstant&) noexcept = delete;
            
            explicit consteval RemoveConstant(RemoveConstant&&) noexcept = delete;

            consteval auto operator=(const RemoveConstant&) noexcept -> RemoveConstant& = delete;

            consteval auto operator=(RemoveConstant&&) noexcept -> RemoveConstant& = delete;

            [[nodiscard]] consteval auto operator==(const RemoveConstant&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveConstant&) const noexcept = delete
            ;

            using Type = Self;
        };

        template<class Self> struct RemoveConstant<const Self> final
        {
            constexpr compl RemoveConstant() noexcept = delete;

            explicit consteval RemoveConstant() noexcept = delete;

            explicit consteval RemoveConstant(const RemoveConstant&) noexcept = delete;
            
            explicit consteval RemoveConstant(RemoveConstant&&) noexcept = delete;

            consteval auto operator=(const RemoveConstant&) noexcept -> RemoveConstant& = delete;

            consteval auto operator=(RemoveConstant&&) noexcept -> RemoveConstant& = delete;

            [[nodiscard]] consteval auto operator==(const RemoveConstant&) const noexcept -> bool =
            delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveConstant&) const noexcept = delete
            ;

            using Type = Self;
        };
    }
    #endif

    /**
     * @brief Returns @p Self with the top-most const qualifier removed, if any.
     */
    template<class Self> using RemoveConstant =
    #ifdef __clang__
    __remove_const(Self)
    #else
    typename Detail::RemoveConstant<Self>::Type
    #endif
    ;
}

#endif
#endif