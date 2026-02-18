```css
0.0.1 - 18/02/2026
```

## Requirements

- `Meta/RemovePointer.hpp`
- `Trait/Pointer.hpp`
- `Trait/Function.hpp`

## Concepts

### Alice::Trait::PointeeSized

```cpp
namespace Alice::Trait
{
	template<class Self> concept PointeeSized;
}
```

Satisfied when `Self`'s pointee type has a size. Types without a size would be:

- Function types.
- `void`.
- Incomplete types.

#### Template parameters

- `Self`: The pointer type from which the pointee will be evaluated. It must satisfy `Alice::Trait::Pointer`.