// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/PointeeSized.hpp"

using Alice::Trait::PointeeSized;

// Forward-declared incomplete type
struct Incomplete;

// Test 1: Fundamental pointer types are PointeeSized
static_assert(PointeeSized<int*>, "Failed: int* should be PointeeSized");
static_assert(PointeeSized<char*>, "Failed: char* should be PointeeSized");
static_assert(PointeeSized<float*>, "Failed: float* should be PointeeSized");
static_assert(PointeeSized<double*>, "Failed: double* should be PointeeSized");
static_assert(PointeeSized<bool*>, "Failed: bool* should be PointeeSized");

// Test 2: Multi-level pointers are PointeeSized (pointee is a pointer, which is sized)
static_assert(PointeeSized<int**>, "Failed: int** should be PointeeSized, as int* has a known size"
);
static_assert(PointeeSized<int***>,
"Failed: int*** should be PointeeSized, as int** has a known size");
static_assert(PointeeSized<void**>,
"Failed: void** should be PointeeSized, as void* has a known size");

// Test 3: void* is NOT PointeeSized (void has no size)
static_assert(not PointeeSized<void*>,
"Failed: void* should NOT be PointeeSized, as void has no size");
static_assert(not PointeeSized<const void*>,
"Failed: const void* should NOT be PointeeSized, as void has no size");
static_assert(not PointeeSized<volatile void*>,
"Failed: volatile void* should NOT be PointeeSized, as void has no size");
static_assert(not PointeeSized<const volatile void*>,
"Failed: const volatile void* should NOT be PointeeSized, as void has no size");

// Test 4: Pointer to incomplete type is NOT PointeeSized
static_assert(not PointeeSized<Incomplete*>,
"Failed: Incomplete* should NOT be PointeeSized, as Incomplete is an incomplete type");
static_assert(not PointeeSized<const Incomplete*>,
"Failed: const Incomplete* should NOT be PointeeSized, as Incomplete is an incomplete type");

// Test 5: Function pointers are NOT PointeeSized (functions have no size)
using FuncType = int(int, int);

using FuncType2 = void();

static_assert(not PointeeSized<FuncType*>,
"Failed: FuncType* should NOT be PointeeSized, as function types have no size");
static_assert(not PointeeSized<FuncType2*>,
"Failed: FuncType2* should NOT be PointeeSized, as function types have no size");

// Test 6: Non-pointer types are NOT PointeeSized
static_assert(not PointeeSized<int>,
"Failed: int should NOT be PointeeSized, as it is not a pointer");
static_assert(not PointeeSized<float>,
"Failed: float should NOT be PointeeSized, as it is not a pointer");
static_assert(not PointeeSized<void>,
"Failed: void should NOT be PointeeSized, as it is not a pointer");

// Test 7: References are NOT PointeeSized
static_assert(not PointeeSized<int&>,
"Failed: int& should NOT be PointeeSized, as it is not a pointer");
static_assert(not PointeeSized<int&&>,
"Failed: int&& should NOT be PointeeSized, as it is not a pointer");

// Test 8: Arrays are NOT PointeeSized
static_assert(not PointeeSized<int[10]>,
"Failed: int[10] should NOT be PointeeSized, as it is not a pointer");

// Test 9: cv-qualified pointers to complete types are PointeeSized
static_assert(PointeeSized<const int*>, "Failed: const int* should be PointeeSized");
static_assert(PointeeSized<volatile int*>, "Failed: volatile int* should be PointeeSized");
static_assert(PointeeSized<const volatile int*>,
"Failed: const volatile int* should be PointeeSized");
static_assert(PointeeSized<int* const>, "Failed: int* const should be PointeeSized");
static_assert(PointeeSized<int* volatile>, "Failed: int* volatile should be PointeeSized");
static_assert(PointeeSized<int* const volatile>,
"Failed: int* const volatile should be PointeeSized");

// Test 10: Pointer to array is PointeeSized (array has a known size)
static_assert(PointeeSized<int(*)[10]>,
"Failed: int(*)[10] should be PointeeSized, as int[10] has a known size");
static_assert(PointeeSized<char(*)[5]>,
"Failed: char(*)[5] should be PointeeSized, as char[5] has a known size");

// Test 11: Custom complete types
struct Complete
{
    int x;
};

enum class MyEnum
{
    A,
    B,
    C
};

static_assert(PointeeSized<Complete*>, "Failed: Complete* should be PointeeSized");
static_assert(PointeeSized<MyEnum*>, "Failed: MyEnum* should be PointeeSized");

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return not PointeeSized<Incomplete>;
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