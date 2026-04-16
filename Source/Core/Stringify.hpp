// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_stringify
#define alice_header_guard_core_stringify

#define alice_core_stringify_private_and_secret2(a, b) a##b

#define alice_core_stringify_private_and_secret1(prefix, ...) \
alice_core_stringify_private_and_secret2(prefix, #__VA_ARGS__)

/**
 * @brief Stringifies the given tokens into an string literal, with the given encoding @p prefix.
 * For macros, it will first expand, and then stringify the tokens that are left.
 */
#define $stringify(prefix, ...) alice_core_stringify_private_and_secret1(prefix, __VA_ARGS__)

#endif
#endif