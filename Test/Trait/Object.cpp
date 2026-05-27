// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Object.hpp"

using Alice::Trait::Object;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ── Fundamental scalar types ────────────────────────────────────────────────

    static_assert(Object<int>);
    static_assert(Object<unsigned int>);
    static_assert(Object<long>);
    static_assert(Object<unsigned long>);
    static_assert(Object<long long>);
    static_assert(Object<unsigned long long>);
    static_assert(Object<short>);
    static_assert(Object<unsigned short>);
    static_assert(Object<signed char>);
    static_assert(Object<unsigned char>);
    static_assert(Object<char>);
    static_assert(Object<char8_t>);
    static_assert(Object<char16_t>);
    static_assert(Object<char32_t>);
    static_assert(Object<wchar_t>);
    static_assert(Object<bool>);
    static_assert(Object<float>);
    static_assert(Object<double>);
    static_assert(Object<long double>);
    static_assert(Object<decltype(nullptr)>);   // std::nullptr_t

    // ── CV-qualified scalars ────────────────────────────────────────────────────

    static_assert(Object<const int>);
    static_assert(Object<volatile int>);
    static_assert(Object<const volatile int>);
    static_assert(Object<const double>);
    static_assert(Object<volatile double>);
    static_assert(Object<const volatile double>);

    // ── Pointer types (pointers are objects) ───────────────────────────────────

    static_assert(Object<int*>);
    static_assert(Object<const int*>);
    static_assert(Object<int* const>);
    static_assert(Object<void*>);              // pointer-to-void is itself an object
    static_assert(Object<int**>);

    // ── Pointer-to-member types ─────────────────────────────────────────────────

    struct S
    {
        int x;
        
        void f();
    };

    static_assert(Object<int S::*>);
    static_assert(Object<void (S::*)()>);

    // ── Array types ─────────────────────────────────────────────────────────────

    static_assert(Object<int[1]>);
    static_assert(Object<int[42]>);
    static_assert(Object<int[][3]>);           // incomplete array — still an object type
    static_assert(Object<const int[5]>);

    // ── Class / struct / union / enum types ────────────────────────────────────

    struct EmptyStruct{};

    struct NonEmpty
    {
        int a;
        
        float b;
    };

    union SomeUnion
    {
        int i;
        
        float f;
    };

    enum SomeEnum
    {
        A,
        B
    };

    enum class ScopedEnum
    {
        X,
        Y
    };

    static_assert(Object<EmptyStruct>);
    static_assert(Object<NonEmpty>);
    static_assert(Object<SomeUnion>);
    static_assert(Object<SomeEnum>);
    static_assert(Object<ScopedEnum>);

    // ── CV-qualified class / union types ───────────────────────────────────────

    static_assert(Object<const EmptyStruct>);
    static_assert(Object<volatile NonEmpty>);
    static_assert(Object<const volatile SomeUnion>);

    // ── Function-pointer types (the pointer itself is an object) ────────────────

    static_assert(Object<void(*)()>);
    static_assert(Object<int(*)(int, double)>);

    // ── Void is NOT an object ───────────────────────────────────────────────────

    static_assert(not Object<void>);
    static_assert(not Object<const void>);
    static_assert(not Object<volatile void>);
    static_assert(not Object<const volatile void>);

    // ── Reference types are NOT objects ────────────────────────────────────────

    static_assert(not Object<int&>);
    static_assert(not Object<const int&>);
    static_assert(not Object<int&&>);
    static_assert(not Object<EmptyStruct&>);
    static_assert(not Object<EmptyStruct&&>);

    // ── Raw function types are NOT objects ─────────────────────────────────────
    // (function pointers are, but bare function types are not)

    static_assert(not Object<void()>);
    static_assert(not Object<int(int)>);
    static_assert(not Object<double(float, long)>);
    static_assert(not Object<void(...) noexcept>);

    struct Incomplete;
    return Object<Incomplete>;
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