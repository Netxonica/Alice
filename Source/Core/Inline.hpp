// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_inline
#define alice_header_guard_core_inline
#ifdef _MSC_VER
#define alice_core_inline_private_and_secret_do_not_use_always [[msvc::forceinline]] inline
#define alice_core_inline_private_and_secret_do_not_use_never [[msvc::noinline]] inline
#else
#define alice_core_inline_private_and_secret_do_not_use_always [[gnu::always_inline]] inline
#define alice_core_inline_private_and_secret_do_not_use_never [[gnu::noinline]] inline
#endif
#define alice_core_inline_private_and_secret_do_not_use_ inline
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif

/**
 * Serves as an inline hinting, with @p level indicating the semantic of the hint, or a plain
 * @c inline in case @p level is omitted.
 *
 * @param level The optional inline level of the hint. If defined, it can only be one of the
 * following:
 *
 * - never.
 * - always.
 */
#define $inline(level) alice_core_inline_private_and_secret_do_not_use_##level

#endif
#endif