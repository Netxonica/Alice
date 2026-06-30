// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_inline
#define alice_header_guard_core_inline

#ifdef _MSC_VER
#define alice_core_inline_private_and_secret_always [[msvc::forceinline]] inline
#define alice_core_inline_private_and_secret_never [[msvc::noinline]] inline
#else
#define alice_core_inline_private_and_secret_always [[gnu::always_inline]] inline
#define alice_core_inline_private_and_secret_never [[gnu::noinline]] inline
#endif
#define alice_core_inline_private_and_secret_ inline

/**
 * @brief Serves as an inlining specification.
 *
 * @p level The level of the inlining, or basic 'inline' if it's not specified. If specified, it
 * only can be: 'always' or 'never'.
 */
#define $inline(level) alice_core_inline_private_and_secret_##level

#endif
#endif