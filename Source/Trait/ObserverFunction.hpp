// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_observer_function
#define alice_header_guard_trait_observer_function

namespace Alice::Trait
{
    namespace Detail
    {
        template<class> struct ObserverFunction final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const
        noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const&>
        final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const&
        noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const&&>
        final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const&&
        noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const
        volatile> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const
        volatile noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const
        volatile&> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const
        volatile& noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const
        volatile&&> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class> struct ObserverFunction<Self (Class::*)(...) const
        volatile&& noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const&> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const& noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const&&> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const&& noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const volatile> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const volatile noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const volatile&> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const volatile& noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const volatile&&> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self, class Class, class... Arguments> struct ObserverFunction<Self (Class::
        *)(Arguments...) const volatile&& noexcept> final
        {
            constexpr compl ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction() noexcept = delete;

            explicit consteval ObserverFunction(const ObserverFunction&) noexcept = delete;

            explicit consteval ObserverFunction(ObserverFunction&&) noexcept = delete;

            consteval auto operator=(const ObserverFunction&) noexcept -> ObserverFunction& =
            delete;

            consteval auto operator=(ObserverFunction&&) noexcept -> ObserverFunction& = delete;

            [[nodiscard]] consteval auto operator==(const ObserverFunction&) const noexcept -> bool
            = delete;

            [[nodiscard]] consteval auto operator<=>(const ObserverFunction&) const noexcept =
            delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }

    /**
     * @brief Satisfied when @p Self is a pointer to a non-static member function that cannot
     * modify the non-mutable non-static data members of the class or union.
     */
    template<class Self> concept ObserverFunction = Detail::ObserverFunction<Self>::Value();
}

#endif
#endif