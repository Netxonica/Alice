// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Constant.hpp"

using Alice::Trait::Constant;

template<Constant> [[nodiscard]] consteval auto OnlyConst() noexcept -> bool
{
    return true;
}

template<class T> requires(not Constant<T>) [[nodiscard]] consteval auto OnlyMutable() noexcept ->
bool
{
    return true;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // --- Satisfies Constant ---

    struct Foo{};

    static_assert(Constant<const int>);
    static_assert(Constant<const float>);
    static_assert(Constant<const bool>);
    static_assert(Constant<const char>);
    static_assert(Constant<int* const>);
    static_assert(Constant<const int* const>);
    static_assert(Constant<const int&> == false);
    static_assert(Constant<const Foo>);
    static_assert(Constant<const Foo*> == false);
    static_assert(Constant<Foo* const>);

    // --- Does NOT satisfy Constant ---

    static_assert(not Constant<const void*>);
    static_assert(not Constant<int>);
    static_assert(not Constant<float>);
    static_assert(not Constant<bool>);
    static_assert(not Constant<char>);
    static_assert(not Constant<void*>);
    static_assert(not Constant<const int*>);
    static_assert(not Constant<int&>);
    static_assert(not Constant<const int&>);
    static_assert(not Constant<int&&>);
    static_assert(not Constant<Foo>);
    static_assert(not Constant<Foo*>);

    // --- Compile-time concept constraint usage (ensures concept gates templates correctly) ---

    static_assert(OnlyConst<const int>());
    static_assert(OnlyMutable<int>());

    struct Incomplete;
    return not Constant<Incomplete>;
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