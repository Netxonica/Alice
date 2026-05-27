// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_member_object_pointer
#define alice_header_guard_trait_member_object_pointer
#ifdef _MSC_VER
#include "Trait/Function.hpp"
#endif

namespace Alice::Trait
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class> struct MemberObjectPointer final
        {
            constexpr compl MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer(const MemberObjectPointer&) noexcept = delete;

            explicit consteval MemberObjectPointer(MemberObjectPointer&&) noexcept = delete;

            consteval auto operator=(const MemberObjectPointer&) noexcept -> MemberObjectPointer& =
            delete;

            consteval auto operator=(MemberObjectPointer&&) noexcept -> MemberObjectPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberObjectPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberObjectPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self, class Class> struct MemberObjectPointer<Self Class::*> final
        {
            constexpr compl MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer(const MemberObjectPointer&) noexcept = delete;

            explicit consteval MemberObjectPointer(MemberObjectPointer&&) noexcept = delete;

            consteval auto operator=(const MemberObjectPointer&) noexcept -> MemberObjectPointer& =
            delete;

            consteval auto operator=(MemberObjectPointer&&) noexcept -> MemberObjectPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberObjectPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberObjectPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return not Function<Self>;
            }
        };

        template<class Self, class Class> struct MemberObjectPointer<Self Class::* const> final
        {
            constexpr compl MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer(const MemberObjectPointer&) noexcept = delete;

            explicit consteval MemberObjectPointer(MemberObjectPointer&&) noexcept = delete;

            consteval auto operator=(const MemberObjectPointer&) noexcept -> MemberObjectPointer& =
            delete;

            consteval auto operator=(MemberObjectPointer&&) noexcept -> MemberObjectPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberObjectPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberObjectPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return not Function<Self>;
            }
        };

        template<class Self, class Class> struct MemberObjectPointer<Self Class::* volatile> final
        {
            constexpr compl MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer(const MemberObjectPointer&) noexcept = delete;

            explicit consteval MemberObjectPointer(MemberObjectPointer&&) noexcept = delete;

            consteval auto operator=(const MemberObjectPointer&) noexcept -> MemberObjectPointer& =
            delete;

            consteval auto operator=(MemberObjectPointer&&) noexcept -> MemberObjectPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberObjectPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberObjectPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return not Function<Self>;
            }
        };

        template<class Self, class Class> struct MemberObjectPointer<Self Class::* const volatile>
        final
        {
            constexpr compl MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer() noexcept = delete;

            explicit consteval MemberObjectPointer(const MemberObjectPointer&) noexcept = delete;

            explicit consteval MemberObjectPointer(MemberObjectPointer&&) noexcept = delete;

            consteval auto operator=(const MemberObjectPointer&) noexcept -> MemberObjectPointer& =
            delete;

            consteval auto operator=(MemberObjectPointer&&) noexcept -> MemberObjectPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberObjectPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberObjectPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return not Function<Self>;
            }
        };
    }
    #endif

    /**
     * @brief Satisfied when @p Self is a pointer to a non-static data member.
     */
    template<class Self> concept MemberObjectPointer =
    #ifdef _MSC_VER
    Detail::MemberObjectPointer<Self>::Value()
    #else
    __is_member_object_pointer(Self)
    #endif
    ;
}

#endif
#endif