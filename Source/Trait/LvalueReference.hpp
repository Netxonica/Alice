// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_lvalue_reference
#define alice_header_guard_trait_lvalue_reference

namespace Alice::Trait
{
    #ifndef __clang__
    namespace Detail
    {
        template<class> struct LvalueReference final
        {
            constexpr compl LvalueReference() noexcept = delete;

            explicit consteval LvalueReference() noexcept = delete;

            explicit consteval LvalueReference(const LvalueReference&) noexcept = delete;

            explicit consteval LvalueReference(LvalueReference&&) noexcept = delete;

            consteval auto operator=(const LvalueReference&) noexcept -> LvalueReference& = delete;

            consteval auto operator=(LvalueReference&&) noexcept -> LvalueReference& = delete;

            [[nodiscard]] consteval auto operator==(const LvalueReference&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const LvalueReference&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self> struct LvalueReference<Self&> final
        {
            constexpr compl LvalueReference() noexcept = delete;

            explicit consteval LvalueReference() noexcept = delete;

            explicit consteval LvalueReference(const LvalueReference&) noexcept = delete;

            explicit consteval LvalueReference(LvalueReference&&) noexcept = delete;

            consteval auto operator=(const LvalueReference&) noexcept -> LvalueReference& = delete;

            consteval auto operator=(LvalueReference&&) noexcept -> LvalueReference& = delete;

            [[nodiscard]] consteval auto operator==(const LvalueReference&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const LvalueReference&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }
    #endif

    /**
     * @brief Satisfied when @p Self is an lvalue reference type.
     */
    template<class Self> concept LvalueReference =
    #ifdef __clang__
    __is_lvalue_reference(Self)
    #else
    Detail::LvalueReference<Self>::Value()
    #endif
    ;
}

#endif
#endif