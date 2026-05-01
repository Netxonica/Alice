// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_rvalue_reference
#define alice_header_guard_trait_rvalue_reference

namespace Alice::Trait
{
    #ifndef __clang__
    namespace Detail
    {
        template<class> struct RvalueReference final
        {
            constexpr compl RvalueReference() noexcept = delete;

            explicit consteval RvalueReference() noexcept = delete;

            explicit consteval RvalueReference(const RvalueReference&) noexcept = delete;

            explicit consteval RvalueReference(RvalueReference&&) noexcept = delete;

            consteval auto operator=(const RvalueReference&) noexcept -> RvalueReference& = delete;

            consteval auto operator=(RvalueReference&&) noexcept -> RvalueReference& = delete;

            [[nodiscard]] consteval auto operator==(const RvalueReference&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const RvalueReference&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self> struct RvalueReference<Self&&> final
        {
            constexpr compl RvalueReference() noexcept = delete;

            explicit consteval RvalueReference() noexcept = delete;

            explicit consteval RvalueReference(const RvalueReference&) noexcept = delete;

            explicit consteval RvalueReference(RvalueReference&&) noexcept = delete;

            consteval auto operator=(const RvalueReference&) noexcept -> RvalueReference& = delete;

            consteval auto operator=(RvalueReference&&) noexcept -> RvalueReference& = delete;

            [[nodiscard]] consteval auto operator==(const RvalueReference&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const RvalueReference&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }
    #endif

    /**
     * @brief Satisfied when @p Self is an rvalue reference type.
     */
    template<class Self> concept RvalueReference =
    #ifdef __clang__
    __is_rvalue_reference(Self)
    #else
    Detail::RvalueReference<Self>::Value()
    #endif
    ;
}

#endif
#endif