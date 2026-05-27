// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Union.hpp"

using Alice::Trait::Union;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    union EmptyUnion{};

    union SimpleUnion
    {
        int i;
        
        float f;
    };

    union SingleMemberUnion
    {
        double d;
    };

    struct NotAUnion{};

    class NotAUnionClass{};

    enum NotAUnionEnum
    {
        A,
        B
    };

    enum class NotAUnionEnumClass
    {
        A,
        B
    };

    // Positive cases

    static_assert(Union<EmptyUnion>);
    static_assert(Union<SimpleUnion>);
    static_assert(Union<SingleMemberUnion>);
    static_assert(Union<const SimpleUnion>);
    static_assert(Union<volatile SimpleUnion>);
    static_assert(Union<const volatile SimpleUnion>);

    // Negative cases

    static_assert(not Union<NotAUnion>);
    static_assert(not Union<NotAUnionClass>);
    static_assert(not Union<NotAUnionEnum>);
    static_assert(not Union<NotAUnionEnumClass>);
    static_assert(not Union<int>);
    static_assert(not Union<float>);
    static_assert(not Union<void>);
    static_assert(not Union<int*>);
    static_assert(not Union<int&>);
    static_assert(not Union<int[]>);
    static_assert(not Union<int[4]>);

    struct Incomplete;
    return not Union<Incomplete>;
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