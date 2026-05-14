// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Convert/Into.hpp"

using Alice::Convert::Into;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Fixture types ─────────────────────────────────────────────────────────────

    struct Alpha{};

    struct Beta{};

    // Canonical case: a concrete conversion from Alpha to Beta.
    struct AlphaToBeta
    {
        Beta Into()
        {
            return Beta{};
        }
    };

    // A type that converts to itself.
    struct SelfLoop
    {
        SelfLoop Into()
        {
            return SelfLoop{};
        }
    };

    // Into() is const-qualified (still callable on an rvalue produced by $forward).
    struct ConstConvert
    {
        Beta Into() const
        {
            return Beta{};
        }
    };

    // Into() is lvalue-ref-qualified; cannot be called on the rvalue that
    // $forward(self) produces, so the concept must not be satisfied.
    struct LvalueOnly
    {
        Beta Into() &
        {
            return Beta{};
        }
    };

    // Into() returns the wrong type.
    struct WrongReturn
    {
        Alpha Into()
        {
            return Alpha{};
        } // returns Alpha, concept asks for Beta
    };

    // No Into() member at all.
    struct NoConvert{};

    // Into() takes a parameter — nullary call in the requires-expression must fail.
    struct NeedsParam
    {
        Beta Into(int)
        {
            return Beta{};
        }
    };

    // Into() is static — the concept's comment mandates a *non-static* member;
    // although `instance.Into()` would compile, this documents the boundary.
    struct StaticInto
    {
        static Beta Into()
        {
            return Beta{};
        }
    };

    // ── Positive assertions ───────────────────────────────────────────────────────

    // Basic: AlphaToBeta → Beta
    
    static_assert(Into<AlphaToBeta, Beta>,
    "A type with a matching Into() member must satisfy the concept.");

    // Self-to-self conversion
    
    static_assert(Into<SelfLoop, SelfLoop>, "A type converting to itself must satisfy the concept."
    );

    // const-qualified Into() is callable on an rvalue
    
    static_assert(Into<ConstConvert, Beta>, "A const Into() member must satisfy the concept.");

    // ── Negative assertions ───────────────────────────────────────────────────────

    // Self is not Sized (void has no sizeof)
    
    static_assert(not Into<void, Beta>,
    "void Self must not satisfy the concept (Marker::Sized not met).");

    // To is not Sized
    
    static_assert(not Into<AlphaToBeta, void>,
    "void To must not satisfy the concept (Marker::Sized not met).");

    // & -qualified Into() cannot be invoked on the rvalue from $forward(self)
    
    static_assert(not Into<LvalueOnly, Beta>,
    "An lvalue-ref-qualified Into() must not satisfy the concept.");

    // Return type mismatch: Into() gives Alpha, concept expects Beta
    
    static_assert(not Into<WrongReturn, Beta>,
    "A mismatched return type must not satisfy the concept.");

    // No Into() member at all
    
    static_assert(not Into<NoConvert, Beta>, "A type without Into() must not satisfy the concept.")
    ;

    // Nullary call fails when Into() requires an argument
    
    static_assert(not Into<NeedsParam, Beta>,
    "Into() requiring arguments must not satisfy the concept.");

    // Static method: concept requires a non-static member function
    
    static_assert(not Into<StaticInto, Beta>,
    "A static Into() method must not satisfy the concept.");

    // Reversed direction: Beta has no Into() returning AlphaToBeta
    
    static_assert(not Into<Beta, AlphaToBeta>,
    "A type lacking the required Into() in a given direction must not satisfy the concept.");

    struct Incomplete;
    return not Into<Incomplete, Incomplete>;
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