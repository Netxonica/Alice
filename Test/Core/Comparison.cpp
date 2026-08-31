// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Comparison.hpp"

using Alice::Comparison;
using enum Comparison;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    struct Fanum
    {
        int x;

        Comparison operator<=>(Fanum rhs)
        {
            return x < rhs.x ? Less : x == rhs.x ? Equal : Greater;
        }
    };

    Fanum skibidi{42}, nocap{67};
    if(skibidi <=> nocap not_eq Less)
        return false;

    skibidi.x = 100;
    if(skibidi <=> nocap not_eq Greater)
        return false;

    skibidi.x = 67;
    if(skibidi <=> nocap not_eq Equal)
        return false;

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