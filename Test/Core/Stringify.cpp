// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Stringify.hpp"

// ─── Minimal string-comparison helper ─────────────

template<class T> [[nodiscard]] constexpr auto str_eq(const T* a, const T* b) noexcept -> bool
{
    for(; *a and *b; ++a, ++b)
        if(*a not_eq *b)
            return false;
    return *a == *b;
}

// ─── Macro used to verify macro-expansion behaviour ──────────────────────────
#define STRINGIFY_TEST_INNER_MACRO inner_value
#define STRINGIFY_TEST_OUTER_MACRO STRINGIFY_TEST_INNER_MACRO

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ═══════════════════════════════════════════════════════════════════════════════
    // 1. No encoding prefix (empty first argument)
    //    $stringify(, ...) must produce a plain "..." string literal.
    // ═══════════════════════════════════════════════════════════════════════════════

    static_assert(str_eq($stringify(, hello), "hello"), "$stringify(,) single identifier");
    static_assert(str_eq($stringify(, hello world), "hello world"),
    "$stringify(,) space-separated tokens");
    static_assert(str_eq($stringify(, ), ""), "$stringify(,) empty variadic → empty string");
    static_assert(str_eq($stringify(, 0), "0"), "$stringify(,) integer literal token");
    static_assert(str_eq($stringify(, 3.14), "3.14"), "$stringify(,) floating-point literal token")
    ;
    static_assert(str_eq($stringify(, +), "+"), "$stringify(,) single operator token");

    // ═══════════════════════════════════════════════════════════════════════════════
    // 2. Comma-separated variadic arguments
    //    The preprocessor preserves commas between __VA_ARGS__ tokens.
    // ═══════════════════════════════════════════════════════════════════════════════

    static_assert(str_eq($stringify(, a, b, c), "a, b, c"),
    "$stringify(,) comma-separated tokens become 'a, b, c'");
    static_assert(str_eq($stringify(, 1, 2, 3), "1, 2, 3"),
    "$stringify(,) comma-separated integers");

    // ═══════════════════════════════════════════════════════════════════════════════
    // 3. UTF-8 prefix  u8  (char8_t in C++20+)
    // ═══════════════════════════════════════════════════════════════════════════════

    static_assert(str_eq($stringify(u8, hello), u8"hello"), "$stringify(u8,) produces u8\"...\"");
    static_assert(str_eq($stringify(u8, foo bar), u8"foo bar"), "$stringify(u8,) with spaces");

    // ═══════════════════════════════════════════════════════════════════════════════
    // 4. UTF-16 prefix  u
    // ═══════════════════════════════════════════════════════════════════════════════

    static_assert(str_eq($stringify(u, hello), u"hello"), "$stringify(u,) produces u\"...\"");
    static_assert(str_eq($stringify(u, foo bar), u"foo bar"), "$stringify(u,) with spaces");

    // ═══════════════════════════════════════════════════════════════════════════════
    // 5. UTF-32 prefix  U
    // ═══════════════════════════════════════════════════════════════════════════════

    static_assert(str_eq($stringify(U, hello), U"hello"), "$stringify(U,) produces U\"...\"");
    static_assert(str_eq($stringify(U, foo bar), U"foo bar"), "$stringify(U,) with spaces");

    // ═══════════════════════════════════════════════════════════════════════════════
    // 6. Macro-expansion semantics
    //    The two-level indirection (secret1 → secret2) forces expansion of any
    //    macro tokens passed as the variadic arguments before stringification.
    // ═══════════════════════════════════════════════════════════════════════════════

    // A directly-expanded macro: INNER → inner_value
    static_assert(str_eq($stringify(, STRINGIFY_TEST_INNER_MACRO), "inner_value"),
    "$stringify expands a single-level macro before stringifying");
    // A doubly-expanded macro: OUTER → INNER → inner_value
    static_assert(str_eq($stringify(, STRINGIFY_TEST_OUTER_MACRO), "inner_value"),
    "$stringify fully expands nested macros before stringifying");

    return str_eq($stringify(, "my_string"), "\"my_string\"");
}

#ifdef alice_windows
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
#else
int main()
#endif
{
    return not alice_test();
}

#endif