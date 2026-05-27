// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/UnscopedEnumeration.hpp"

using Alice::Trait::UnscopedEnumeration;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    enum PlainEnum
    {
        A,
        B,
        C
    };

    enum PlainEnumWithBase : int
    {
        X,
        Y,
        Z
    };

    enum class ScopedEnumClass
    {
        Foo,
        Bar
    };

    enum struct ScopedEnumStruct
    {
        Baz,
        Qux
    };

    struct Struct{};

    union Union
    {
        int i;
        
        float f;
    };

    class Class{};

    // Satisfied: plain unscoped enums

    static_assert(UnscopedEnumeration<PlainEnum>);
    static_assert(UnscopedEnumeration<PlainEnumWithBase>);
    static_assert(UnscopedEnumeration<const PlainEnum>);
    static_assert(UnscopedEnumeration<volatile PlainEnum>);
    static_assert(UnscopedEnumeration<const volatile PlainEnum>);

    // Not satisfied: scoped enums (enum class / enum struct)

    static_assert(not UnscopedEnumeration<ScopedEnumClass>);
    static_assert(not UnscopedEnumeration<ScopedEnumStruct>);

    // Not satisfied: non-enum types

    static_assert(not UnscopedEnumeration<int>);
    static_assert(not UnscopedEnumeration<float>);
    static_assert(not UnscopedEnumeration<bool>);
    static_assert(not UnscopedEnumeration<char>);
    static_assert(not UnscopedEnumeration<void>);
    static_assert(not UnscopedEnumeration<Struct>);
    static_assert(not UnscopedEnumeration<Union>);
    static_assert(not UnscopedEnumeration<Class>);
    static_assert(not UnscopedEnumeration<int*>);
    static_assert(not UnscopedEnumeration<int&>);
    static_assert(not UnscopedEnumeration<int[]>);

    struct Incomplete;
    return not UnscopedEnumeration<Incomplete>;
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