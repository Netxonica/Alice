```css
0.0.1 - 16/02/2026
```

## Concepts

### Alice::Trait::Pointer

```cpp
namespace Alice::Trait
{
	template<class Self> concept Pointer;
}
```

Satisfied when `Self` is a possibly `const` and/or `volatile` qualified pointer type.

#### Template parameters

- `Self`: The type to be evaluated against.