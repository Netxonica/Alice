// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/AddLvalueReference.hpp"

using Alice::Trait::Same;
using Alice::Meta::AddLvalueReference;

// --- Basic types acquire lvalue reference ---
static_assert(Same<AddLvalueReference<int>, int&>, "int -> int&");
static_assert(Same<AddLvalueReference<float>, float&>, "float -> float&");
static_assert(Same<AddLvalueReference<double>, double&>, "double -> double&");
static_assert(Same<AddLvalueReference<char>, char&>, "char -> char&");
static_assert(Same<AddLvalueReference<bool>, bool&>, "bool -> bool&");

// --- Pointers acquire lvalue reference ---
static_assert(Same<AddLvalueReference<int*>, int*&>, "int* -> int*&");
static_assert(Same<AddLvalueReference<const int*>, const int*&>, "const int* -> const int*&");

// --- cv-qualified types acquire lvalue reference ---
static_assert(Same<AddLvalueReference<const int>, const int&>, "const int -> const int&");
static_assert(Same<AddLvalueReference<volatile int>, volatile int&>,
"volatile int -> volatile int&");
static_assert(Same<AddLvalueReference<const volatile int>, const volatile int&>,
"cv int -> cv int&");

// --- Reference collapsing: lvalue ref stays lvalue ref ---
static_assert(Same<AddLvalueReference<int&>, int&>, "int& -> int& (collapses)");
static_assert(Same<AddLvalueReference<const int&>, const int&>, "const int& -> const int&");

// --- Reference collapsing: rvalue ref + lvalue = lvalue ref ---
static_assert(Same<AddLvalueReference<int&&>, int&>, "int&& -> int& (collapses)");
static_assert(Same<AddLvalueReference<const int&&>, const int&>, "const int&& -> const int&");

// --- void: cannot form reference, must remain void ---
static_assert(Same<AddLvalueReference<void>, void>, "void -> void (no ref to void)");
static_assert(Same<AddLvalueReference<const void>, const void>, "const void -> const void");

// --- Array types acquire lvalue reference ---
static_assert(Same<AddLvalueReference<int[4]>, int(&)[4]>, "int[4] -> int(&)[4]");
static_assert(Same<AddLvalueReference<int[]>, int(&)[]>, "int[] -> int(&)[]");

// --- Function types acquire lvalue reference ---
static_assert(Same<AddLvalueReference<int(int)>, int(&)(int)>, "fn type -> fn lvalue ref");

// --- User-defined type ---
struct Foo{};

static_assert(Same<AddLvalueReference<Foo>, Foo&>, "Foo -> Foo&");
static_assert(Same<AddLvalueReference<const Foo>, const Foo&>, "const Foo -> const Foo&");
static_assert(Same<AddLvalueReference<Foo&>, Foo&>, "Foo& -> Foo& (collapses)");
static_assert(Same<AddLvalueReference<Foo&&>, Foo&>, "Foo&& -> Foo& (collapses)");

[[nodiscard]] auto function(const int&&) noexcept -> bool
{
    return false;
}

[[nodiscard]] auto function(const int&) noexcept -> bool
{
    return true;
}

struct Incomplete;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    return function(AddLvalueReference<const int>{42}) and not Same<Incomplete, AddLvalueReference<
    Incomplete>>;
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