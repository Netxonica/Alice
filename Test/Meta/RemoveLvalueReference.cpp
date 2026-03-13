// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemoveLvalueReference.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemoveLvalueReference;

// --- Non-reference types are unchanged ---
static_assert(Same<RemoveLvalueReference<int>, int>, "int -> int");
static_assert(Same<RemoveLvalueReference<float>, float>, "float -> float");
static_assert(Same<RemoveLvalueReference<double>, double>, "double -> double");
static_assert(Same<RemoveLvalueReference<char>, char>, "char -> char");
static_assert(Same<RemoveLvalueReference<bool>, bool>, "bool -> bool");
static_assert(Same<RemoveLvalueReference<void>, void>, "void -> void");

// --- Lvalue reference is stripped ---
static_assert(Same<RemoveLvalueReference<int&>, int>, "int& -> int");
static_assert(Same<RemoveLvalueReference<float&>, float>, "float& -> float");
static_assert(Same<RemoveLvalueReference<double&>, double>, "double& -> double");
static_assert(Same<RemoveLvalueReference<char&>, char>, "char& -> char");
static_assert(Same<RemoveLvalueReference<bool&>, bool>, "bool& -> bool");

// --- Rvalue reference is NOT stripped ---
static_assert(Same<RemoveLvalueReference<int&&>, int&&>, "int&& -> int&&");
static_assert(Same<RemoveLvalueReference<float&&>, float&&>, "float&& -> float&&");
static_assert(Same<RemoveLvalueReference<const int&&>, const int&&>, "const int&& -> const int&&");

// --- cv-qualification is preserved ---
static_assert(Same<RemoveLvalueReference<const int>, const int>, "const int -> const int");
static_assert(Same<RemoveLvalueReference<volatile int>, volatile int>,
"volatile int -> volatile int");
static_assert(Same<RemoveLvalueReference<const volatile int>, const volatile int>,
"cv int -> cv int");
static_assert(Same<RemoveLvalueReference<const int&>, const int>, "const int& -> const int");
static_assert(Same<RemoveLvalueReference<volatile int&>, volatile int>,
"volatile int& -> volatile int");
static_assert(Same<RemoveLvalueReference<const volatile int&>, const volatile int>,
"cv int& -> cv int");

// --- Pointer types are unchanged ---
static_assert(Same<RemoveLvalueReference<int*>, int*>, "int* -> int*");
static_assert(Same<RemoveLvalueReference<const int*>, const int*>, "const int* -> const int*");
static_assert(Same<RemoveLvalueReference<int**>, int**>, "int** -> int**");
static_assert(Same<RemoveLvalueReference<int*&>, int*>, "int*& -> int*");

// --- Array types ---
static_assert(Same<RemoveLvalueReference<int[4]>, int[4]>, "int[4] -> int[4]");
static_assert(Same<RemoveLvalueReference<int(&)[4]>, int[4]>, "int(&)[4] -> int[4]");
static_assert(Same<RemoveLvalueReference<int(&)[]>, int[]>, "int(&)[] -> int[]");

// --- Function types ---
static_assert(Same<RemoveLvalueReference<int(int)>, int(int)>, "fn -> fn");
static_assert(Same<RemoveLvalueReference<int(&)(int)>, int(int)>, "fn lvalue ref -> fn");

// --- User-defined types ---
struct Foo{};

static_assert(Same<RemoveLvalueReference<Foo>, Foo>, "Foo -> Foo");
static_assert(Same<RemoveLvalueReference<Foo&>, Foo>, "Foo& -> Foo");
static_assert(Same<RemoveLvalueReference<const Foo&>, const Foo>, "const Foo& -> const Foo");
static_assert(Same<RemoveLvalueReference<Foo&&>, Foo&&>, "Foo&& -> Foo&&");

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
    return function(RemoveLvalueReference<const int&>{42}) and Same<RemoveLvalueReference<
    Incomplete&>, Incomplete>;
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