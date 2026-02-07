// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Move.hpp"

[[nodiscard]] auto moved(auto&) noexcept -> bool
{
    return false;
}

[[nodiscard]] auto moved(auto&&) noexcept -> bool
{
    return true;
}

[[nodiscard]] auto universal(auto&& x) noexcept -> bool
{
    return moved($move(x));
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    int x = 42;
    return universal(x) and universal(42);
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