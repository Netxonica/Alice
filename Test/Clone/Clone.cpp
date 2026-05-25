// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Clone/Clone.hpp"

using Alice::Clone;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Test fixtures ---

    struct ValidClone
    {
        ValidClone Clone() const
        {
            return {};
        }
    };

    struct NoCloneMethod
    {
        // No Clone() at all
    };

    struct CloneReturnsDifferentType
    {
        struct Other{};

        Other Clone() const
        {
            return {};
        }
    };

    struct CloneNotConst
    {
        CloneNotConst Clone()
        {
            return {};
        }  // missing const
    };

    struct CloneTakesParameters
    {
        CloneTakesParameters Clone(int) const
        {
            return {};
        }
    };

    struct CloneReturnsVoid
    {
        void Clone() const{}
    };

    struct CloneReturnsRef
    {
        // Returns a reference to Self, not Self by value; Same<Self> requires exact type match
        CloneReturnsRef& Clone() const
        {
            static CloneReturnsRef instance;
            return instance;
        }
    };

    struct CloneReturnsConstRef
    {
        const CloneReturnsConstRef& Clone() const
        {
            static CloneReturnsConstRef instance;
            return instance;
        }
    };

    struct CloneReturnsPointer
    {
        CloneReturnsPointer* Clone() const
        {
            return nullptr;
        }
    };

    struct DerivedValid : ValidClone{};  // inherits a valid Clone(), but because it doesn't return
                                         // DerivedValid, it is invalid

    struct OverloadedClone
    {
        // One overload is valid, another is not; the const one must be valid
        OverloadedClone Clone() const
        {
            return {};
        }

        OverloadedClone Clone(int)
        {
            return {};
        }
    };

    // --- Positive assertions (must satisfy Clone) ---

    static_assert(Clone<ValidClone>,
    "ValidClone has Clone() const -> ValidClone; must satisfy Clone");
    static_assert(Clone<OverloadedClone>,
    "OverloadedClone has a valid Clone() const overload; must satisfy Clone");

    // --- Negative assertions (must NOT satisfy Clone) ---

    static_assert(not Clone<DerivedValid>,
    "DerivedValid inherits a valid Clone() const; must satisfy Clone");
    static_assert(not Clone<NoCloneMethod>, "NoCloneMethod has no Clone(); must not satisfy Clone")
    ;
    static_assert(not Clone<CloneReturnsDifferentType>,
    "Clone() returns a different type; must not satisfy Clone");
    static_assert(not Clone<CloneNotConst>,
    "Clone() is not const-qualified; must not satisfy Clone");
    static_assert(not Clone<CloneTakesParameters>,
    "Clone() requires a parameter; must not satisfy Clone");
    static_assert(not Clone<CloneReturnsVoid>, "Clone() returns void; must not satisfy Clone");
    static_assert(not Clone<CloneReturnsRef>,
    "Clone() returns Self&, not Self; must not satisfy Clone");
    static_assert(not Clone<CloneReturnsConstRef>,
    "Clone() returns const Self&, not Self; must not satisfy Clone");
    static_assert(not Clone<CloneReturnsPointer>,
    "Clone() returns Self*, not Self; must not satisfy Clone");

    // Primitive types carry no Clone() method

    static_assert(not Clone<int>, "int must not satisfy Clone");
    static_assert(not Clone<float>, "float must not satisfy Clone");
    static_assert(not Clone<void*>, "void* must not satisfy Clone");

    struct Incomplete;
    return not Clone<Incomplete>;
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