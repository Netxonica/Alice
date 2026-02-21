// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Void.hpp"

using Alice::Trait::Void;

// Test 1: void IS Void
static_assert(Void<void>, "Failed: void should be Void");

// Test 2: cv-qualified void IS Void
static_assert(Void<const void>, "Failed: const void should be Void");
static_assert(Void<volatile void>, "Failed: volatile void should be Void");
static_assert(Void<const volatile void>, "Failed: const volatile void should be Void");

// Test 3: Fundamental types are NOT Void
static_assert(not Void<int>, "Failed: int should NOT be Void");
static_assert(not Void<char>, "Failed: char should NOT be Void");
static_assert(not Void<float>, "Failed: float should NOT be Void");
static_assert(not Void<double>, "Failed: double should NOT be Void");
static_assert(not Void<bool>, "Failed: bool should NOT be Void");

// Test 4: Pointers to void are NOT Void (they are pointer types)
static_assert(not Void<void*>, "Failed: void* should NOT be Void, it is a pointer");
static_assert(not Void<const void*>, "Failed: const void* should NOT be Void, it is a pointer");
static_assert(not Void<volatile void*>,
"Failed: volatile void* should NOT be Void, it is a pointer");
static_assert(not Void<const volatile void*>,
"Failed: const volatile void* should NOT be Void, it is a pointer");

// Test 5: Pointers to pointers to void are NOT Void
static_assert(not Void<void**>, "Failed: void** should NOT be Void, it is a pointer");
static_assert(not Void<const void**>, "Failed: const void** should NOT be Void, it is a pointer");

// Test 6: Other pointer types are NOT Void
static_assert(not Void<int*>, "Failed: int* should NOT be Void");
static_assert(not Void<char*>, "Failed: char* should NOT be Void");

// Test 7: References are NOT Void (note: references to void are ill-formed)
static_assert(not Void<int&>, "Failed: int& should NOT be Void");
static_assert(not Void<int&&>, "Failed: int&& should NOT be Void");
static_assert(not Void<const int&>, "Failed: const int& should NOT be Void");

// Test 8: Arrays are NOT Void
static_assert(not Void<int[10]>, "Failed: int[10] should NOT be Void");
static_assert(not Void<char[]>, "Failed: char[] should NOT be Void");

// Test 9: Function types are NOT Void
using FuncType = int(int, int);

using VoidFunc = void();

static_assert(not Void<FuncType>, "Failed: function type int(int, int) should NOT be Void");
static_assert(not Void<VoidFunc>,
"Failed: function type void() should NOT be Void, it returns void but is not void");

// Test 10: Function pointers are NOT Void
static_assert(not Void<FuncType*>, "Failed: FuncType* should NOT be Void");
static_assert(not Void<VoidFunc*>, "Failed: VoidFunc* should NOT be Void");
static_assert(not Void<void(*)()>, "Failed: void(*)() should NOT be Void, it is a function pointer"
);

// Test 11: Custom types are NOT Void
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

static_assert(not Void<CustomType>, "Failed: CustomType should NOT be Void");
static_assert(not Void<CustomEnum>, "Failed: CustomEnum should NOT be Void");

// Test 12: Pointers to custom types are NOT Void
static_assert(not Void<CustomType*>, "Failed: CustomType* should NOT be Void");
static_assert(not Void<CustomEnum*>, "Failed: CustomEnum* should NOT be Void");

// Test 13: Character types are NOT Void
static_assert(not Void<char8_t>, "Failed: char8_t should NOT be Void");
static_assert(not Void<char16_t>, "Failed: char16_t should NOT be Void");
static_assert(not Void<char32_t>, "Failed: char32_t should NOT be Void");
static_assert(not Void<wchar_t>, "Failed: wchar_t should NOT be Void");

// Test 14: Integer types of various sizes are NOT Void
static_assert(not Void<short>, "Failed: short should NOT be Void");
static_assert(not Void<long>, "Failed: long should NOT be Void");
static_assert(not Void<long long>, "Failed: long long should NOT be Void");

// Test 15: cv-qualified non-void types are NOT Void
static_assert(not Void<const int>, "Failed: const int should NOT be Void");
static_assert(not Void<volatile int>, "Failed: volatile int should NOT be Void");
static_assert(not Void<const volatile int>, "Failed: const volatile int should NOT be Void");

struct Incomplete;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return not Void<Incomplete>;
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