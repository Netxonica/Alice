// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_stringify
#define alice_header_guard_core_stringify

#define alice_private_and_secret_concatenate_helper(a, b) a##b
#define alice_private_and_secret_concatenate(prefix, ...) \
alice_private_and_secret_concatenate_helper(prefix, #__VA_ARGS__)
#define $stringify(prefix, ...) alice_private_and_secret_concatenate(prefix, __VA_ARGS__)

#endif
#endif