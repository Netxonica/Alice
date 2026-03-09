# `Alice::Trait::NullPointer`

**Header:** `Trait/NullPointer.hpp`  
**Namespace:** `Alice::Trait`  
**Introduced:** `0.0.1 - 09/03/2026`

```cpp
namespace Alice::Trait
{
    template<class Self> concept NullPointer;
}
```

---

## Description

`NullPointer` is a **compile-time concept** that is satisfied if and only if `Self` is the type produced by `decltype(nullptr)`, ignoring any top-level _cv_-qualifiers (`const`, `volatile`, or `const volatile`).

---

## Template Parameters

| Parameter | Description                                                                                   |
| --------- | --------------------------------------------------------------------------------------------- |
| `Self`    | The type to inspect. May be any complete or incomplete type, including cv-qualified variants. |

---

## Satisfying Types

The concept is satisfied by exactly the following four types:

| Type                               | Satisfied |
| ---------------------------------- | --------- |
| `decltype(nullptr)`                | ✅         |
| `const decltype(nullptr)`          | ✅         |
| `volatile decltype(nullptr)`       | ✅         |
| `const volatile decltype(nullptr)` | ✅         |

All other types — including pointers, integers, references, arrays, enumerations, class types, and even `decltype(nullptr)*` — do **not** satisfy the concept.

---

## Non-Satisfying Types

| Type                  | Satisfied |
| --------------------- | --------- |
| `void`                | ❌         |
| `int`                 | ❌         |
| `void*`               | ❌         |
| `int*`                | ❌         |
| `decltype(nullptr)*`  | ❌         |
| `decltype(nullptr)&`  | ❌         |
| `int[]`               | ❌         |
| `enum` / `enum class` | ❌         |
| Any class or struct   | ❌         |

---

## Usage Examples

### 1. Concept check with `static_assert`

```cpp
#include "Trait/NullPointer.hpp"

static_assert( Alice::Trait::NullPointer<decltype(nullptr)>);
static_assert( Alice::Trait::NullPointer<const decltype(nullptr)>);
static_assert(!Alice::Trait::NullPointer<int>);
static_assert(!Alice::Trait::NullPointer<void*>);
```

### 2. Constrained function template

```cpp
#include "Trait/NullPointer.hpp"

// Accepts only nullptr_t (cv-qualified or plain).
template<Alice::Trait::NullPointer T>
void accept_null_pointer(T) { /* ... */ }

accept_null_pointer(nullptr);            // OK
// accept_null_pointer(0);              // Error: int does not satisfy NullPointer
// accept_null_pointer((void*)nullptr); // Error: void* does not satisfy NullPointer
```

### 3. Function overload dispatch

```cpp
#include "Trait/NullPointer.hpp"

template<class T>
void process(T arg) requires Alice::Trait::NullPointer<T>
{
    // handle null-pointer semantics
}

template<class T>
void process(T arg)
{
    // general case
}

process(nullptr);  // → NullPointer overload
process(42);       // → general overload
```

### 4. `if constexpr` branch

```cpp
#include "Trait/NullPointer.hpp"

template<class T>
void inspect(T value)
{
    if constexpr (Alice::Trait::NullPointer<T>)
    {
        // T is decltype(nullptr) — handle accordingly
    }
    else
    {
        // T is something else
    }
}
```

---

## Notes

- `decltype(nullptr)` is a distinct, non-pointer type. Although a `decltype(nullptr)` value implicitly converts to any pointer or pointer-to-member type, `nullptr` itself is **not** a pointer type.
- Ref-qualified variants (`decltype(nullptr)&`, `decltype(nullptr)&&`) do **not** satisfy the concept.