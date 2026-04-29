// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_size
#define alice_header_guard_core_size
#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace Alice
{
    /**
     * @brief The pointer-sized unsigned integer type.
     */
    struct [[nodiscard]] Size
    {
        /**
         * @brief The native type underlying to this type, useful for interacting with C.
         */
        using Native = decltype(sizeof(bool));
    private:
        Native m_value;
    public:
        /**
         * @brief Trivial destructor.
         */
        constexpr compl Size() noexcept = default;

        /**
         * @brief Zero-initialization default constructor.
         */
        explicit constexpr Size() noexcept : m_value(0uz){}

        /**
         * @brief Trivial copy constructor.
         */
        constexpr Size(const Size& other) noexcept = default;

        /**
         * @brief Trivial move constructor.
         */
        constexpr Size(Size&& other) noexcept = default;

        /**
         * @brief Trivial copy assignment.
         */
        constexpr auto operator=(const Size& rhs) noexcept -> Size& = default;

        /**
         * @brief Trivial move assignment.
         */
        constexpr auto operator=(Size&& rhs) noexcept -> Size& = default;

        [[nodiscard]] consteval auto operator==(const Size&) const noexcept -> bool = delete;

        [[nodiscard]] consteval auto operator<=>(const Size&) const noexcept = delete;

        /**
         * @brief @ref Native constructor.
         */
        explicit constexpr Size(const Native value) noexcept : m_value(value){}

        /**
         * @brief @ref Native assignment.
         */
        constexpr auto operator=(const Native value) noexcept -> Size&
        {
            m_value = value;
            return *this;
        }

        /**
         * @brief Cast to @ref Native.
         */
        [[nodiscard]] explicit constexpr operator Native() const noexcept
        {
            return m_value;
        }

        /**
         * @brief The smallest value that can be represented by this type.
         */
        [[nodiscard]] static consteval auto Minimum() noexcept -> Size
        {
            return Size{};
        }

        /**
         * @brief The largest value that can be represented by this type.
         */
        [[nodiscard]] static consteval auto Maximum() noexcept -> Size
        {
            return Size{18446744073709551615uz};
        }

        /**
         * @brief Computes the bitwise NOT of @ref this.
         */
        [[nodiscard]] constexpr auto operator compl() const noexcept -> Size
        {
            return Size{compl m_value};
        }

        /**
         * @brief Computes the bitwise AND of @ref this and @ref rhs.
         */
        [[nodiscard]] constexpr auto operator bitand(const Size rhs) const noexcept -> Size
        {
            return Size{m_value bitand rhs.m_value};
        }

        /**
         * @brief Computes the bitwise OR of @ref this and @ref rhs.
         */
        [[nodiscard]] constexpr auto operator bitor(const Size rhs) const noexcept -> Size
        {
            return Size{m_value bitor rhs.m_value};
        }

        /**
         * @brief Computes the bitwise XOR of @ref this and @ref rhs.
         */
        [[nodiscard]] constexpr auto operator xor(const Size rhs) const noexcept -> Size
        {
            return Size{m_value xor rhs.m_value};
        }

        /**
         * @brief Computes the self-assigning bitwise AND of @ref this and @ref rhs.
         */
        constexpr auto operator and_eq(const Size rhs) noexcept -> void
        {
            m_value and_eq rhs.m_value;
        }

        /**
         * @brief Computes the self-assigning bitwise OR of @ref this and @ref rhs.
         */
        constexpr auto operator or_eq(const Size rhs) noexcept -> void
        {
            m_value or_eq rhs.m_value;
        }

        /**
         * @brief Computes the self-assigning bitwise XOR of @ref this and @ref rhs.
         */
        constexpr auto operator xor_eq(const Size rhs) noexcept -> void
        {
            m_value xor_eq rhs.m_value;
        }

        /**
         * @brief Computes the arithmetic unary plus of @ref this.
         */
        [[nodiscard]] constexpr auto operator+() const noexcept -> Size
        {
            return *this;
        }

        /**
         * @brief Computes the arithmetic pre-increment by 1 of @ref this.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        constexpr auto operator++() noexcept -> void
        {
            ++m_value;
        }

        /**
         * @brief Computes the arithmetic post-increment by 1 of @ref this.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        constexpr auto operator++(int) noexcept -> Size
        {
            return Size{m_value++};
        }

        /**
         * @brief Computes the arithmetic pre-decrement by 1 of @ref this.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        constexpr auto operator--() noexcept -> void
        {
            --m_value;
        }

        /**
         * @brief Computes the arithmetic post-decrement by 1 of @ref this.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        constexpr auto operator--(int) noexcept -> Size
        {
            return Size{m_value--};
        }

        /**
         * @brief Computes the arithmetic addition of @ref this and @ref rhs.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        [[nodiscard]] constexpr auto operator+(const Size rhs) const noexcept -> Size
        {
            return Size{m_value + rhs.m_value};
        }

        /**
         * @brief Computes the self-assigning arithmetic addition of @ref this and @ref rhs.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        constexpr auto operator+=(const Size rhs) noexcept -> void
        {
            m_value += rhs.m_value;
        }

        /**
         * @brief Computes the arithmetic subtraction of @ref this and @ref rhs.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        [[nodiscard]] constexpr auto operator-(const Size rhs) const noexcept -> Size
        {
            return Size{m_value - rhs.m_value};
        }

        /**
         * @brief Computes the self-assigning arithmetic subtraction of @ref this and @ref rhs.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        constexpr auto operator-=(const Size rhs) noexcept -> void
        {
            m_value -= rhs.m_value;
        }

        /**
         * @brief Computes the arithmetic multiplication of @ref this and @ref rhs.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        [[nodiscard]] constexpr auto operator*(const Size rhs) const noexcept -> Size
        {
            return Size{m_value * rhs.m_value};
        }

        /**
         * @brief Computes the self-assigning arithmetic multiplication of @ref this and @ref rhs.
         *
         * It's naturally unsafe because the result can be a wraparound.
         */
        constexpr auto operator*=(const Size rhs) noexcept -> void
        {
            m_value *= rhs.m_value;
        }

        /**
         * @brief Computes the arithmetic division of @ref this and @ref rhs.
         *
         * It's naturally unsafe because:
         *
         * - The result can be a truncation.
         * - If @ref rhs is 0, it is undefined behavior.
         */
        [[nodiscard]] constexpr auto operator/(const Size rhs) const noexcept -> Size
        {
            return Size{m_value / rhs.m_value};
        }

        /**
         * @brief Computes the self-assigning arithmetic division of @ref this and @ref rhs.
         *
         * It's naturally unsafe because:
         *
         * - The result can be a truncation.
         * - If @ref rhs is 0, it is undefined behavior.
         */
        constexpr auto operator/=(const Size rhs) noexcept -> void
        {
            m_value /= rhs.m_value;
        }

        /**
         * @brief Computes the arithmetic modulo of @ref this and @ref rhs.
         *
         * It's naturally unsafe because if @ref rhs is 0, it is undefined behavior.
         */
        [[nodiscard]] constexpr auto operator%(const Size rhs) const noexcept -> Size
        {
            return Size{m_value % rhs.m_value};
        }

        /**
         * @brief Computes the self-assigning arithmetic modulo of @ref this and @ref rhs.
         *
         * It's naturally unsafe because if @ref rhs is 0, it is undefined behavior.
         */
        constexpr auto operator%=(const Size rhs) noexcept -> void
        {
            m_value %= rhs.m_value;
        }

        /**
         * @brief Computes @ref this with only the most significant bit set, or 0 if the input is
         * 0.
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
            #endif
            return Size{m_value == 0uz ? 0uz : 1uz << static_cast<Native>(63uz - static_cast<Native
            >(
            #ifdef _MSC_VER
            __lzcnt64
            #else
            __builtin_clzg
            #endif
            (m_value)))};
        }

        /**
         * @brief Computes @ref this with only the least significant bit set, or 0 if the input is
         * 0.
         */
        [[nodiscard]] constexpr auto IsolateLowestOne() const noexcept -> Size
        {
            #ifdef _MSC_VER
            if(m_value == 0uz)
                return Size{};
            if consteval
            {
                Native counter = 0uz;
                while(not static_cast<bool>(m_value << static_cast<Native>(63uz - counter) >> 63uz)
                )
                    ++counter;
                return Size{
                0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000 >>
                static_cast<Native>(63uz - counter)};
            }
            unsigned long index;
            _BitScanReverse64(&index, m_value);
            return Size{index};
            #else
            return Size{m_value == 0uz ? 0uz :
            0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000 >>
            static_cast<Native>(63uz - static_cast<Native>(__builtin_ctzg(m_value)))};
            #endif
        }

        /**
         * @brief Computes the reversed byte order.
         */
        [[nodiscard]] constexpr auto SwapBytes() const noexcept -> Size
        {
            return Size{
            #ifdef _MSC_VER
            _byteswap_uint64
            #else
            __builtin_bswap64
            #endif
            (m_value)
            };
        }
    };

    namespace Literals
    {
        /**
         * @brief @ref Size UDL.
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