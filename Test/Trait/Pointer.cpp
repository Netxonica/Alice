// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Pointer.hpp"

using Alice::Trait::Pointer;

// Test 1: Single pointers should be detected as pointers
static_assert(Pointer<int*>, "Failed: int* should be a pointer");
static_assert(Pointer<char*>, "Failed: char* should be a pointer");
static_assert(Pointer<float*>, "Failed: float* should be a pointer");
static_assert(Pointer<double*>, "Failed: double* should be a pointer");

// Test 2: Multiple levels of pointers
static_assert(Pointer<int**>, "Failed: int** should be a pointer");
static_assert(Pointer<char**>, "Failed: char** should be a pointer");
static_assert(Pointer<int***>, "Failed: int*** should be a pointer");

// Test 3: Non-pointer types should NOT be pointers
static_assert(not Pointer<int>, "Failed: int should NOT be a pointer");
static_assert(not Pointer<char>, "Failed: char should NOT be a pointer");
static_assert(not Pointer<float>, "Failed: float should NOT be a pointer");
static_assert(not Pointer<double>, "Failed: double should NOT be a pointer");

// Test 4: Const-qualified pointers
static_assert(Pointer<const int*>, "Failed: const int* should be a pointer");
static_assert(Pointer<int* const>, "Failed: int* const should be a pointer");
static_assert(Pointer<const int* const>, "Failed: const int* const should be a pointer");

// Test 5: Volatile-qualified pointers
static_assert(Pointer<volatile int*>, "Failed: volatile int* should be a pointer");
static_assert(Pointer<int* volatile>, "Failed: int* volatile should be a pointer");

// Test 6: CV-qualified pointers
static_assert(Pointer<const volatile int*>, "Failed: const volatile int* should be a pointer");
static_assert(Pointer<const volatile int* const volatile>,
"Failed: const volatile int* const volatile should be a pointer");

// Test 7: Pointer to array
static_assert(Pointer<int(*)[10]>, "Failed: int(*)[10] should be a pointer");
static_assert(Pointer<char(*)[5]>, "Failed: char(*)[5] should be a pointer");

// Test 8: Pointer to function
using FuncType = int(int, int);

using FuncType2 = void();

static_assert(Pointer<FuncType*>, "Failed: pointer to function int(int, int) should be a pointer");
static_assert(Pointer<FuncType2*>, "Failed: pointer to function void() should be a pointer");

// Test 9: Custom types
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

static_assert(Pointer<CustomType*>, "Failed: CustomType* should be a pointer");
static_assert(not Pointer<CustomType>, "Failed: CustomType should NOT be a pointer");
static_assert(Pointer<CustomEnum*>, "Failed: CustomEnum* should be a pointer");
static_assert(not Pointer<CustomEnum>, "Failed: CustomEnum should NOT be a pointer");

// Test 10: Void pointers
static_assert(Pointer<void*>, "Failed: void* should be a pointer");
static_assert(Pointer<const void*>, "Failed: const void* should be a pointer");
static_assert(Pointer<volatile void*>, "Failed: volatile void* should be a pointer");

// Test 11: References are NOT pointers
static_assert(not Pointer<int&>, "Failed: int& should NOT be a pointer");
static_assert(not Pointer<const int&>, "Failed: const int& should NOT be a pointer");
static_assert(not Pointer<int&&>, "Failed: int&& should NOT be a pointer");

// Test 12: Arrays are NOT pointers
static_assert(not Pointer<int[10]>, "Failed: int[10] should NOT be a pointer");
static_assert(not Pointer<char[5]>, "Failed: char[5] should NOT be a pointer");

// Test 13: Function types are NOT pointers
static_assert(not Pointer<FuncType>, "Failed: function type int(int, int) should NOT be a pointer")
;
static_assert(not Pointer<FuncType2>, "Failed: function type void() should NOT be a pointer");

// Test 14: Nullptr type
static_assert(not Pointer<decltype(nullptr)>,
"Failed: decltype(nullptr) should NOT be a pointer type");

// Test 15: Pointer to pointer to const
static_assert(Pointer<const int**>, "Failed: const int** should be a pointer");
static_assert(Pointer<int* const*>, "Failed: int* const* should be a pointer");

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return not Pointer<int*&>;
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