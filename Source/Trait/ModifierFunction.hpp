// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_modifier_function
#define alice_header_guard_trait_modifier_function

namespace Alice::Trait
{
    namespace Detail
    {
        template<class> struct ModifierFunction final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...)> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) noexcept>
        final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) &> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) & noexcept>
        final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) &&> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) && noexcept>
        final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) volatile>
        final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) volatile
        noexcept> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) volatile&>
        final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) volatile&
        noexcept> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) volatile&&>
        final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ModifierFunction<Self (Class::*)(...) volatile&&
        noexcept> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...)> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) noexcept> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) &> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) & noexcept> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) &&> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) && noexcept> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) volatile> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) volatile noexcept> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) volatile&> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) volatile& noexcept> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) volatile&&> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ModifierFunction<Self (Class::
        *)(Arguments...) volatile&& noexcept> final
        {
            constexpr compl ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction() noexcept = delete;

            explicit consteval ModifierFunction(const ModifierFunction&) noexcept = delete;

            explicit consteval ModifierFunction(ModifierFunction&&) noexcept = delete;

            consteval auto operator=(const ModifierFunction&) noexcept -> ModifierFunction& =
            delete;

            consteval auto operator=(ModifierFunction&&) noexcept -> ModifierFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ModifierFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ModifierFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }

    /**
     * @brief Satisfied when @p Self is a pointer to a non-static member function that can modify
     * the non-mutable non-static data members of the class or union.
     */
    template<class Self> concept ModifierFunction = Detail::ModifierFunction<Self>::Value();
}

#endif
#endif