// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_member_function_pointer
#define alice_header_guard_trait_member_function_pointer

namespace Alice::Trait
{
    #ifdef _MSC_VER
    namespace Detail
    {
        template<class> struct MemberFunctionPointer final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...)> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) volatile> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) volatile noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const volatile> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const volatile noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) &> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) & noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const&> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const& noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) volatile&> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) volatile& noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const volatile&> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const volatile& noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) &&> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) && noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const&&> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const&& noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) volatile&&> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) volatile&& noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const volatile&&> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct MemberFunctionPointer<Self (
        Class::*)(Arguments...) const volatile&& noexcept> final
        {
            constexpr compl MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer() noexcept = delete;

            explicit consteval MemberFunctionPointer(const MemberFunctionPointer&) noexcept =
            delete;

            explicit consteval MemberFunctionPointer(MemberFunctionPointer&&) noexcept = delete;

            consteval auto operator=(const MemberFunctionPointer&) noexcept ->
            MemberFunctionPointer& = delete;

            consteval auto operator=(MemberFunctionPointer&&) noexcept -> MemberFunctionPointer& =
            delete;

            [[nodiscard]] consteval auto operator==(const MemberFunctionPointer&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const MemberFunctionPointer&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }
    #endif

    /**
     * @brief Satisfied when @p Self is a pointer to a non-static member function.
     */
    template<class Self> concept MemberFunctionPointer =
    #ifdef _MSC_VER
    Detail::MemberFunctionPointer<Self>::Value()
    #else
    __is_member_function_pointer(Self)
    #endif
    ;
}

#endif
#endif