// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemovePointer.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemovePointer;

// Test 1: Remove single pointer
static_assert(Same<RemovePointer<int*>, int>, "Failed: int* should become int");
static_assert(Same<RemovePointer<char*>, char>, "Failed: char* should become char");
static_assert(Same<RemovePointer<float*>, float>, "Failed: float* should become float");
static_assert(Same<RemovePointer<double*>, double>, "Failed: double* should become double");

// Test 2: Remove double pointer (only removes one level)
static_assert(Same<RemovePointer<int**>, int*>, "Failed: int** should become int*");
static_assert(Same<RemovePointer<char**>, char*>, "Failed: char** should become char*");

// Test 3: Remove triple pointer (only removes one level)
static_assert(Same<RemovePointer<int***>, int**>, "Failed: int*** should become int**");

// Test 4: Non-pointer types remain unchanged
static_assert(Same<RemovePointer<int>, int>, "Failed: int should remain int");
static_assert(Same<RemovePointer<char>, char>, "Failed: char should remain char");
static_assert(Same<RemovePointer<float>, float>, "Failed: float should remain float");

// Test 5: Const-qualified pointers
static_assert(Same<RemovePointer<const int*>, const int>,
"Failed: const int* should become const int");
static_assert(Same<RemovePointer<int* const>, int>, "Failed: int* const should become int");
static_assert(Same<RemovePointer<const int* const>, const int>,
"Failed: const int* const should become const int");

// Test 6: Volatile-qualified pointers
static_assert(Same<RemovePointer<volatile int*>, volatile int>,
"Failed: volatile int* should become volatile int");
static_assert(Same<RemovePointer<int* volatile>, int>, "Failed: int* volatile should become int");

// Test 7: CV-qualified pointers
static_assert(Same<RemovePointer<const volatile int*>, const volatile int>,
"Failed: const volatile int* should become const volatile int");
static_assert(Same<RemovePointer<const volatile int* const volatile>, const volatile int>,
"Failed: const volatile int* const volatile should become const volatile int");

// Test 8: Pointer to array
static_assert(Same<RemovePointer<int(*)[10]>, int[10]>, "Failed: int(*)[10] should become int[10]")
;
static_assert(Same<RemovePointer<char(*)[5]>, char[5]>, "Failed: char(*)[5] should become char[5]")
;

// Test 9: Pointer to function
using FuncType = int(int, int);

using FuncType2 = void();

static_assert(Same<RemovePointer<FuncType*>, FuncType>,
"Failed: pointer to function int(int, int) should become int(int, int)");
static_assert(Same<RemovePointer<FuncType2*>, FuncType2>,
"Failed: pointer to function void() should become void()");

// Test 10: Custom types
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

static_assert(Same<RemovePointer<CustomType*>, CustomType>,
"Failed: CustomType* should become CustomType");
static_assert(Same<RemovePointer<CustomType>, CustomType>,
"Failed: CustomType should remain CustomType");
static_assert(Same<RemovePointer<CustomEnum*>, CustomEnum>,
"Failed: CustomEnum* should become CustomEnum");

// Test 11: Pointer to const vs const pointer distinction
static_assert(Same<RemovePointer<const int*>, const int>,
"Failed: const int* should preserve const qualification");
static_assert(not Same<RemovePointer<const int*>, int>,
"Failed: const int* should NOT become non-const int");

// Test 12: Void pointer
static_assert(Same<RemovePointer<void*>, void>, "Failed: void* should become void");
static_assert(Same<RemovePointer<const void*>, const void>,
"Failed: const void* should become const void");

// Test 13: Multiple levels require multiple applications
static_assert(not Same<RemovePointer<int**>, int>,
"Failed: RemovePointer should only remove one level");
static_assert(Same<RemovePointer<RemovePointer<int**>>, int>,
"Failed: Nested RemovePointer should remove two levels");

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return Same<void, RemovePointer<void*>>;
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