// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_safety
#define alice_header_guard_core_safety

namespace Alice::Detail
{
    template<bool safety = true> struct [[nodiscard]] Safety final
    {
        constexpr compl Safety() noexcept = default;

        explicit consteval Safety() noexcept = default;

        consteval Safety(const Safety&) noexcept = default;

        explicit consteval Safety(Safety&&) noexcept = delete;

        consteval auto operator=(const Safety&) noexcept -> Safety& = delete;

        consteval auto operator=(Safety&&) noexcept -> Safety& = delete;

        [[nodiscard]] consteval auto operator==(const Safety&) const noexcept -> bool = delete;

        [[nodiscard]] consteval auto operator<=>(const Safety&) const noexcept = delete;

        [[nodiscard]] explicit consteval operator bool() const noexcept
        {
            return true;
        }
    };

    template<> struct [[nodiscard]] Safety<false> final
    {
        constexpr compl Safety() noexcept = default;

        explicit consteval Safety() noexcept = default;

        consteval Safety(const Safety&) noexcept = default;

        explicit consteval Safety(Safety&&) noexcept = delete;

        consteval auto operator=(const Safety&) noexcept -> Safety& = delete;

        consteval auto operator=(Safety&&) noexcept -> Safety& = delete;

        [[nodiscard]] consteval auto operator==(const Safety&) const noexcept -> bool = delete;

        [[nodiscard]] consteval auto operator<=>(const Safety&) const noexcept = delete;

        consteval Safety(const Safety<>&) noexcept = delete(
        "\ncall to unreliable function requires unsafe block");

        [[nodiscard]] explicit consteval operator bool() const noexcept
        {
            return false;
        }
    };

    namespace Internal
    {
        template<class> struct [[nodiscard]] Unsafe final
        {
            constexpr compl Unsafe() noexcept = delete;

            explicit consteval Unsafe() noexcept = delete;

            explicit consteval Unsafe(const Unsafe&) noexcept = delete;

            explicit consteval Unsafe(Unsafe&&) noexcept = delete;

            consteval auto operator=(const Unsafe&) noexcept -> Unsafe& = delete;

            consteval auto operator=(Unsafe&&) noexcept -> Unsafe& = delete;

            [[nodiscard]] consteval auto operator==(const Unsafe&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Unsafe&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<bool safety> struct [[nodiscard]] Unsafe<Safety<safety>> final
        {
            constexpr compl Unsafe() noexcept = delete;

            explicit consteval Unsafe() noexcept = delete;

            explicit consteval Unsafe(const Unsafe&) noexcept = delete;

            explicit consteval Unsafe(Unsafe&&) noexcept = delete;

            consteval auto operator=(const Unsafe&) noexcept -> Unsafe& = delete;

            consteval auto operator=(Unsafe&&) noexcept -> Unsafe& = delete;

            [[nodiscard]] consteval auto operator==(const Unsafe&) const noexcept -> bool = delete;

            [[nodiscard]] consteval auto operator<=>(const Unsafe&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                static_assert(not safety, "\ncall to unreliable function requires unsafe block");
                return true;
            }
        };
    }

    template <class Self> concept Unsafe = Internal::Unsafe<Self>::Value();
}

inline const constexpr ::Alice::Detail::Safety<> alice_safety_object_private_and_secret_do_not_use;

/**
 * @brief Determines whether the current safety context is safe or unsafe.
 */
#define $safety static_cast<bool>(alice_safety_object_private_and_secret_do_not_use)

/**
 * @brief Propagates the current safety context to a template parameter list, with the optional
 * arguments given by @p ...
 */
#define $template(...) <alice_safety_object_private_and_secret_do_not_use __VA_OPT__(,) \
__VA_ARGS__>

/**
 * @brief Propagates the current safety context to a list initialization, with the optional
 * arguments given by @p ...
 */
#define $list(...) {alice_safety_object_private_and_secret_do_not_use __VA_OPT__(,) __VA_ARGS__}

/**
 * @brief Propagates the current safety context to a subscript expression, with the optional
 * arguments given by @p ...
 */
#define $subscript(...) [alice_safety_object_private_and_secret_do_not_use __VA_OPT__(,) \
__VA_ARGS__]

/**
 * @brief Propagates the current safety context to a lambda capture, with the optional arguments
 * given by @p ...
 */
#define $capture(...) [alice_safety_object_private_and_secret_do_not_use __VA_OPT__(,) \
__VA_ARGS__]

/**
 * @brief Propagates the current safety context to a function call, with the optional arguments
 * given by @p ...
 */
#define $function(...) (alice_safety_object_private_and_secret_do_not_use __VA_OPT__(,) \
__VA_ARGS__)

/**
 * @brief Declares a templated entity as an unsafe context, with the optional arguments given by
 * @p ...
 */
#define $template_unreliable(...) template<::Alice::Detail::Unsafe auto \
alice_safety_object_private_and_secret_do_not_use [[maybe_unused]] __VA_OPT__(,) __VA_ARGS__>

/**
 * @brief Declares a requires, function, operator, or constructor, as an unsafe context, with the
 * optional arguments given by @p ...
 */
#define $unreliable(...) ([[maybe_unused]] const ::Alice::Detail::Safety<false> \
alice_safety_object_private_and_secret_do_not_use __VA_OPT__(,) __VA_ARGS__)

/**
 * @brief Creates a safe context. Calls to unsafe entities are illegal within this context.
 */
#define $safe if constexpr([[maybe_unused]] const constexpr ::Alice::Detail::Safety<> \
alice_safety_object_private_and_secret_do_not_use; true)

/**
 * @brief Creates an unsafe context. Calls to safe and unsafe entities are legal within this
 * context.
 */
#define $unsafe if constexpr([[maybe_unused]] const constexpr ::Alice::Detail::Safety<false> \
alice_safety_object_private_and_secret_do_not_use; true)

#endif
#endif