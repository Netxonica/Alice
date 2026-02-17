// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Stringify.hpp"

// Consteval string comparator
template<class T> [[nodiscard]] consteval auto str_eq(const T* a, const T* b) noexcept -> bool
{
    while(*a and *b)
        if(*a++ not_eq *b++)
            return false;
    return *a == *b;
}

// Test 1: Empty prefix produces a narrow string literal (const char*)
static_assert(str_eq($stringify(, int), "int"), "Failed: $stringify(, int) should produce \"int\"")
;
static_assert(str_eq($stringify(, float), "float"),
"Failed: $stringify(, float) should produce \"float\"");
static_assert(str_eq($stringify(, double), "double"),
"Failed: $stringify(, double) should produce \"double\"");

// Test 2: Multiple variadic arguments are joined with ", "
static_assert(str_eq($stringify(, int, float), "int, float"),
"Failed: $stringify(, int, float) should produce \"int, float\"");
static_assert(str_eq($stringify(, int, float, double), "int, float, double"),
"Failed: $stringify(, int, float, double) should produce \"int, float, double\"");

// Test 3: Expressions and operators are stringified as written
static_assert(str_eq($stringify(, 1 + 2), "1 + 2"),
"Failed: $stringify(, 1 + 2) should produce \"1 + 2\"");
static_assert(str_eq($stringify(, x == y), "x == y"),
"Failed: $stringify(, x == y) should produce \"x == y\"");
static_assert(str_eq($stringify(, a && b), "a && b"),
"Failed: $stringify(, a && b) should produce \"a && b\"");

// Test 4: Whitespace is collapsed to a single space
static_assert(str_eq($stringify(,    int   ), "int"),
"Failed: $stringify(,    int   ) should collapse whitespace to \"int\"");
static_assert(str_eq($stringify(, int    *   p), "int * p"),
"Failed: $stringify(, int    *   p) should collapse whitespace to \"int * p\"");

// Test 5: L prefix produces a wide string literal (const wchar_t*)
static_assert(str_eq($stringify(L, int), L"int"),
"Failed: $stringify(L, int) should produce L\"int\"");
static_assert(str_eq($stringify(L, int, float), L"int, float"),
"Failed: $stringify(L, int, float) should produce L\"int, float\"");

// Test 6: u8 prefix produces a UTF-8 string literal (const char8_t*)
static_assert(str_eq($stringify(u8, int), u8"int"),
"Failed: $stringify(u8, int) should produce u8\"int\"");
static_assert(str_eq($stringify(u8, int, float), u8"int, float"),
"Failed: $stringify(u8, int, float) should produce u8\"int, float\"");

// Test 7: u prefix produces a UTF-16 string literal (const char16_t*)
static_assert(str_eq($stringify(u, int), u"int"),
"Failed: $stringify(u, int) should produce u\"int\"");
static_assert(str_eq($stringify(u, int, float), u"int, float"),
"Failed: $stringify(u, int, float) should produce u\"int, float\"");

// Test 8: U prefix produces a UTF-32 string literal (const char32_t*)
static_assert(str_eq($stringify(U, int), U"int"),
"Failed: $stringify(U, int) should produce U\"int\"");
static_assert(str_eq($stringify(U, int, float), U"int, float"),
"Failed: $stringify(U, int, float) should produce U\"int, float\"");

// Test 9: Stringifying template syntax preserves angle brackets
static_assert(str_eq($stringify(, MyTemplate<int>), "MyTemplate<int>"),
"Failed: $stringify(, MyTemplate<int>) should produce \"MyTemplate<int>\"");
static_assert(str_eq($stringify(, Pair<int, float>), "Pair<int, float>"),
"Failed: $stringify(, Pair<int, float>) should produce \"Pair<int, float>\"");

// Test 10: Pointer and reference syntax is preserved
static_assert(str_eq($stringify(, int*), "int*"),
"Failed: $stringify(, int*) should produce \"int*\"");
static_assert(str_eq($stringify(, int&), "int&"),
"Failed: $stringify(, int&) should produce \"int&\"");
static_assert(str_eq($stringify(, int&&), "int&&"),
"Failed: $stringify(, int&&) should produce \"int&&\"");

// Test 11: Nested macro arguments are expanded before stringification
#define MY_TYPE double
static_assert(str_eq($stringify(, MY_TYPE), "double"),
"Failed: $stringify(, MY_TYPE) should expand MY_TYPE to \"double\"");
#undef MY_TYPE

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return str_eq("", $stringify(,));
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