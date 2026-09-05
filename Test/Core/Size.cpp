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
    // UDL
    {
        using namespace Alice::Literals;
        Size skibidi = 67_size;
        if(static_cast<Size::Native>(skibidi) not_eq 67uz)
            return false;
    }
    // Unary plus
    {
        Size skibidi{67uz};
        if(static_cast<Size::Native>(+skibidi) not_eq 67uz)
            return false;
    }
    // Pre-increment
    {
        Size skibidi{67uz};
        if(static_cast<Size::Native>(skibidi) not_eq 67uz)
            return false;
        if(static_cast<Size::Native>(++skibidi) not_eq 68uz)
            return false;
    }
    // Post-increment
    {
        Size skibidi{67uz};
        if(static_cast<Size::Native>(skibidi++) not_eq 67uz)
            return false;
        if(static_cast<Size::Native>(skibidi) not_eq 68uz)
            return false;
    }
    // Pre-decrement
    {
        Size skibidi{67uz};
        if(static_cast<Size::Native>(skibidi) not_eq 67uz)
            return false;
        if(static_cast<Size::Native>(--skibidi) not_eq 66uz)
            return false;
    }
    // Post-decrement
    {
        Size skibidi{67uz};
        if(static_cast<Size::Native>(skibidi--) not_eq 67uz)
            return false;
        if(static_cast<Size::Native>(skibidi) not_eq 66uz)
            return false;
    }
    // Addition and assignment
    {
        Size skibidi{67uz}, fanum{42uz};
        skibidi += fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 109uz)
            return false;
    }
    // Addition
    {
        Size skibidi{67uz}, fanum{42uz}, meow = skibidi + fanum;
        if(static_cast<Size::Native>(meow) not_eq 109uz)
            return false;
    }
    // Subtraction and assignment
    {
        Size skibidi{67uz}, fanum{42uz};
        skibidi -= fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 25uz)
            return false;
    }
    // Subtraction
    {
        Size skibidi{67uz}, fanum{42uz}, meow = skibidi - fanum;
        if(static_cast<Size::Native>(meow) not_eq 25uz)
            return false;
    }
    // Multiplication and assignment
    {
        Size skibidi{42uz}, fanum{10uz};
        skibidi *= fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 420uz)
            return false;
    }
    // Multiplication
    {
        Size skibidi{42uz}, fanum{10uz}, meow = skibidi * fanum;
        if(static_cast<Size::Native>(meow) not_eq 420uz)
            return false;
    }
    //Division and assignment
    {
        Size skibidi{40uz}, fanum{10uz};
        skibidi /= fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 4uz)
            return false;
    }
    // Division
    {
        Size skibidi{40uz}, fanum{10uz}, meow = skibidi / fanum;
        if(static_cast<Size::Native>(meow) not_eq 4uz)
            return false;
    }
    // Modulo and assignment
    {
        Size skibidi{42uz}, fanum{10uz};
        skibidi %= fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 2uz)
            return false;
    }
    // Modulo
    {
        Size skibidi{42uz}, fanum{10uz}, meow = skibidi % fanum;
        if(static_cast<Size::Native>(meow) not_eq 2uz)
            return false;
    }
    // Bitwise NOT
    {
        Size skibidi(42uz), fanum = compl skibidi;
        if(static_cast<Size::Native>(fanum) not_eq 18446744073709551573uz)
            return false;
    }
    // Bitwise AND and assignment
    {
        Size skibidi(42uz), fanum{10uz};
        skibidi and_eq fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 10uz)
            return false;
    }
    // Bitwise AND
    {
        Size skibidi(42uz), fanum{10uz}, meow = skibidi bitand fanum;
        if(static_cast<Size::Native>(meow) not_eq 10uz)
            return false;
    }
    // Bitwise OR and assignment
    {
        Size skibidi(42uz), fanum{10uz};
        skibidi or_eq fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 42uz)
            return false;
    }
    // Bitwise OR
    {
        Size skibidi(42uz), fanum{10uz}, meow = skibidi bitor fanum;
        if(static_cast<Size::Native>(meow) not_eq 42uz)
            return false;
    }
    // Bitwise XOR and assignment
    {
        Size skibidi(42uz), fanum{10uz};
        skibidi xor_eq fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 32uz)
            return false;
    }
    // Bitwise XOR
    {
        Size skibidi(42uz), fanum{10uz}, meow = skibidi xor fanum;
        if(static_cast<Size::Native>(meow) not_eq 32uz)
            return false;
    }
    // Bitwise left shift and assignment
    {
        Size skibidi(42uz), fanum{10uz};
        skibidi <<= fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 43008uz)
            return false;
    }
    // Bitwise left shift
    {
        Size skibidi(42uz), fanum{10uz}, meow = skibidi << fanum;
        if(static_cast<Size::Native>(meow) not_eq 43008uz)
            return false;
    }
    // Bitwise right shift and assignment
    {
        Size skibidi(42uz), fanum{1uz};
        skibidi >>= fanum;
        if(static_cast<Size::Native>(skibidi) not_eq 21uz)
            return false;
    }
    // Bitwise right shift
    {
        Size skibidi(42uz), fanum{1uz}, meow = skibidi >> fanum;
        if(static_cast<Size::Native>(meow) not_eq 21uz)
            return false;
    }
    // Less-than comparison
    {
        Size skibidi{42uz}, fanum{10uz};
        if(static_cast<bool>(skibidi < fanum))
            return false;
    }
    // Less-than-or-equal-to comparison
    {
        Size skibidi{42uz}, fanum{10uz};
        if(static_cast<bool>(skibidi <= fanum))
            return false;
    }
    // Greater-than comparison
    {
        Size skibidi{42uz}, fanum{10uz};
        if(not static_cast<bool>(skibidi > fanum))
            return false;
    }
    // Greater-than-or-equal-to comparison
    {
        Size skibidi{42uz}, fanum{10uz};
        if(not static_cast<bool>(skibidi >= fanum))
            return false;
    }
    // Equality comparison
    {
        Size skibidi{42uz}, fanum{10uz};
        if(static_cast<bool>(skibidi == fanum))
            return false;
    }
    // Inequality comparison
    {
        Size skibidi{42uz}, fanum{10uz};
        if(not static_cast<bool>(skibidi not_eq fanum))
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
        if(static_cast<Size::Native>(skibidi) not_eq 18'446'744'073'709'551'615uz)
            return false;
    }
    // Bits value
    {
        Size skibidi = Size::Bits();
        if(static_cast<Size::Native>(skibidi) not_eq 64uz)
            return false;
    }
    // Digits value
    {
        Size skibidi = Size::Digits();
        if(static_cast<Size::Native>(skibidi) not_eq 20uz)
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