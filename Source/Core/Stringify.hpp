// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_stringify
#define alice_header_guard_core_stringify
#define alice_core_stringify_private_and_secret_do_not_use2(a, b) a##b
#define alice_core_stringify_private_and_secret_do_not_use(prefix, ...) \
alice_core_stringify_private_and_secret_do_not_use2(prefix, #__VA_ARGS__)
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif

/**
 * Stringifies, with the given encoding by @p prefix, the tokens given by @ref ..., into an string
 * literal. For macros, it will first expand, and then stringify the tokens that are left.
 *
 * @param prefix The optional encoding prefix the produced string literal will have. If defined, it
 * can only be one of the following:
 *
 * - L.
 * - u8.
 * - U.
 * - u.
 *
 * @param ... The tokens that the processed string literal representation will contain.
 */
#define $stringify(prefix, ...) alice_core_stringify_private_and_secret_do_not_use(prefix, __VA_ARGS__)

#endif
#endif