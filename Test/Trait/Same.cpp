// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"

using Alice::Trait::Same;

// -----------------------------------------------------------------------------
// Test Helpers (Custom Types)
// -----------------------------------------------------------------------------

struct TypeA{};

struct TypeB{};

template<Same<bool> auto boolean> struct TypeC
{
    static constexpr bool value = boolean;
};

// -----------------------------------------------------------------------------
// Test Suite (Static Assertions)
// -----------------------------------------------------------------------------

// Positive Cases: These MUST evaluate to true
static_assert(Same<int, int>, "Failed: int should be same as int");
static_assert(Same<TypeA, TypeA>, "Failed: TypeA should be same as TypeA");
static_assert(Same<void*, void*>, "Failed: void* should be same as void*");
static_assert(TypeC<true>::value, "Failed: `boolean` should be true and of bool type");

// Negative Cases: These MUST evaluate to false (note the !)
static_assert(not Same<int, float>, "Failed: int is NOT float");
static_assert(not Same<TypeA, TypeB>, "Failed: TypeA is NOT TypeB");

// Qualifier Sensitivity Tests (Const/Volatile)
static_assert(not Same<int, const int>, "Failed: int is NOT const int");
static_assert(not Same<int, volatile int>, "Failed: int is NOT volatile int");
static_assert(not Same<const int, volatile int>, "Failed: const is NOT volatile");
static_assert(Same<const TypeA, const TypeA>, "Failed: const A should be const A");

// Reference Sensitivity Tests
static_assert(not Same<int, int&>, "Failed: int is NOT int&");
static_assert(not Same<int&, int&&>, "Failed: lvalue ref is NOT rvalue ref");

// Pointer Sensitivity Tests
static_assert(not Same<int, int*>, "Failed: int is NOT int*");
static_assert(not Same<int*, const int*>, "Failed: int* is NOT const int*");

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return Same<int, int>;
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