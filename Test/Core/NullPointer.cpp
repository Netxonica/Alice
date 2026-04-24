// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/NullPointer.hpp"

using Alice::NullPointer;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ═══════════════════════════════════════════════════════════════════════════════
    // 1. A NullPointer value equals nullptr (and symmetrically)
    // ═══════════════════════════════════════════════════════════════════════════════

    constexpr NullPointer null_val = nullptr;

    static_assert(null_val == nullptr, "NullPointer value must equal nullptr");
    static_assert(nullptr == null_val, "nullptr must equal NullPointer value (symmetric)");

    // ═══════════════════════════════════════════════════════════════════════════════
    // 2. Inequality is the exact complement
    // ═══════════════════════════════════════════════════════════════════════════════

    static_assert(not(null_val not_eq nullptr), "NullPointer must not be != nullptr");
    static_assert(not(nullptr not_eq null_val), "nullptr must not be != NullPointer (symmetric)");

    // ═══════════════════════════════════════════════════════════════════════════════
    // 3. Reflexive equality
    // ═══════════════════════════════════════════════════════════════════════════════

    static_assert(null_val == null_val, "NullPointer value must equal itself");

    // ═══════════════════════════════════════════════════════════════════════════════
    // 4. Converts to a null raw pointer
    // ═══════════════════════════════════════════════════════════════════════════════

    constexpr int* p_int = null_val;
    constexpr void* p_void = null_val;
    constexpr const int* p_cint = null_val;
    constexpr const char* p_cchar = null_val;

    static_assert(p_int == nullptr, "int* from NullPointer must be null");
    static_assert(p_void == nullptr, "void* from NullPointer must be null");
    static_assert(p_cint == nullptr, "const int* from NullPointer must be null");
    static_assert(p_cchar == nullptr, "const char* from NullPointer must be null");

    // ═══════════════════════════════════════════════════════════════════════════════
    // 5. Converts to a null pointer-to-member
    // ═══════════════════════════════════════════════════════════════════════════════

    struct Probe
    {
        int data;
        
        void fn(){}
    };

    constexpr decltype(&Probe::data) pm_data = null_val;
    constexpr decltype(&Probe::fn) pm_fn = null_val;

    static_assert(pm_data == nullptr, "pointer-to-data-member from NullPointer must be null");
    static_assert(pm_fn == nullptr, "pointer-to-member-function from NullPointer must be null");

    return not static_cast<bool>(NullPointer{nullptr});
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