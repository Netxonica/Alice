# `Alice::NullPointer`

**Header:** `Core/NullPointer.hpp`  
**Namespace:** `Alice`  
**Introduced:** `0.0.1` - `09/03/2026`

```cpp
namespace Alice
{
    using NullPointer;
}
```

---

## Description

`NullPointer` is a **type alias** for the unique type of the `nullptr` prvalue literal.

The alias exists to give null-pointer semantics a named, discoverable identity, enabling consistent use in function signatures, template constraints, variable declarations, and documentation without repeating the verbose `decltype(nullptr)` spelling throughout a codebase.

---

## Type Properties

| Property                                          | Value                                                            |
| ------------------------------------------------- | ---------------------------------------------------------------- |
| `sizeof(Alice::NullPointer)`                      | Implementation-defined; equals `sizeof(void*)` on most platforms |
| `alignof(Alice::NullPointer)`                     | Same as `alignof(void*)` on most platforms                       |
| Is a pointer type                                 | No                                                               |
| Is a class type                                   | No                                                               |
| Is a scalar type                                  | Yes                                                              |
| Implicitly converts to any pointer type           | Yes                                                              |
| Implicitly converts to any pointer-to-member type | Yes                                                              |
| Default-initialized value                         | `nullptr`                                                        |

---

## Usage Examples

### 1. Variable declaration

```cpp
#include "Core/NullPointer.hpp"

Alice::NullPointer np = nullptr;    // plain
const Alice::NullPointer cnp = nullptr; // const-qualified
```

### 2. Function parameter and return type

```cpp
#include "Core/NullPointer.hpp"

// Accept only the null-pointer type.
void register_sentinel(Alice::NullPointer);

// Return the canonical null-pointer value.
Alice::NullPointer make_null() noexcept { return nullptr; }
```

### 3. Function overloading

```cpp
#include "Core/NullPointer.hpp"

void process(Alice::NullPointer);   // null-pointer sentinel path
void process(int*);                 // general pointer path
void process(int);                  // integer path

process(nullptr);           // → Alice::NullPointer overload
process(static_cast<int*>(nullptr)); // → int* overload
process(0);                 // → int overload
```

### 4. Template type check

```cpp
#include "alice/null_pointer.hpp"

template<class T>
constexpr bool is_null_pointer_type =
    __is_same(__remove_cv(T), Alice::NullPointer);

static_assert( is_null_pointer_type<Alice::NullPointer>);
static_assert( is_null_pointer_type<const Alice::NullPointer>);
static_assert(!is_null_pointer_type<void*>);
static_assert(!is_null_pointer_type<int>);
```

### 5. Use alongside `Alice::Trait::NullPointer`

`Alice::NullPointer` (type alias) and `Alice::Trait::NullPointer` (concept) are complementary:

```cpp
#include "Core/NullPointer.hpp"
#include "Trait/NullPointer.hpp"

// The alias names the type; the concept constrains templates.
template<Alice::Trait::NullPointer T>
void accept(T) { /* T is guaranteed to be Alice::NullPointer */ }

accept(Alice::NullPointer{});   // OK
// accept(0);                   // Error: int does not satisfy NullPointer
```

---

## Notes

- `Alice::NullPointer` is **not** a pointer type, it is a distinct scalar type whose only value converts to a null pointer constant. It can, however, be implicitly converted to any pointer type.
- `Alice::NullPointer*` (pointer _to_ `Alice::NullPointer`) is a different, unrelated type and does not represent a null pointer.
- A value-initialization and zero-initialization yields `nullptr` in this type.