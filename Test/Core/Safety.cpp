// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifdef alice_windows
#include <Windows.h>
#endif
#include "Core/Safety.hpp"

$template_unreliable() void templated_foo(){} // templated unreliable function

// $unreliable also works for declaring a function reference type returning void and taking no
// extra parameters
constexpr void caller(void (&my_unreliable_function) $unreliable())
{
    $unsafe my_unreliable_function $function();
}

template<class T> concept HasConstructed = requires $unreliable(T object) // Also works with requires blocks
{
    object.constructed $function();
};

class UnsafeConstructible
{
    bool m_constructed = false;
public:
    // Unreliable constructor
    constexpr UnsafeConstructible $unreliable() noexcept : m_constructed(true){}

    // Unreliable member function
    constexpr bool constructed $unreliable() const noexcept { return m_constructed; }
};

constexpr void fun2 $unreliable() noexcept{}

// Unreliable free function showcasing how the unsafe context propagates in unreliable functions
constexpr void fun1 $unreliable() noexcept
{
    fun2 $function(); // No need for explicit unsafe blocks, fun1 is an unreliable function and it
                      // already introduces an implicit unsafe block
}

// Unreliable free function
constexpr void foo $unreliable() noexcept{}

// Unreliable free function with parameters
constexpr int compute $unreliable(int x) noexcept
{
    return x * 2;
}

// Safe wrapper that would normally forbid unsafe call
constexpr int safe_computation() noexcept
{
    int result = 0;
    
    // foo $(); // Would be illegal — $unreliable called from safe context
    
    static_assert($safety); // Ok, we're in an implicitly safe context

    return result;
}

[[nodiscard]] constexpr auto alice_test() noexcept -> bool
{
    static_assert($safety); // Ok, we're in an implicitly safe context

    caller(foo); // Ok, foo is an $unreliable function with no extra parameters and returning void,
                                         // which matches the type of my_unreliable_function

    safe_computation(); // Ok, regular call

    // Explicit unsafe region
    $unsafe
    {
        static_assert(not $safety); // Ok, we're not in a safe context

        safe_computation(); // Ok, regular call

        foo $function(); // Ok, we're within an explicit unsafe region, calling the unreliable foo
                         // is allowed

        fun1 $function(); // Ok, we're within an explicit unsafe region, and the unsafety is
                          // propagated to fun2

        templated_foo $template()(); // Ok, can also propagate via templates

        // Test propagation of parameters through $function
        int doubled = compute $function(5);
        if (doubled != 10)
            return false;

        // Test unreliable constructor propagation via $list
        UnsafeConstructible obj $list();
        static_assert(HasConstructed<UnsafeConstructible>); // Ok, UnsafeConstructible has a member
                                                            // function named 'constructed' that is
                                                            // unreliable
        if (not obj.constructed $function())
            return false;

        // Demonstrate lambda capture form with $capture
        auto f = $capture()() { return compute $function(3); };
        if (f() != 6)
            return false;

        // Nested explicit safe region restores restrictions
        $safe
        {
            // compute $function(4); // Would be illegal — $unreliable called from safe context

            safe_computation(); // Ok, regular call

            static_assert($safety); // Ok, we're in a safe context
        }
    }

    return $safety; // Should be equivalent to returning true thanks to the implicit safe context
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