// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Reference.hpp"

using Alice::Trait::Reference;

// Test 1: Lvalue references ARE References
static_assert(Reference<int&>, "Failed: int& should be a Reference");
static_assert(Reference<char&>, "Failed: char& should be a Reference");
static_assert(Reference<float&>, "Failed: float& should be a Reference");
static_assert(Reference<double&>, "Failed: double& should be a Reference");

// Test 2: Rvalue references ARE References
static_assert(Reference<int&&>, "Failed: int&& should be a Reference");
static_assert(Reference<char&&>, "Failed: char&& should be a Reference");
static_assert(Reference<float&&>, "Failed: float&& should be a Reference");
static_assert(Reference<double&&>, "Failed: double&& should be a Reference");

// Test 3: Non-reference types are NOT References
static_assert(not Reference<int>, "Failed: int should NOT be a Reference");
static_assert(not Reference<char>, "Failed: char should NOT be a Reference");
static_assert(not Reference<float>, "Failed: float should NOT be a Reference");
static_assert(not Reference<void>, "Failed: void should NOT be a Reference");

// Test 4: Pointers are NOT References
static_assert(not Reference<int*>, "Failed: int* should NOT be a Reference");
static_assert(not Reference<char*>, "Failed: char* should NOT be a Reference");
static_assert(not Reference<void*>, "Failed: void* should NOT be a Reference");

// Test 5: References to pointers ARE References
static_assert(Reference<int*&>, "Failed: int*& should be a Reference");
static_assert(Reference<int*&&>, "Failed: int*&& should be a Reference");
static_assert(Reference<char*&>, "Failed: char*& should be a Reference");

// Test 6: cv-qualified lvalue references ARE References
static_assert(Reference<const int&>, "Failed: const int& should be a Reference");
static_assert(Reference<volatile int&>, "Failed: volatile int& should be a Reference");
static_assert(Reference<const volatile int&>, "Failed: const volatile int& should be a Reference");

// Test 7: cv-qualified rvalue references ARE References
static_assert(Reference<const int&&>, "Failed: const int&& should be a Reference");
static_assert(Reference<volatile int&&>, "Failed: volatile int&& should be a Reference");
static_assert(Reference<const volatile int&&>, "Failed: const volatile int&& should be a Reference"
);

// Test 8: References to arrays ARE References
static_assert(Reference<int(&)[10]>, "Failed: int(&)[10] should be a Reference");
static_assert(Reference<int(&&)[10]>, "Failed: int(&&)[10] should be a Reference");
static_assert(Reference<char(&)[5]>, "Failed: char(&)[5] should be a Reference");
static_assert(Reference<int(&)[]>, "Failed: int(&)[] should be a Reference");

// Test 9: Arrays themselves are NOT References
static_assert(not Reference<int[10]>, "Failed: int[10] should NOT be a Reference");
static_assert(not Reference<char[]>, "Failed: char[] should NOT be a Reference");

// Test 10: References to functions ARE References
using FuncType = int(int, int);

static_assert(Reference<FuncType&>, "Failed: FuncType& should be a Reference");
static_assert(Reference<FuncType&&>, "Failed: FuncType&& should be a Reference");
static_assert(Reference<int(&)(int)>, "Failed: int(&)(int) should be a Reference");

// Test 11: Function types and function pointers are NOT References
static_assert(not Reference<FuncType>, "Failed: function type should NOT be a Reference");
static_assert(not Reference<FuncType*>, "Failed: function pointer should NOT be a Reference");
static_assert(not Reference<int(*)(int)>, "Failed: int(*)(int) should NOT be a Reference");

// Test 12: Custom types
struct CustomType
{
    int x;
};

enum class CustomEnum
{
    A,
    B,
    C
};

static_assert(Reference<CustomType&>, "Failed: CustomType& should be a Reference");
static_assert(Reference<CustomType&&>, "Failed: CustomType&& should be a Reference");
static_assert(not Reference<CustomType>, "Failed: CustomType should NOT be a Reference");
static_assert(Reference<CustomEnum&>, "Failed: CustomEnum& should be a Reference");
static_assert(not Reference<CustomEnum>, "Failed: CustomEnum should NOT be a Reference");

// Test 13: References to cv-qualified pointers ARE References
static_assert(Reference<const int*&>, "Failed: const int*& should be a Reference");
static_assert(Reference<int* const&>, "Failed: int* const& should be a Reference");
static_assert(Reference<const int* const&>, "Failed: const int* const& should be a Reference");

// Test 14: References to void are NOT possible (but void and void* themselves are not References)
static_assert(not Reference<void>, "Failed: void should NOT be a Reference");
static_assert(not Reference<void*>, "Failed: void* should NOT be a Reference");

// Test 15: Pointers to references don't exist, but we can test pointer to non-reference
static_assert(not Reference<int**>, "Failed: int** should NOT be a Reference");

// Test 16: Mixed lvalue and rvalue scenarios with complex types
static_assert(Reference<const CustomType&>, "Failed: const CustomType& should be a Reference");
static_assert(Reference<volatile CustomType&&>,
"Failed: volatile CustomType&& should be a Reference");
static_assert(Reference<int(&)[10][20]>, "Failed: int(&)[10][20] should be a Reference");

struct Incomplete;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return not Reference<Incomplete> and Reference<Incomplete&>;
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