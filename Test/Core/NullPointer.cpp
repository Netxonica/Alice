// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Core/NullPointer.hpp"

using Alice::Trait::Same;
using Alice::NullPointer;

// Test 1: NullPointer IS the same as decltype(nullptr)
static_assert(Same<NullPointer, decltype(nullptr)>,
"Failed: NullPointer should be the same as decltype(nullptr)");

// Test 2: NullPointer is NOT the same as fundamental types
static_assert(not Same<NullPointer, int>, "Failed: NullPointer should NOT be the same as int");
static_assert(not Same<NullPointer, char>, "Failed: NullPointer should NOT be the same as char");
static_assert(not Same<NullPointer, bool>, "Failed: NullPointer should NOT be the same as bool");
static_assert(not Same<NullPointer, void>, "Failed: NullPointer should NOT be the same as void");

// Test 3: NullPointer is NOT the same as pointer types
static_assert(not Same<NullPointer, int*>, "Failed: NullPointer should NOT be the same as int*");
static_assert(not Same<NullPointer, void*>, "Failed: NullPointer should NOT be the same as void*");
static_assert(not Same<NullPointer, char*>, "Failed: NullPointer should NOT be the same as char*");
static_assert(not Same<NullPointer, NullPointer*>,
"Failed: NullPointer should NOT be the same as NullPointer*");

// Test 4: NullPointer is NOT the same as reference types
static_assert(not Same<NullPointer, int&>, "Failed: NullPointer should NOT be the same as int&");
static_assert(not Same<NullPointer, int&&>, "Failed: NullPointer should NOT be the same as int&&");

// Test 5: cv-qualified NullPointer types
static_assert(Same<const NullPointer, const decltype(nullptr)>,
"Failed: const NullPointer should be the same as const decltype(nullptr)");
static_assert(not Same<NullPointer, const NullPointer>,
"Failed: NullPointer should NOT be the same as const NullPointer");
static_assert(not Same<NullPointer, volatile NullPointer>,
"Failed: NullPointer should NOT be the same as volatile NullPointer");

// Test 6: Compile-time initialization and assignment
constexpr NullPointer null_value = nullptr;

static_assert(null_value == nullptr,
"Failed: NullPointer initialized with nullptr should equal nullptr");

// Test 7: Multiple nullptr instances are equal
constexpr NullPointer null1 = nullptr;

constexpr NullPointer null2 = nullptr;

static_assert(null1 == null2, "Failed: Two NullPointer instances should be equal");

// Test 8: NullPointer can be assigned to pointers
constexpr auto test_assignment = []() consteval
{
    int* ptr = nullptr;
    NullPointer np = nullptr;
    ptr = np;
    return ptr == nullptr;
};

static_assert(test_assignment(), "Failed: NullPointer should be assignable to pointer types");

// Test 9: NullPointer can initialize pointers
constexpr auto test_initialization = []() consteval
{
    NullPointer np = nullptr;
    int* ptr = np;
    return ptr == nullptr;
};

static_assert(test_initialization(),
"Failed: NullPointer should be able to initialize pointer types");

// Test 10: NullPointer converts to bool as false
constexpr auto test_bool_conversion = []() consteval
{
    NullPointer np = nullptr;
    return not static_cast<bool>(np);
};

static_assert(test_bool_conversion(), "Failed: NullPointer should convert to bool as false");

// Test 11: NullPointer with various pointer types
constexpr auto test_various_pointers = []() consteval
{
    NullPointer np = nullptr;
    void* vp = np;
    int* ip = np;
    char* cp = np;
    return (vp == nullptr) and (ip == nullptr) and (cp == nullptr);
};

static_assert(test_various_pointers(),
"Failed: NullPointer should convert to various pointer types");

// Test 12: NullPointer with function pointers
constexpr auto test_function_pointer = []() consteval
{
    using FuncPtr = int(*)(int);
    NullPointer np = nullptr;
    FuncPtr fp = np;
    return fp == nullptr;
};

static_assert(test_function_pointer(),
"Failed: NullPointer should convert to function pointer types");

// Test 13: NullPointer with member pointers
struct TestStruct
{
    int x;
};

constexpr auto test_member_pointer = []() consteval
{
    using MemPtr = int TestStruct::*;
    NullPointer np = nullptr;
    MemPtr mp = np;
    return mp == nullptr;
};

static_assert(test_member_pointer(), "Failed: NullPointer should convert to member pointer types");

// Test 14: NullPointer comparison with nullptr
static_assert(nullptr == nullptr, "Failed: nullptr should equal nullptr");

constexpr NullPointer np = nullptr;

static_assert(np == nullptr, "Failed: NullPointer should equal nullptr");
static_assert(nullptr == np, "Failed: nullptr should equal NullPointer");

[[nodiscard]] consteval auto test_overload(void*) noexcept -> bool
{
    return false;
}

[[nodiscard]] consteval auto test_overload(NullPointer) noexcept -> bool
{
    return true;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return test_overload(nullptr);
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