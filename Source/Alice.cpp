// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#include <climits>
#include "Core/Size.hpp"
#include "Core/NullPointer.hpp"

static_assert(CHAR_BIT == 8, "each byte must be 8-bits");
static_assert(alignof(::Alice::Size::Native) == 8uz and sizeof(::Alice::Size::Native) == 8uz,
"the alignment and size of ::Alice::Size::Native must be 8 bytes (padding-exclusive)");

#ifdef alice_windows
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
#else
int main()
#endif
{
    #ifdef alice_windows
    return 0;
    #endif
}

#endif