// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Operator/OrAssignment.hpp"

using Alice::Operator::OrAssignment;
using Alice::Operator::ReturnOrAssignment;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    
    struct Incomplete;
    return not OrAssignment<Incomplete, Incomplete> and not ReturnOrAssignment<Incomplete,
    Incomplete>;
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