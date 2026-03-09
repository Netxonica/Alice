// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/NullPointer.hpp"

using Alice::Trait::NullPointer;

// --- Types that MUST satisfy NullPointer ---

static_assert(NullPointer<decltype(nullptr)>, "decltype(nullptr) must satisfy NullPointer");
static_assert(NullPointer<const decltype(nullptr)>,
"const decltype(nullptr) must satisfy NullPointer");
static_assert(NullPointer<volatile decltype(nullptr)>,
"volatile decltype(nullptr) must satisfy NullPointer");
static_assert(NullPointer<const volatile decltype(nullptr)>,
"const volatile decltype(nullptr) must satisfy NullPointer");

// --- Types that MUST NOT satisfy NullPointer ---

static_assert(not NullPointer<void>, "void must not satisfy NullPointer");
static_assert(not NullPointer<bool>, "bool must not satisfy NullPointer");
static_assert(not NullPointer<char>, "char must not satisfy NullPointer");
static_assert(not NullPointer<signed char>, "signed char must not satisfy NullPointer");
static_assert(not NullPointer<unsigned char>, "unsigned char must not satisfy NullPointer");
static_assert(not NullPointer<short>, "short must not satisfy NullPointer");
static_assert(not NullPointer<unsigned short>, "unsigned short must not satisfy NullPointer");
static_assert(not NullPointer<int>, "int must not satisfy NullPointer");
static_assert(not NullPointer<unsigned int>, "unsigned int must not satisfy NullPointer");
static_assert(not NullPointer<long>, "long must not satisfy NullPointer");
static_assert(not NullPointer<unsigned long>, "unsigned long must not satisfy NullPointer");
static_assert(not NullPointer<long long>, "long long must not satisfy NullPointer");
static_assert(not NullPointer<unsigned long long>,
"unsigned long long must not satisfy NullPointer");
static_assert(not NullPointer<float>, "float must not satisfy NullPointer");
static_assert(not NullPointer<double>, "double must not satisfy NullPointer");
static_assert(not NullPointer<long double>, "long double must not satisfy NullPointer");
static_assert(not NullPointer<void*>, "void* must not satisfy NullPointer");
static_assert(not NullPointer<int*>, "int* must not satisfy NullPointer");
static_assert(not NullPointer<const int*>, "const int* must not satisfy NullPointer");
static_assert(not NullPointer<decltype(nullptr)*>,
"decltype(nullptr)* must not satisfy NullPointer");
static_assert(not NullPointer<int&>, "int& must not satisfy NullPointer");
static_assert(not NullPointer<int&&>, "int&& must not satisfy NullPointer");
static_assert(not NullPointer<decltype(nullptr)&>,
"decltype(nullptr)& must not satisfy NullPointer");
static_assert(not NullPointer<int[]>, "int[] must not satisfy NullPointer");
static_assert(not NullPointer<int[1]>, "int[1] must not satisfy NullPointer");

enum PlainEnum
{
    kA
};

enum class ScopedEnum
{
    kB
};

static_assert(not NullPointer<PlainEnum>, "plain enum must not satisfy NullPointer");

static_assert(not NullPointer<ScopedEnum>, "scoped enum must not satisfy NullPointer");

struct EmptyStruct{};

class EmptyClass{};

union EmptyUnion{};

static_assert(not NullPointer<EmptyStruct>, "struct must not satisfy NullPointer");
static_assert(not NullPointer<EmptyClass>, "class must not satisfy NullPointer");
static_assert(not NullPointer<EmptyUnion>, "union must not satisfy NullPointer");
static_assert(not NullPointer<int EmptyStruct::*>, "pointer-to-member must not satisfy NullPointer"
);

// ===========================================================================
// Runtime tests: concept used as a constraint in function overloads
// ===========================================================================

// Returns 1 when the argument is a null pointer, 0 otherwise.
[[nodiscard]] constexpr auto dispatch(NullPointer auto) noexcept -> bool
{
    return true;
}

[[nodiscard]] constexpr auto dispatch(auto) noexcept -> bool
{
    return false;
}

struct Incomplete;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // nullptr literal  → should pick the NullPointer overload
    if(not dispatch(nullptr))
        return false;

    // Typed nullptr variable
    decltype(nullptr) np{};
    if(not dispatch(np))
        return false;

    // Plain pointer (non-null) → should NOT pick the NullPointer overload
    int x = 0;
    if(dispatch(&x))
        return false;

    // Integer zero → should NOT pick the NullPointer overload
    if(dispatch(0))
        return false;

    return not NullPointer<Incomplete>;
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