// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_forward
#define alice_header_guard_core_forward

#define $forward(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)

#endif
#endif