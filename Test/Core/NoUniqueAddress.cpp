// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/NoUniqueAddress.hpp"

struct Empty{};

struct Foo
{
    Empty e;

    int x;
};

struct Bar
{
    [[$no_unique_address]] Empty e;

    int x;
};

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Empty is an EBO but it isn't optimized away because we don't use no_unique_address

    static_assert(sizeof(Foo) == 8uz);

    // Empty is an EBO and it is optimized away because we use no_unique_address

    static_assert(sizeof(Bar) not_eq 8uz);

    return sizeof(Bar) == 4uz;
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