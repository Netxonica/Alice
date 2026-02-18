// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Function.hpp"

using Alice::Trait::Function;

// Test 1: Basic function types ARE Functions
static_assert(Function<void()>, "Failed: void() should be a Function");
static_assert(Function<int()>, "Failed: int() should be a Function");
static_assert(Function<int(int)>, "Failed: int(int) should be a Function");
static_assert(Function<int(int, float)>, "Failed: int(int, float) should be a Function");
static_assert(Function<void(int, int, int)>, "Failed: void(int, int, int) should be a Function");

// Test 2: Function types with various return types ARE Functions
static_assert(Function<char()>, "Failed: char() should be a Function");
static_assert(Function<float()>, "Failed: float() should be a Function");
static_assert(Function<double()>, "Failed: double() should be a Function");
static_assert(Function<int*()>, "Failed: int*() should be a Function");
static_assert(Function<void*()>, "Failed: void*() should be a Function");

// Test 3: Function pointers are NOT Functions (they're pointer types)
static_assert(not Function<void(*)()>,
"Failed: void(*)() should NOT be a Function, it is a function pointer");
static_assert(not Function<int(*)(int)>,
"Failed: int(*)(int) should NOT be a Function, it is a function pointer");
static_assert(not Function<int(*)(int, float)>,
"Failed: int(*)(int, float) should NOT be a Function, it is a function pointer");

// Test 4: Function references are NOT Functions (they're reference types)
static_assert(not Function<void(&)()>,
"Failed: void(&)() should NOT be a Function, it is a function reference");
static_assert(not Function<int(&)(int)>,
"Failed: int(&)(int) should NOT be a Function, it is a function reference");

// Test 5: Non-function types are NOT Functions
static_assert(not Function<int>, "Failed: int should NOT be a Function");
static_assert(not Function<float>, "Failed: float should NOT be a Function");
static_assert(not Function<void>, "Failed: void should NOT be a Function");
static_assert(not Function<int*>, "Failed: int* should NOT be a Function");

// Test 6: cv-qualified function types ARE Functions
static_assert(Function<void() const>, "Failed: void() const should be a Function");
static_assert(Function<void() volatile>, "Failed: void() volatile should be a Function");
static_assert(Function<void() const volatile>, "Failed: void() const volatile should be a Function"
);

// Test 7: cvref-qualified function types ARE Functions
static_assert(Function<void() &>, "Failed: void() & should be a Function");
static_assert(Function<void() &&>, "Failed: void() && should be a Function");
static_assert(Function<void() const &>, "Failed: void() const & should be a Function");
static_assert(Function<void() const &&>, "Failed: void() const && should be a Function");
static_assert(Function<void() volatile const &&>,
"Failed: void() volatile const && should be a Function");

// Test 8: noexcept function types ARE Functions
static_assert(Function<void() noexcept>, "Failed: void() noexcept should be a Function");
static_assert(Function<int(int) noexcept>, "Failed: int(int) noexcept should be a Function");
static_assert(Function<void() const noexcept>, "Failed: void() const noexcept should be a Function"
);

// Test 9: Variadic function types ARE Functions
static_assert(Function<void(...)>, "Failed: void(...) should be a Function");
static_assert(Function<int(int, ...)>, "Failed: int(int, ...) should be a Function");

// Test 10: Member function pointers are NOT Functions
struct TestClass{};

static_assert(not Function<void(TestClass::*)()>,
"Failed: void(TestClass::*)() should NOT be a Function, it is a member function pointer");
static_assert(not Function<int(TestClass::*)(int)>,
"Failed: int(TestClass::*)(int) should NOT be a Function, it is a member function pointer");

// Test 11: Arrays are NOT Functions
static_assert(not Function<int[10]>, "Failed: int[10] should NOT be a Function");
static_assert(not Function<void*[]>, "Failed: void*[] should NOT be a Function");

// Test 12: Classes/structs are NOT Functions
struct MyStruct
{
    int x;

    void operator()(){}
};

enum class MyEnum
{
    A,
    B,
    C
};

static_assert(not Function<MyStruct>, "Failed: MyStruct should NOT be a Function");
static_assert(not Function<MyEnum>, "Failed: MyEnum should NOT be a Function");

// Test 13: References to non-functions are NOT Functions
static_assert(not Function<int&>, "Failed: int& should NOT be a Function");
static_assert(not Function<int&&>, "Failed: int&& should NOT be a Function");

// Test 14: Complex function signatures ARE Functions
static_assert(Function<int(int*, const char*, float)>,
"Failed: int(int*, const char*, float) should be a Function");
static_assert(Function<void(int&, const float&)>,
"Failed: void(int&, const float&) should be a Function");
static_assert(Function<int*(void*, char)>, "Failed: int*(void*, char) should be a Function");

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return not Function<decltype([]{})>;
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