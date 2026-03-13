// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/AddRvalueReference.hpp"

using Alice::Trait::Same;
using Alice::Meta::AddRvalueReference;

// --- Basic types acquire rvalue reference ---
static_assert(Same<AddRvalueReference<int>, int&&>, "int -> int&&");
static_assert(Same<AddRvalueReference<float>, float&&>, "float -> float&&");
static_assert(Same<AddRvalueReference<double>, double&&>, "double -> double&&");
static_assert(Same<AddRvalueReference<char>, char&&>, "char -> char&&");
static_assert(Same<AddRvalueReference<bool>, bool&&>, "bool -> bool&&");

// --- Pointers acquire rvalue reference ---
static_assert(Same<AddRvalueReference<int*>, int*&&>, "int* -> int*&&");
static_assert(Same<AddRvalueReference<const int*>, const int*&&>, "const int* -> const int*&&");

// --- cv-qualified types acquire rvalue reference ---
static_assert(Same<AddRvalueReference<const int>, const int&&>, "const int -> const int&&");
static_assert(Same<AddRvalueReference<volatile int>, volatile int&&>,
"volatile int -> volatile int&&");
static_assert(Same<AddRvalueReference<const volatile int>, const volatile int&&>,
"cv int -> cv int&&");

// --- Reference collapsing: lvalue ref + rvalue = lvalue ref ---
static_assert(Same<AddRvalueReference<int&>, int&>, "int& -> int& (collapses)");
static_assert(Same<AddRvalueReference<const int&>, const int&>,
"const int& -> const int& (collapses)");
static_assert(Same<AddRvalueReference<volatile int&>, volatile int&>,
"volatile int& -> volatile int& (collapses)");

// --- Reference collapsing: rvalue ref stays rvalue ref ---
static_assert(Same<AddRvalueReference<int&&>, int&&>, "int&& -> int&& (collapses)");
static_assert(Same<AddRvalueReference<const int&&>, const int&&>, "const int&& -> const int&&");

// --- void: cannot form reference, must remain void ---
static_assert(Same<AddRvalueReference<void>, void>, "void -> void (no ref to void)");
static_assert(Same<AddRvalueReference<const void>, const void>, "const void -> const void");

// --- Array types acquire rvalue reference ---
static_assert(Same<AddRvalueReference<int[4]>, int(&&)[4]>, "int[4] -> int(&&)[4]");
static_assert(Same<AddRvalueReference<int[]>, int(&&)[]>, "int[] -> int(&&)[]");

// --- Function types acquire rvalue reference ---
static_assert(Same<AddRvalueReference<int(int)>, int(&&)(int)>, "fn type -> fn rvalue ref");

// --- User-defined types ---
struct Foo{};

static_assert(Same<AddRvalueReference<Foo>, Foo&&>, "Foo -> Foo&&");
static_assert(Same<AddRvalueReference<const Foo>, const Foo&&>, "const Foo -> const Foo&&");
static_assert(Same<AddRvalueReference<Foo&>, Foo&>, "Foo& -> Foo& (collapses)");
static_assert(Same<AddRvalueReference<Foo&&>, Foo&&>, "Foo&& -> Foo&&");

[[nodiscard]] auto function(const int&&) noexcept -> bool
{
    return true;
}

[[nodiscard]] auto function(const int&) noexcept -> bool
{
    return false;
}

struct Incomplete;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return function(AddRvalueReference<const int>{42}) and not Same<AddRvalueReference<Incomplete>,
    Incomplete>;
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