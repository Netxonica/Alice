// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Move.hpp"
#include "Math/Logic/Proposition.hpp"

using Alice::Math::Logic::Proposition;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Contradiction
    {
        Proposition skibidi = Proposition::Contradiction();
        if(static_cast<bool>(skibidi))
            return false;
    }
    // Copy constructor
    {
        Proposition skibidi = Proposition::Contradiction(), fanum(skibidi);
        if(static_cast<bool>(fanum))
            return false;
    }
    // Move constructor
    {
        Proposition skibidi = Proposition::Contradiction(), fanum($move(skibidi));
        if(static_cast<bool>(fanum))
            return false;
    }
    // Tautology
    {
        Proposition skibidi = Proposition::Tautology();
        if(not static_cast<bool>(skibidi))
            return false;
    }
    // NOT
    {
        Proposition skibidi = Proposition::Contradiction(), fanum = not skibidi;
        if(not static_cast<bool>(fanum))
            return false;
    }
    // AND
    {
        Proposition skibidi = Proposition::Contradiction(), meow = Proposition::Tautology(), fanum
        = skibidi and meow;
        if(static_cast<bool>(fanum))
            return false;
    }
    // OR
    {
        Proposition skibidi = Proposition::Contradiction(), meow = Proposition::Tautology(), fanum
        = skibidi or meow;
        if(not static_cast<bool>(fanum))
            return false;
    }
    // Implies
    {
        Proposition skibidi = Proposition::Contradiction(), meow = Proposition::Tautology(), fanum
        = skibidi.Implies(meow);
        if(not static_cast<bool>(fanum))
            return false;
    }
    // Biconditional
    {
        Proposition skibidi = Proposition::Contradiction(), meow = Proposition::Tautology(), fanum
        = skibidi == meow;
        if(static_cast<bool>(fanum))
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