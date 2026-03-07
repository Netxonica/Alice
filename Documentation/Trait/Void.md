# `Alice::Trait::Void`

**Header:** `Trait/Void.hpp`  
**Namespace:** `Alice::Trait`  
**Introduced:** `0.0.1` - `07/03/2026`

```cpp
namespace Alice::Trait
{
    template<class Self> concept Void;
}
```

---

## Description

`Alice::Trait::Void` is a concept that is satisfied if and only if `Self` is `void`, ignoring any top-level cv-qualification (`const` and/or `volatile`).

It is the primitive building block for any generic code that must branch on, constrain, or exclude the `void` type. Because `void` is an incomplete type that cannot be instantiated, formed into a reference, or used as a value, correct identification of it — and its cv-qualified variants — is often necessary at the boundary between generic algorithms and I/O, type-erased APIs, or return-type deduction.

---

## Template Parameters

| Parameter | Description                                                    |
| --------- | -------------------------------------------------------------- |
| `Self`    | The type being tested. May be any complete or incomplete type. |

---

## Satisfying Types

The following types satisfy `Void`:

| Type                  | Notes                                                         |
| --------------------- | ------------------------------------------------------------- |
| `void`                | The canonical void type.                                      |
| `const void`          | cv-qualified; `const` is stripped before comparison.          |
| `volatile void`       | cv-qualified; `volatile` is stripped before comparison.       |
| `const volatile void` | cv-qualified; both qualifiers are stripped before comparison. |

---

## Non-Satisfying Types

Any type that is not one of the four variants above does **not** satisfy `Void`. Representative examples:

| Type                                   | Reason                                        |
| -------------------------------------- | --------------------------------------------- |
| `void*`                                | Pointer-to-void is a complete, non-void type. |
| `int`, `float`, `bool`, …              | Fundamental non-void types.                   |
| `int*`, `int&`, `int&&`                | Derived types.                                |
| `int[]`, `int[N]`                      | Array types.                                  |
| User-defined `struct`, `union`, `enum` | Non-void user-defined types.                  |
| `void()`                               | Function type; not the same as `void`.        |
| `void(*)()`                            | Function pointer; not the same as `void`.     |
| Member pointers                        | Not void.                                     |

---

## Usage

### Basic type check

```cpp
#include "Trait/Void.hpp"

static_assert( Alice::Trait::Void<void>);
static_assert( Alice::Trait::Void<const void>);
static_assert(!Alice::Trait::Void<int>);
static_assert(!Alice::Trait::Void<void*>);
```

### Constraining a template

```cpp
#include "Trait/Void.hpp"

// Overload selected only when T is (cv-qualified) void.
template<Alice::Trait::Void T>
void describe() { /* handle void case */ }

// General overload for everything else.
template<class T>
void describe() { /* handle non-void case */ }
```

### Conditional compilation via `if constexpr`

```cpp
#include "Trait/Void.hpp"

template<class T>
void process() {
    if constexpr (Alice::Trait::Void<T>) {
        // T is void — skip value handling.
    } else {
        T value{};
        (void)value;
    }
}
```

---

## Notes

- Because `void` is an incomplete type, no instantiation, sizeof, or alignof expression involving `void` is valid; the concept only identifies the type and makes no attempt to use it as a value type.
- Top-level cv-qualifiers on `void` are semantically meaningless in most contexts (a `const void` function return type is equivalent to `void`), but they are syntactically valid and the concept handles them uniformly.