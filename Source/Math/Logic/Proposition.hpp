// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_math_logic_proposition
#define alice_header_guard_math_logic_proposition
#include "Core/Safety.hpp"

namespace Alice::Math::Logic
{
    /**
     * @brief A classical propositional logic type.
     */
    struct [[nodiscard]] Proposition
    {
        /**
         * @brief The native type representing the underlying type of this class. It's useful for
         * interacting with C.
         */
        using Native = bool;
    private:
        Native m_value;

        explicit constexpr Proposition(const bool value) noexcept : m_value(value){}
    public:
        /**
         * @brief The trivial destructor.
         */
        constexpr compl Proposition() noexcept = default;

        explicit consteval Proposition() noexcept = delete;

        /**
         * @brief The trivial copy constructor.
         */
        constexpr Proposition(const Proposition& other) noexcept = default;

        /**
         * @brief The trivial move constructor.
         */
        constexpr Proposition(Proposition&& other) noexcept = default;

        consteval auto operator=(const Proposition&) noexcept -> Proposition& = delete(
        #ifndef _MSC_VER
        "CPL doesn't define assignment operations"
        #endif
        );

        consteval auto operator=(Proposition&&) noexcept -> Proposition& = delete(
        #ifndef _MSC_VER
        "CPL doesn't define assignment operations"
        #endif
        );

        [[nodiscard]] consteval auto operator not_eq(const Proposition&) const noexcept -> bool =
        delete;

        [[nodiscard]] consteval auto operator<=>(const Proposition&) const noexcept = delete;

        /**
         * @brief The explicit conversion operator to @ref Native.
         */
        [[nodiscard]] explicit constexpr operator Native() const noexcept
        {
            return m_value;
        }

        /**
         * @brief Computes the contradiction, which is always false.
         */
        [[nodiscard]] static consteval auto Contradiction() noexcept -> Proposition
        {
            return Proposition{false};
        }

        /**
         * @brief Computes the tautology, which is always true.
         */
        [[nodiscard]] static consteval auto Tautology() noexcept -> Proposition
        {
            return Proposition{true};
        }

        /**
         * @brief Computes the unary negation.
         */
        [[nodiscard]] constexpr auto operator not() const noexcept -> Proposition
        {
            return Proposition{not m_value};
        }

        /**
         * @brief Computes the binary conjunction.
         */
        [[nodiscard]] constexpr auto operator and(const Proposition rhs) const noexcept ->
        Proposition
        {
            return Proposition{m_value and rhs.m_value};
        }

        /**
         * @brief Computes the binary disjunction.
         */
        [[nodiscard]] constexpr auto operator or(const Proposition rhs) const noexcept ->
        Proposition
        {
            return Proposition{m_value or rhs.m_value};
        }

        /**
         * @brief Computes the binary material implication.
         */
        [[nodiscard]] constexpr auto Implies(const Proposition rhs) const noexcept -> Proposition
        {
            return Proposition{not m_value or rhs.m_value};
        }

        /**
         * @brief Computes the binary conditional.
         */
        [[nodiscard]] constexpr auto operator==(const Proposition rhs) const noexcept ->
        Proposition
        {
            return Proposition{m_value == rhs.m_value};
        }
    };
}

#endif
#endif