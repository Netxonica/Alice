// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_size
#define alice_header_guard_core_size
#ifdef _MSC_VER
#include <intrin.h>
#endif
#include "Core/Safety.hpp"
#include "Math/Logic/Proposition.hpp"

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
         * @brief Computes the unary plus.
         */
        [[nodiscard]] constexpr auto operator+() const noexcept -> Size
        {
            return Size{m_value};
        }

        /**
         * @brief Computes the pre-increment by 1.
         */
        constexpr auto operator++() noexcept -> Size&
        {
            ++m_value;
            return *this;
        }

        /**
         * @brief Computes the post-increment by 1.
         */
        constexpr auto operator++(int) noexcept -> Size
        {
            return Size{m_value++};
        }

        /**
         * @brief Computes the pre-decrement by 1.
         */
        constexpr auto operator--() noexcept -> Size&
        {
            --m_value;
            return *this;
        }

        /**
         * @brief Computes the post-decrement by 1.
         */
        constexpr auto operator--(int) noexcept -> Size
        {
            return Size{m_value--};
        }

        /**
         * @brief Computes the arithmetic addition and assigment.
         */
        constexpr auto operator+=(const Size rhs) noexcept -> Size&
        {
            m_value += rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the arithmetic addition.
         */
        [[nodiscard]] constexpr auto operator+(const Size rhs) const noexcept -> Size
        {
            return Size{m_value + rhs.m_value};
        }

        /**
         * @brief Computes the arithmetic subtraction and assigment.
         */
        constexpr auto operator-=(const Size rhs) noexcept -> Size&
        {
            m_value -= rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the arithmetic subtraction.
         */
        [[nodiscard]] constexpr auto operator-(const Size rhs) const noexcept -> Size
        {
            return Size{m_value - rhs.m_value};
        }

        /**
         * @brief Computes the arithmetic multiplication and assigment.
         */
        constexpr auto operator*=(const Size rhs) noexcept -> Size&
        {
            m_value *= rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the arithmetic multiplication.
         */
        [[nodiscard]] constexpr auto operator*(const Size rhs) const noexcept -> Size
        {
            return Size{m_value * rhs.m_value};
        }

        /**
         * @brief Computes the arithmetic division and assigment.
         */
        constexpr auto operator/=(const Size rhs) noexcept -> Size&
        {
            m_value /= rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the arithmetic division.
         */
        [[nodiscard]] constexpr auto operator/(const Size rhs) const noexcept -> Size
        {
            return Size{m_value / rhs.m_value};
        }

        /**
         * @brief Computes the arithmetic modulo and assigment.
         */
        constexpr auto operator%=(const Size rhs) noexcept -> Size&
        {
            m_value %= rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the arithmetic modulo.
         */
        [[nodiscard]] constexpr auto operator%(const Size rhs) const noexcept -> Size
        {
            return Size{m_value % rhs.m_value};
        }

        /**
         * @brief Computes the bitwise negation.
         */
        [[nodiscard]] constexpr auto operator compl() const noexcept -> Size
        {
            return Size{compl m_value};
        }

        /**
         * @brief Computes the bitwise conjunction and assignment.
         */
        constexpr auto operator and_eq(const Size rhs) noexcept -> Size&
        {
            m_value and_eq rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the bitwise conjunction.
         */
        [[nodiscard]] constexpr auto operator bitand(const Size rhs) const noexcept -> Size
        {
            return Size{m_value bitand rhs.m_value};
        }

        /**
         * @brief Computes the bitwise disjunction and assignment.
         */
        constexpr auto operator or_eq(const Size rhs) noexcept -> Size&
        {
            m_value or_eq rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the bitwise disjunction.
         */
        [[nodiscard]] constexpr auto operator bitor(const Size rhs) const noexcept -> Size
        {
            return Size{m_value bitor rhs.m_value};
        }

        /**
         * @brief Computes the bitwise exclusive disjunction and assignment.
         */
        constexpr auto operator xor_eq(const Size rhs) noexcept -> Size&
        {
            m_value xor_eq rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the bitwise exclusive disjunction.
         */
        [[nodiscard]] constexpr auto operator xor(const Size rhs) const noexcept -> Size
        {
            return Size{m_value xor rhs.m_value};
        }

        /**
         * @brief Computes the bitwise left shift and assignment.
         */
        constexpr auto operator<<=(const Size rhs) noexcept -> Size&
        {
            m_value <<= rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the bitwise left shift.
         */
        [[nodiscard]] constexpr auto operator<<(const Size rhs) const noexcept -> Size
        {
            return Size{m_value << rhs.m_value};
        }

        /**
         * @brief Computes the bitwise right shift and assignment.
         */
        constexpr auto operator>>=(const Size rhs) noexcept -> Size&
        {
            m_value >>= rhs.m_value;
            return *this;
        }

        /**
         * @brief Computes the bitwise right shift.
         */
        [[nodiscard]] constexpr auto operator>>(const Size rhs) const noexcept -> Size
        {
            return Size{m_value >> rhs.m_value};
        }

        /**
         * @brief Computes the less-than comparison.
         */
        [[nodiscard]] constexpr auto operator<(const Size rhs) const noexcept -> Math::Logic::
        Proposition
        {
            return m_value < rhs.m_value ? Math::Logic::Proposition::Tautology() : Math::Logic::
            Proposition::Contradiction();
        }

        /**
         * @brief Computes the less-than-or-equal-to comparison.
         */
        [[nodiscard]] constexpr auto operator<=(const Size rhs) const noexcept -> Math::Logic::
        Proposition
        {
            return m_value <= rhs.m_value ? Math::Logic::Proposition::Tautology() : Math::Logic::
            Proposition::Contradiction();
        }

        /**
         * @brief Computes the greater-than comparison.
         */
        [[nodiscard]] constexpr auto operator>(const Size rhs) const noexcept -> Math::Logic::
        Proposition
        {
            return m_value > rhs.m_value ? Math::Logic::Proposition::Tautology() : Math::Logic::
            Proposition::Contradiction();
        }

        /**
         * @brief Computes the greater-than-or-equal-to comparison.
         */
        [[nodiscard]] constexpr auto operator>=(const Size rhs) const noexcept -> Math::Logic::
        Proposition
        {
            return m_value >= rhs.m_value ? Math::Logic::Proposition::Tautology() : Math::Logic::
            Proposition::Contradiction();
        }

        /**
         * @brief Computes the equality comparison.
         */
        [[nodiscard]] constexpr auto operator==(const Size rhs) const noexcept -> Math::Logic::
        Proposition
        {
            return m_value == rhs.m_value ? Math::Logic::Proposition::Tautology() : Math::Logic::
            Proposition::Contradiction();
        }

        /**
         * @brief Computes the inequality comparison.
         */
        [[nodiscard]] constexpr auto operator not_eq(const Size rhs) const noexcept -> Math::Logic
        ::Proposition
        {
            return m_value not_eq rhs.m_value ? Math::Logic::Proposition::Tautology() : Math::Logic
            ::Proposition::Contradiction();
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
            return Size{18'446'744'073'709'551'615uz};
        }

        /**
         * @brief The size of this integer type in bits.
         */
        [[nodiscard]] static consteval auto Bits() noexcept -> Size
        {
            return Size{64uz};
        }

        /**
         * @brief The maximum number of digits of this integer type in decimal base.
         */
        [[nodiscard]] static consteval auto Digits() noexcept -> Size
        {
            return Size{20uz};
        }

        /**
         * @brief Computes the number of ones in the binary representation of this instance.
         */
        [[nodiscard]] constexpr auto Ones() const noexcept -> Size
        {
            #ifdef _MSC_VER
            if consteval
            {
                Native count = 0uz;
                for(Native bit = 0uz; bit < 64uz; ++bit)
                    if((m_value >> bit) bitand 1uz)
                        ++count;
                return Size{count};
            }
            else
            {
                return Size{__popcnt64(m_value)};
            }
            #else
            return Size{static_cast<Native>(__builtin_popcountg(m_value))};
            #endif
        }

        /**
         * @brief Computes the number of zeros in the binary representation of this instance.
         */
        [[nodiscard]] constexpr auto Zeros() const noexcept -> Size
        {
            #ifdef _MSC_VER
            if consteval
            {
                Native count = 0uz;
                for(Native bit = 0uz; bit < 64uz; ++bit)
                    if(not((m_value >> bit) bitand 1uz))
                        ++count;
                return Size{count};
            }
            else
            {
                return Size{__popcnt64(compl m_value)};
            }
            #else
            return Size{static_cast<Native>(__builtin_popcountg(compl m_value))};
            #endif
        }

        /**
         * @brief Computes the number of leading ones in the binary representation of this
         * instance.
         */
        [[nodiscard]] constexpr auto LeadingOnes() const noexcept -> Size
        {
            #ifdef _MSC_VER
            if consteval
            {
                if(m_value == 18'446'744'073'709'551'615uz)
                    return Size{64uz};
                Native count = 0uz;
                for(Native bit = 63uz; (m_value >> bit) bitand 1uz; --bit)
                    ++count;
                return Size{count};
            }
            else
            {
                return Size{__lzcnt64(compl m_value)};
            }
            #else
            return Size{static_cast<Native>(__builtin_clzg(compl m_value, 64))};
            #endif
        }

        /**
         * @brief Computes the number of leading zeros in the binary representation of this
         * instance.
         */
        [[nodiscard]] constexpr auto LeadingZeros() const noexcept -> Size
        {
            #ifdef _MSC_VER
            if consteval
            {
                if(m_value == 0uz)
                    return Size{64uz};
                Native count = 0uz;
                for(Native bit = 63uz; not((m_value >> bit) bitand 1uz); --bit)
                    ++count;
                return Size{count};
            }
            else
            {
                return Size{__lzcnt64(m_value)};
            }
            #else
            return Size{static_cast<Native>(__builtin_clzg(m_value, 64))};
            #endif
        }

        /**
         * @brief Computes the number of trailing ones in the binary representation of this
         * instance.
         */
        [[nodiscard]] constexpr auto TrailingOnes() const noexcept -> Size
        {
            #ifdef _MSC_VER
            if consteval
            {
                Native count = 0uz;
                for(Native bit = 0uz; bit < 64uz and (m_value >> bit) bitand 1uz; ++bit)
                    ++count;
                return Size{count};
            }
            else
            {
                return Size{_tzcnt_u64(compl m_value)};
            }
            #else
            return Size{static_cast<Native>(__builtin_ctzg(compl m_value, 64))};
            #endif
        }

        /**
         * @brief Computes the number of trailing zeros in the binary representation of this
         * instance.
         */
        [[nodiscard]] constexpr auto TrailingZeros() const noexcept -> Size
        {
            #ifdef _MSC_VER
            if consteval
            {
                Native count = 0uz;
                for(Native bit = 0uz; bit < 64uz and not((m_value >> bit) bitand 1uz); ++bit)
                    ++count;
                return Size{count};
            }
            else
            {
                return Size{_tzcnt_u64(m_value)};
            }
            #else
            return Size{static_cast<Native>(__builtin_ctzg(m_value, 64))};
            #endif
        }

        /**
         * @brief Computes the minimum number of bits required to represent this instance.
         */
        [[nodiscard]] constexpr auto BitWidth() const noexcept -> Size
        {
            return Bits() - LeadingZeros();
        }

        /**
         * @brief Computes this instance with only the most significant bit set.
         */
        [[nodiscard]] constexpr auto IsolateHighestOne() const noexcept -> Size
        {
            #ifdef _MSC_VER
            if consteval
            {
                if(m_value == 0uz)
                    return Size{};
                Native counter = 0uz;
                while(not static_cast<bool>(m_value >> static_cast<Native>(63uz - counter)))
                    ++counter;
                return Size{1uz << static_cast<Native>(63uz - counter)};
            }
            else
            {
                return Size{1uz << static_cast<Native>(63 - __lzcnt64(m_value))};
            }
            #else
            return Size{1uz << static_cast<Native>(63 - __builtin_clzg(m_value))};
            #endif
        }
    };

    namespace Literals
    {
        /**
         * @brief The UDL constructing a @ref Size from a literal.
         */
        [[nodiscard]] consteval auto operator""_size(const unsigned long long value) noexcept ->
        Size
        {
            return Size{static_cast<Size::Native>(value)};
        }
    }
}

#endif
#endif