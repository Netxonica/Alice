// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Move.hpp"
#include "Core/Size.hpp"

using Alice::Size;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Default constructor
    {
        Size skibidi;
        if(static_cast<Size::Native>(skibidi) not_eq 0uz)
            return false;
    }
    // Copy constructor
    {
        Size skibidi, fahh(skibidi);
        if(static_cast<Size::Native>(fahh) not_eq 0uz)
            return false;
    }
    // Move constructor
    {
        Size skibidi, fahh($move(skibidi));
        if(static_cast<Size::Native>(fahh) not_eq 0uz)
            return false;
    }
    // Native constructor
    {
        Size skibidi{67uz};
        if(static_cast<Size::Native>(skibidi) not_eq 67uz)
            return false;
    }
    // Copy assignment
    {
        Size skibidi{67uz}, fahh;
        fahh = skibidi;
        if(static_cast<Size::Native>(fahh) not_eq 67uz)
            return false;
    }
    // Move assignment
    {
        Size skibidi{67uz}, fahh;
        fahh = $move(skibidi);
        if(static_cast<Size::Native>(fahh) not_eq 67uz)
            return false;
    }
    // Native assignment
    {
        Size skibidi;
        skibidi = 67uz;
        if(static_cast<Size::Native>(skibidi) not_eq 67uz)
            return false;
    }
    // Minimum value
    {
        Size skibidi = Size::Minimum();
        if(static_cast<Size::Native>(skibidi) not_eq 0uz)
            return false;
    }
    // Maximum value
    {
        Size skibidi = Size::Maximum();
        if(static_cast<Size::Native>(skibidi) not_eq 18446744073709551615uz)
            return false;
    }
    // Bits value
    {
        Size skibidi = Size::Bits();
        if(static_cast<Size::Native>(skibidi) not_eq 64uz)
            return false;
    }
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