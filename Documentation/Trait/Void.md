```css
0.0.1 - 21/02/2026
```

## Concepts

### Alice::Trait::Void

```cpp
namespace Alice::Trait
{
	template<class Self> concept Void;
}
```

Satisfied when `Self` is a `void` type.

#### Template parameters

- `Self`: The type to be evaluated. To satisfy this concept it must be a possibly `const` and/or `volatile` qualified `void` type.