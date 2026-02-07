// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Meta/RemoveLvalueReference.hpp"

using Alice::Meta::RemoveLvalueReference;

[[nodiscard]] auto lvalue(auto&&) noexcept -> bool
{
    return true;
}

[[nodiscard]] auto lvalue(auto&) noexcept -> bool
{
    return false;
}

[[nodiscard]] auto universal(auto&& x) noexcept -> bool
{
    return lvalue(static_cast<decltype(x)&&>(x));
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    int val = 42;
    int& x = val;
    return universal(42) and not universal(x) and universal(RemoveLvalueReference<decltype(x)>(val));
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