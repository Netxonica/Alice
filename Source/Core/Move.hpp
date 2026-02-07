// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_move
#define alice_header_guard_core_move
#include "Meta/RemoveLvalueReference.hpp"

#define $move(...) static_cast<::Alice::Meta::RemoveLvalueReference<decltype(__VA_ARGS__)>&&>(\
__VA_ARGS__)

#endif
#endif