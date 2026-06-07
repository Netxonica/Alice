// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_inline
#define alice_header_guard_core_inline

#ifdef _MSC_VER
#define alice_core_inline_private_and_secret_always __forceinline
#define alice_core_inline_private_and_secret_never __declspec(noinline)
#else
#define alice_core_inline_private_and_secret_always [[gnu::always_inline]]
#define alice_core_inline_private_and_secret_never [[gnu::noinline]]
#endif

/**
 * @brief Serves as an inlining specification.
 *
 * @p level The level of the inlining. Only can be: 'always' or 'never'.
 */
#define $inline(level) alice_core_inline_private_and_secret_##level

#endif
#endif