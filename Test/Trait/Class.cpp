// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Trait/Class.hpp"

using Alice::Trait::Class;

[[nodiscard]] auto alice_test() noexcept -> bool
{
    // Positive cases

    struct EmptyStruct{};

    class EmptyClass{};

    struct StructWithMembers
    {
        int x;
        
        void foo(){}
    };

    class ClassWithMembers
    {
        [[maybe_unused]] int x;
        
        void foo(){}
    };

    struct DerivedStruct : EmptyStruct{};

    class DerivedClass : EmptyClass{};

    struct AbstractStruct
    {
        virtual void foo() = 0;
    };

    class AbstractClass
    {
        virtual void foo() = 0;
    };

    static_assert(Class<EmptyStruct>);
    static_assert(Class<EmptyClass>);
    static_assert(Class<StructWithMembers>);
    static_assert(Class<ClassWithMembers>);
    static_assert(Class<DerivedStruct>);
    static_assert(Class<DerivedClass>);
    static_assert(Class<AbstractStruct>);
    static_assert(Class<AbstractClass>);

    // CV-qualified class types

    static_assert(Class<const EmptyStruct>);
    static_assert(Class<volatile EmptyStruct>);
    static_assert(Class<const volatile EmptyStruct>);

    // Negative cases

    static_assert(not Class<int>);
    static_assert(not Class<float>);
    static_assert(not Class<bool>);
    static_assert(not Class<char>);
    static_assert(not Class<int*>);
    static_assert(not Class<int&>);
    static_assert(not Class<int&&>);
    static_assert(not Class<int[]>);
    static_assert(not Class<int[4]>);
    static_assert(not Class<void>);
    static_assert(not Class<decltype(nullptr)>); // nullptr_t

    // Enums and unions are not classes
    
    enum PlainEnum
    {
        A,
        B
    };
    
    enum class ScopedEnum
    {
        A,
        B
    };

    union SomeUnion
    {
        int x;
        
        float y;
    };

    static_assert(not Class<PlainEnum>);
    static_assert(not Class<ScopedEnum>);
    static_assert(not Class<SomeUnion>);

    // Function and function pointer types

    static_assert(not Class<void()>);
    static_assert(not Class<void(*)()>);
    static_assert(not Class<void(&)()>);

    // Member pointer types
    static_assert(not Class<int EmptyStruct::*>);
    static_assert(not Class<void (EmptyStruct::*)()>);

    struct Incomplete;
    return not Class<Incomplete>;
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