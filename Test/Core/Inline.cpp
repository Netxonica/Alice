// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Inline.hpp"

$inline() void foo(){}

$inline(never) void bar(){}

$inline(always) void quz(){}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    foo();
    bar();
    quz();

    return true;
}

#ifdef alice_windows
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
#else
int main()
#endif
{
    return not alice_test();
}

#endif