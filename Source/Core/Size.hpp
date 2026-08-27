// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_size
#define alice_header_guard_core_size
#include "Core/Inline.hpp"
#include "Core/Safety.hpp"

namespace Alice
{
    /**
     * @brief The pointer-sized unsigned integer type.
     */
    struct [[nodiscard]] Size
    {
        /**
         * @brief The native type representing the underlying type of this class. It's useful for
         * interacting with C.
         */
        using Native = decltype(sizeof(bool));
    private:
        Native m_value;
    public:
        /**
         * @brief The trivial destructor.
         */
        constexpr compl Size() noexcept = default;

        /**
         * @brief The zero-initialization default constructor.
         */
        explicit constexpr Size() noexcept : m_value(0uz){}

        /**
         * @brief The uninitialized unsafe default constructor.
         */
        explicit constexpr Size $unreliable() noexcept{}

        /**
         * @brief The trivial copy constructor.
         */
        constexpr Size(const Size& other) noexcept = default;

        /**
         * @brief The trivial move constructor.
         */
        constexpr Size(Size&& other) noexcept = default;

        /**
         * @brief The trivial copy assignment operator.
         */
        constexpr auto operator=(const Size& rhs) noexcept -> Size& = default;

        /**
         * @brief The trivial move assignment operator.
         */
        constexpr auto operator=(Size&& rhs) noexcept -> Size& = default;

        /**
         * @brief The @ref Native constructor.
         */
        explicit constexpr Size(const Native value) noexcept : m_value(value){}

        /**
         * @brief The @ref Native assignment operator.
         */
        constexpr auto operator=(const Native value) noexcept -> Size&
        {
            m_value = value;
            return *this;
        }

        /**
         * @brief The explicit conversion operator to @ref Native.
         */
        [[nodiscard]] explicit constexpr operator Native() const noexcept
        {
            return m_value;
        }

        /**
         * @brief The smallest value that can be represented.
         */
        [[nodiscard]] static consteval auto Minimum() noexcept -> Size
        {
            return Size{0uz};
        }

        /**
         * @brief The biggest value that can be represented.
         */
        [[nodiscard]] static consteval auto Maximum() noexcept -> Size
        {
            return Size{18446744073709551615uz};
        }

        /**
         * @brief The size of this integer type in bits.
         */
        [[nodiscard]] static consteval auto Bits() noexcept -> Size
        {
            return Size{64uz};
        }
    };
}

#endif
#endif