// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Constructible.hpp"

using Alice::Trait::Constructible;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Test subjects -----------------------------------------------------------

    struct DefaultConstructible
    {
        DefaultConstructible() = default;
    };

    struct NonDefaultConstructible
    {
        NonDefaultConstructible() = delete;

        explicit NonDefaultConstructible(int){}
    };

    struct CopyConstructible
    {
        CopyConstructible(const CopyConstructible&) = default;

        CopyConstructible() = default;
    };

    struct NonCopyConstructible
    {
        NonCopyConstructible(const NonCopyConstructible&) = delete;

        NonCopyConstructible() = default;
    };

    struct MoveConstructible
    {
        MoveConstructible(MoveConstructible&&) = default;

        MoveConstructible() = default;
    };

    struct NonMoveConstructible
    {
        NonMoveConstructible(NonMoveConstructible&&) = delete;

        NonMoveConstructible() = default;
    };

    struct MultiArgConstructible
    {
        MultiArgConstructible(int, float, bool){}
    };

    struct PrivateConstructor
    {
    private:
        PrivateConstructor() = default;
    };

    // --- Positive cases ----------------------------------------------------------

    // Default construction

    static_assert(Constructible<DefaultConstructible>, "DefaultConstructible must satisfy Constructible<>");

    // Construction from a matching single argument

    static_assert(Constructible<NonDefaultConstructible, int>,
    "NonDefaultConstructible must satisfy Constructible<int>");

    // Copy construction

    static_assert(Constructible<CopyConstructible, const CopyConstructible&>,
    "CopyConstructible must satisfy Constructible<const CopyConstructible&>");

    // Move construction

    static_assert(Constructible<MoveConstructible, MoveConstructible&&>,
    "MoveConstructible must satisfy Constructible<MoveConstructible&&>");

    // Multi-argument construction

    static_assert(Constructible<MultiArgConstructible, int, float, bool>,
    "MultiArgConstructible must satisfy Constructible<int, float, bool>");

    // Scalars are constructible from themselves

    static_assert(Constructible<int, int>, "int must satisfy Constructible<int>");
    static_assert(Constructible<int>, "int must satisfy Constructible<> (value-initialisation)");

    // --- Negative cases ----------------------------------------------------------

    // Deleted default constructor

    static_assert(not Constructible<NonDefaultConstructible>,
    "NonDefaultConstructible must not satisfy Constructible<>");

    // Deleted copy constructor
    
    static_assert(not Constructible<NonCopyConstructible, const NonCopyConstructible&>,
    "NonCopyConstructible must not satisfy Constructible<const NonCopyConstructible&>");

    // Deleted move constructor
    
    static_assert(not Constructible<NonMoveConstructible, NonMoveConstructible&&>,
    "NonMoveConstructible must not satisfy Constructible<NonMoveConstructible&&>");

    // Wrong argument types
    
    static_assert(not Constructible<NonDefaultConstructible, float*>,
    "NonDefaultConstructible must not satisfy Constructible<float*>");

    // Too many arguments
    
    static_assert(not Constructible<MultiArgConstructible, int, float, bool, int>,
    "MultiArgConstructible must not satisfy Constructible<int, float, bool, int>");

    // Too few arguments
    
    static_assert(not Constructible<MultiArgConstructible, int>,
    "MultiArgConstructible must not satisfy Constructible<int>");

    // Private constructor
    
    static_assert(not Constructible<PrivateConstructor>,
    "PrivateConstructor must not satisfy Constructible<>");

    // References are never default-constructible
    
    static_assert(not Constructible<int&>, "int& must not satisfy Constructible<>");

    struct Incomplete;
    return not Constructible<Incomplete>;
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