// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/UnboundedArray.hpp"

using Alice::Trait::UnboundedArray;

// Test 1: Unbounded arrays ARE UnboundedArray
static_assert(UnboundedArray<int[]>, "Failed: int[] should be an UnboundedArray");
static_assert(UnboundedArray<char[]>, "Failed: char[] should be an UnboundedArray");
static_assert(UnboundedArray<float[]>, "Failed: float[] should be an UnboundedArray");
static_assert(UnboundedArray<double[]>, "Failed: double[] should be an UnboundedArray");

// Test 2: Bounded arrays are NOT UnboundedArray
static_assert(not UnboundedArray<int[10]>,
"Failed: int[10] should NOT be an UnboundedArray, it has a known bound");
static_assert(not UnboundedArray<char[5]>,
"Failed: char[5] should NOT be an UnboundedArray, it has a known bound");
static_assert(not UnboundedArray<float[100]>,
"Failed: float[100] should NOT be an UnboundedArray, it has a known bound");
static_assert(not UnboundedArray<int[1]>,
"Failed: int[1] should NOT be an UnboundedArray, it has a known bound");

// Test 3: Non-array types are NOT UnboundedArray
static_assert(not UnboundedArray<int>, "Failed: int should NOT be an UnboundedArray");
static_assert(not UnboundedArray<char>, "Failed: char should NOT be an UnboundedArray");
static_assert(not UnboundedArray<float>, "Failed: float should NOT be an UnboundedArray");
static_assert(not UnboundedArray<void>, "Failed: void should NOT be an UnboundedArray");

// Test 4: Pointers are NOT UnboundedArray
static_assert(not UnboundedArray<int*>, "Failed: int* should NOT be an UnboundedArray");
static_assert(not UnboundedArray<char*>, "Failed: char* should NOT be an UnboundedArray");

// Test 5: Pointers to unbounded arrays are NOT UnboundedArray
static_assert(not UnboundedArray<int(*)[]>,
"Failed: int(*)[] should NOT be an UnboundedArray, it is a pointer");
static_assert(not UnboundedArray<char(*)[]>,
"Failed: char(*)[] should NOT be an UnboundedArray, it is a pointer");

// Test 6: Pointers to bounded arrays are NOT UnboundedArray
static_assert(not UnboundedArray<int(*)[10]>,
"Failed: int(*)[10] should NOT be an UnboundedArray, it is a pointer");
static_assert(not UnboundedArray<char(*)[5]>,
"Failed: char(*)[5] should NOT be an UnboundedArray, it is a pointer");

// Test 7: References to unbounded arrays are NOT UnboundedArray
static_assert(not UnboundedArray<int(&)[]>,
"Failed: int(&)[] should NOT be an UnboundedArray, it is a reference");
static_assert(not UnboundedArray<char(&)[]>,
"Failed: char(&)[] should NOT be an UnboundedArray, it is a reference");

// Test 8: References to bounded arrays are NOT UnboundedArray
static_assert(not UnboundedArray<int(&)[10]>,
"Failed: int(&)[10] should NOT be an UnboundedArray, it is a reference");
static_assert(not UnboundedArray<char(&)[5]>,
"Failed: char(&)[5] should NOT be an UnboundedArray, it is a reference");

// Test 9: cv-qualified unbounded arrays ARE UnboundedArray
static_assert(UnboundedArray<const int[]>, "Failed: const int[] should be an UnboundedArray");
static_assert(UnboundedArray<volatile int[]>, "Failed: volatile int[] should be an UnboundedArray")
;
static_assert(UnboundedArray<const volatile int[]>,
"Failed: const volatile int[] should be an UnboundedArray");

// Test 10: cv-qualified bounded arrays are NOT UnboundedArray
static_assert(not UnboundedArray<const int[10]>,
"Failed: const int[10] should NOT be an UnboundedArray, it has a known bound");
static_assert(not UnboundedArray<volatile int[10]>,
"Failed: volatile int[10] should NOT be an UnboundedArray, it has a known bound");
static_assert(not UnboundedArray<const volatile int[10]>,
"Failed: const volatile int[10] should NOT be an UnboundedArray, it has a known bound");

// Test 11: Multi-dimensional unbounded arrays where the top dimension is unbounded ARE UnboundedArray
static_assert(UnboundedArray<int[][10]>,
"Failed: int[][10] should be an UnboundedArray, first dimension is unbounded");
static_assert(UnboundedArray<char[][5]>,
"Failed: char[][5] should be an UnboundedArray, first dimension is unbounded");
static_assert(UnboundedArray<int[][10][20]>,
"Failed: int[][10][20] should be an UnboundedArray, first dimension is unbounded");

// Test 12: Multi-dimensional bounded arrays are NOT UnboundedArray
static_assert(not UnboundedArray<int[10][10]>,
"Failed: int[10][10] should NOT be an UnboundedArray, first dimension is bounded");
static_assert(not UnboundedArray<char[5][5]>,
"Failed: char[5][5] should NOT be an UnboundedArray, first dimension is bounded");
static_assert(not UnboundedArray<int[10][20][30]>,
"Failed: int[10][20][30] should NOT be an UnboundedArray, first dimension is bounded");

// Test 13: Custom types with unbounded arrays
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

static_assert(UnboundedArray<CustomType[]>, "Failed: CustomType[] should be an UnboundedArray");
static_assert(UnboundedArray<CustomEnum[]>, "Failed: CustomEnum[] should be an UnboundedArray");
static_assert(not UnboundedArray<CustomType[10]>,
"Failed: CustomType[10] should NOT be an UnboundedArray");

// Test 14: References and pointers to custom types are NOT UnboundedArray
static_assert(not UnboundedArray<CustomType&>,
"Failed: CustomType& should NOT be an UnboundedArray");
static_assert(not UnboundedArray<CustomType*>,
"Failed: CustomType* should NOT be an UnboundedArray");

// Test 15: Function types are NOT UnboundedArray
using FuncType = int(int, int);

static_assert(not UnboundedArray<FuncType>, "Failed: function type should NOT be an UnboundedArray"
);
static_assert(not UnboundedArray<FuncType*>,
"Failed: function pointer should NOT be an UnboundedArray");

// Test 16: Arrays of pointers vs pointers to arrays
static_assert(UnboundedArray<int*[]>,
"Failed: int*[] should be an UnboundedArray, it is an unbounded array of pointers");
static_assert(not UnboundedArray<int*[10]>,
"Failed: int*[10] should NOT be an UnboundedArray, it is a bounded array of pointers");

struct Incomplete;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return not UnboundedArray<Incomplete>;
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