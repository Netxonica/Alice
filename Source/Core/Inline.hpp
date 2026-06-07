// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_inline
#define alice_header_guard_core_inline

#ifdef _MSC_VER
#define alice_core_inline_private_and_secret_balways __forceinline
#define alice_core_inline_private_and_secret_bnever __declspec(noinline) inline
#else
#define alice_core_inline_private_and_secret_balways [[gnu::always_inline]] inline
#define alice_core_inline_private_and_secret_bnever [[gnu::noinline]] inline
#endif
#define alice_core_inline_private_and_secret_b inline

/**
 * @brief Serves as an inlining specification.
 *
 * @p ... The level of the inlining, or basic 'inline' if it's not specified. If specified, it only
 * can be: 'always' or 'never'.
 */
#define $inline(...) alice_core_inline_private_and_secret_b##__VA_ARGS__

#endif
#endif