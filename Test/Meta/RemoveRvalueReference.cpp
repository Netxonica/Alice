// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemoveRvalueReference.hpp"

using Alice::Trait::Same;
using Alice::Meta::RemoveRvalueReference;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Non-references are passed through unchanged

    static_assert(Same<RemoveRvalueReference<int>, int>);
    static_assert(Same<RemoveRvalueReference<const int>, const int>);
    static_assert(Same<RemoveRvalueReference<int*>, int*>);
    static_assert(Same<RemoveRvalueReference<const int*>, const int*>);
    static_assert(Same<RemoveRvalueReference<int* const>, int* const>);
    static_assert(Same<RemoveRvalueReference<void>, void>);

    // Lvalue references are untouched

    static_assert(Same<RemoveRvalueReference<int&>, int&>);
    static_assert(Same<RemoveRvalueReference<const int&>, const int&>);
    static_assert(Same<RemoveRvalueReference<int*&>, int*&>);
    static_assert(Same<RemoveRvalueReference<void*&>, void*&>);

    // Rvalue references have the && stripped, yielding the bare type

    static_assert(Same<RemoveRvalueReference<int&&>, int>);
    static_assert(Same<RemoveRvalueReference<const int&&>, const int>);
    static_assert(Same<RemoveRvalueReference<int*&&>, int*>);
    static_assert(Same<RemoveRvalueReference<void*&&>, void*>);

    // Stripping && from an lvalue-ref-qualified type yields the lvalue ref (not the base type)

    static_assert(Same<RemoveRvalueReference<int&>, int&>);

    struct Incomplete;
    return Same<RemoveRvalueReference<Incomplete&&>, Incomplete>;
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