// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/NullPointer.hpp"
#include "Trait/NullPointer.hpp"

using Alice::Trait::NullPointer;

// ===========================================================================
// Compile-time correctness tests (static_assert)
// ===========================================================================

// --- Identity: Alice::NullPointer must be exactly decltype(nullptr) ----------

static_assert(NullPointer<Alice::NullPointer>,
"Alice::NullPointer must be the same type as decltype(nullptr)");

// --- cv-qualified aliases must remain the same underlying type --------------

static_assert(NullPointer<const Alice::NullPointer>,
"const Alice::NullPointer must be the same type as decltype(nullptr)");
static_assert(NullPointer<volatile Alice::NullPointer>,
"volatile Alice::NullPointer must be the same type as decltype(nullptr)");
static_assert(NullPointer<const volatile Alice::NullPointer>,
"const volatile Alice::NullPointer must be the same type as decltype(nullptr)");

// --- Size and alignment must match decltype(nullptr) ------------------------

static_assert(sizeof(Alice::NullPointer) == sizeof(decltype(nullptr)),
"sizeof(Alice::NullPointer) must equal sizeof(decltype(nullptr))");
static_assert(alignof(Alice::NullPointer) == alignof(decltype(nullptr)),
"alignof(Alice::NullPointer) must equal alignof(decltype(nullptr))");

// ===========================================================================
// Runtime tests: concept used as a constraint in function overloads
// ===========================================================================

// Returns 1 when the argument is a null pointer, 0 otherwise.
[[nodiscard]] constexpr auto dispatch(NullPointer auto) noexcept -> bool
{
    return true;
}

[[nodiscard]] constexpr auto dispatch(auto) noexcept -> bool
{
    return false;
}

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Typed nullptr variable
    Alice::NullPointer np{};
    if(not dispatch(np))
        return false;

    // nullptr literal  → should pick the NullPointer overload
    np = nullptr;
    if(not dispatch(np))
        return false;

    return true;
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