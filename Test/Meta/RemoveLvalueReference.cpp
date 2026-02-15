// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Core/Forward.hpp"
#include "Meta/RemoveLvalueReference.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemoveLvalueReference;

// --- Case 1: Lvalue Reference Removal ---
static_assert(Same<RemoveLvalueReference<int&>, int>, "Failed: int& should become int");
static_assert(Same<RemoveLvalueReference<const int&>, const int>,
"Failed: const int& should become const int");

// --- Case 2: Non-Lvalue Types (Should remain unchanged) ---
static_assert(Same<RemoveLvalueReference<int>, int>, "Failed: int should remain int");
static_assert(Same<RemoveLvalueReference<int*>, int*>, "Failed: int* should remain int*");

// --- Case 3: Rvalue Reference Preservation ---
static_assert(Same<RemoveLvalueReference<int&&>, int&&>, "Failed: int&& should remain int&&");

// --- Case 4: Complex Types ---
struct Mock{};

static_assert(Same<RemoveLvalueReference<Mock&>, Mock>, "Failed: Mock& should become Mock");

static_assert(Same<RemoveLvalueReference<void(&)()>, void()>,
"Failed: Function reference should become function type");

[[nodiscard]] auto lvalue(auto&&) noexcept -> bool
{
    return true;
}

[[nodiscard]] auto lvalue(auto&) noexcept -> bool
{
    return false;
}

[[nodiscard]] auto universal(auto&& x) noexcept -> bool
{
    return lvalue($forward(x));
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    int val = 42;
    int& x = val;
    return universal(42) and not universal(x) and universal(RemoveLvalueReference<decltype(x)>(val)
    );
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