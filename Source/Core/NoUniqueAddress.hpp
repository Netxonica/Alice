// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_core_no_unique_address
#define alice_header_guard_core_no_unique_address

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#elifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wdollar-in-identifier-extension"
#endif

/**
 * @brief Correct and portable no_unique_address attribute.
 */
#ifdef _MSC_VER
#define $no_unique_address msvc::no_unique_address
#else
#define $no_unique_address no_unique_address
#endif

#endif
#endif