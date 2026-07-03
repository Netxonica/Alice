// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/ImplicitLifetime.hpp"

using Alice::Trait::ImplicitLifetime;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // ─────────────────────────────────────────────────────────────────────────────
    // Fixtures
    // ─────────────────────────────────────────────────────────────────────────────

    // Aggregate types (no user-provided ctors or dtor)
    
    struct EmptyAggregate{};

    struct PlainAggregate
    {
        int x;
        
        float y;
    };

    struct NestedAggregate
    {
        PlainAggregate inner;
        
        int z;
    };

    // Non-aggregate; both special members are explicitly defaulted.
    // Satisfies [class.prop] (3.2): trivial eligible ctor + trivial dtor.

    struct ExplicitlyDefaulted
    {
        ExplicitlyDefaulted() = default;

        ~ExplicitlyDefaulted() = default;

        int value;
    };

    // Non-aggregate; the only declared constructor is user-provided.
    // The compiler suppresses the implicit default constructor, and with the deleted copy ctor,
    // no trivial constructor exists → fails both clauses of [class.prop].

    struct UserProvidedCtor
    {
        UserProvidedCtor(const UserProvidedCtor&) = delete;

        UserProvidedCtor(int v) : value{v}{}
        
        int value;
    };

    // IS an aggregate (no user-provided constructors), but the destructor IS
    // user-provided → fails [class.prop] (3.1).
    // The implicit default constructor is trivial, but the destructor is not,
    // so (3.2) also fails.

    struct UserProvidedDtor
    {
        ~UserProvidedDtor()
        {
            /* side-effect */
        }
    };

    // Virtual method: not an aggregate, and the vtable machinery makes both the
    // implicit default constructor and the implicit destructor non-trivial →
    // fails both clauses.

    struct HasVirtualMethod
    {
        virtual void foo(){}

        virtual ~HasVirtualMethod(){}
    };

    // Same disqualifiers as HasVirtualMethod.

    struct HasVirtualDtor
    {
        virtual ~HasVirtualDtor(){}
    };

    enum PlainEnum
    {
        Red,
        Green,
        Blue
    };

    enum class ScopedEnum : int
    {
        X,
        Y,
        Z
    };

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: scalar types (all pointer, arithmetic, and enumeration types)
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(ImplicitLifetime<bool>);
    static_assert(ImplicitLifetime<char>);
    static_assert(ImplicitLifetime<int>);
    static_assert(ImplicitLifetime<unsigned int>);
    static_assert(ImplicitLifetime<long long>);
    static_assert(ImplicitLifetime<float>);
    static_assert(ImplicitLifetime<double>);
    static_assert(ImplicitLifetime<long double>);

    // cv-qualifiers do not affect implicit-lifetime status

    static_assert(ImplicitLifetime<const int>);
    static_assert(ImplicitLifetime<volatile float>);
    static_assert(ImplicitLifetime<const volatile double>);

    // Pointer types are scalar

    static_assert(ImplicitLifetime<int *>);
    static_assert(ImplicitLifetime<void *>);
    static_assert(ImplicitLifetime<const int *>);
    static_assert(ImplicitLifetime<decltype(nullptr)>);  // nullptr_t is a scalar type

    // Member-object pointer is scalar

    static_assert(ImplicitLifetime<int PlainAggregate::*>);

    // Enum types (both unscoped and scoped) are scalar

    static_assert(ImplicitLifetime<PlainEnum>);
    static_assert(ImplicitLifetime<ScopedEnum>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: array types
    // ─────────────────────────────────────────────────────────────────────────────

    static_assert(ImplicitLifetime<int[4]>);
    static_assert(ImplicitLifetime<PlainAggregate[2]>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Positive: implicit-lifetime class types
    // ─────────────────────────────────────────────────────────────────────────────

    // Aggregates with a non-user-provided destructor — satisfies [class.prop] (3.1)

    static_assert(ImplicitLifetime<EmptyAggregate>);
    static_assert(ImplicitLifetime<PlainAggregate>);
    static_assert(ImplicitLifetime<NestedAggregate>);

    // cv-qualification does not strip implicit-lifetime status from a class type

    static_assert(ImplicitLifetime<const PlainAggregate>);
    static_assert(ImplicitLifetime<const EmptyAggregate>);

    // Non-aggregate; satisfies [class.prop] (3.2): trivial eligible ctor + trivial dtor

    static_assert(ImplicitLifetime<ExplicitlyDefaulted>);

    // ─────────────────────────────────────────────────────────────────────────────
    // Negative: types that do NOT satisfy ImplicitLifetime
    // ─────────────────────────────────────────────────────────────────────────────

    // No trivial constructor path exists (user-provided is the only one)

    static_assert(not ImplicitLifetime<UserProvidedCtor>);

    // Aggregate, but user-provided destructor disqualifies (3.1) and the
    // non-trivial dtor disqualifies (3.2)

    static_assert(not ImplicitLifetime<UserProvidedDtor>);

    // Virtual dispatch requires non-trivial ctor/dtor — fails both clauses

    static_assert(not ImplicitLifetime<HasVirtualMethod>);
    static_assert(not ImplicitLifetime<HasVirtualDtor>);

    struct Incomplete;
    return not ImplicitLifetime<Incomplete>;
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