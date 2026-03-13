# `Alice::Meta::AddLvalueReference`

**Header:** `Meta/AddLvalueReference.hpp`
**Namespace:** `Alice::Meta`
**Introduced:** `0.0.1` - `13/03/2026`

```cpp
namespace Alice::Meta
{
    template<class Self> using AddLvalueReference;
}
```

---

## Description

Returns `Self`'s type with an added lvalue reference. If `Self` was and rvalue reference, it becomes an lvalue reference due to reference collapsing. The lvalue reference won't be added if `Self` is a possibly cv qualified `void` type or type alias.

---

## Template Parameters

| Parameter | Description                                                                      |
| --------- | -------------------------------------------------------------------------------- |
| `Self`    | The type to add the lvalue reference to. May be any complete or incomplete type. |
