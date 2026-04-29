// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Size.hpp"

using Alice::Size;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    using namespace Alice::Literals;

    static_assert(static_cast<Size::Native>(42_size) == 42uz);

    Size size;
    if(static_cast<Size::Native>(size) not_eq 0uz)
        return false;

    Size csize{size};
    if(static_cast<Size::Native>(csize) not_eq 0uz)
        return false;

    Size msize{42_size};
    if(static_cast<Size::Native>(msize) not_eq 42uz)
        return false;

    Size nsize{42uz};
    if(static_cast<Size::Native>(nsize) not_eq 42uz)
        return false;

    size = 42uz;
    if(static_cast<Size::Native>(size) not_eq 42uz)
        return false;

    if(static_cast<Size::Native>(Size::Minimum()) not_eq 0uz)
        return false;

    if(static_cast<Size::Native>(Size::Maximum()) not_eq 18446744073709551615uz)
        return false;

    size = 42uz;
    if(static_cast<Size::Native>(compl size) not_eq 18446744073709551573uz)
        return false;

    if(static_cast<Size::Native>(size bitand 10_size) not_eq 10uz)
        return false;

    if(static_cast<Size::Native>(size bitor 10_size) not_eq 42uz)
        return false;

    if(static_cast<Size::Native>(size xor 10_size) not_eq 32uz)
        return false;

    size and_eq 10_size;
    if(static_cast<Size::Native>(size) not_eq 10uz)
        return false;

    size = 42uz;
    size or_eq 10_size;
    if(static_cast<Size::Native>(size) not_eq 42uz)
        return false;

    size = 42uz;
    size xor_eq 10_size;
    if(static_cast<Size::Native>(size) not_eq 32uz)
        return false;

    size = 42uz;
    if(static_cast<Size::Native>(+size) not_eq 42uz)
        return false;

    ++size;
    if(static_cast<Size::Native>(size) not_eq 43uz)
        return false;

    if(static_cast<Size::Native>(size++) not_eq 43uz)
        return false;
    
    --size;
    if(static_cast<Size::Native>(size) not_eq 43uz)
        return false;

    if(static_cast<Size::Native>(size--) not_eq 43uz)
        return false;

    if(static_cast<Size::Native>(size + 10_size) not_eq 52uz)
        return false;

    if(static_cast<Size::Native>(size - 10_size) not_eq 32uz)
        return false;

    if(static_cast<Size::Native>(size * 10_size) not_eq 420uz)
        return false;

    if(static_cast<Size::Native>(size / 10_size) not_eq 4uz)
        return false;

    if(static_cast<Size::Native>(size % 10_size) not_eq 2uz)
        return false;

    size += 10_size;
    if(static_cast<Size::Native>(size) not_eq 52uz)
        return false;

    size -= 10_size;
    if(static_cast<Size::Native>(size) not_eq 42uz)
        return false;

    size *= 10_size;
    if(static_cast<Size::Native>(size) not_eq 420uz)
        return false;

    size /= 10_size;
    if(static_cast<Size::Native>(size) not_eq 42uz)
        return false;

    size %= 10_size;
    if(static_cast<Size::Native>(size) not_eq 2uz)
        return false;

    size = 0uz;
    if(static_cast<Size::Native>(size.IsolateHighestOne()) not_eq 0uz)
        return false;

    size = 0b01100100uz;
    if(static_cast<Size::Native>(size.IsolateHighestOne()) not_eq 0b01000000uz)
        return false;

    size = 0uz;
    if(static_cast<Size::Native>(size.IsolateLowestOne()) not_eq 0uz)
        return false;

    size = 0b01100100uz;
    if(static_cast<Size::Native>(size.IsolateLowestOne()) not_eq 0b00000100uz)
        return false;

    size = 0x1234567890123456uz;
    if(static_cast<Size::Native>(size.SwapBytes()) not_eq 0x5634129078563412uz)
        return false;
    
    return static_cast<Size::Native>(42_size) == 42uz;
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