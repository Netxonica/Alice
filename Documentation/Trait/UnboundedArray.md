```css
0.0.1 - 19/02/2026
```

## Concepts

### Alice::Trait::UnboundedArray

```cpp
namespace Alice::Trait
{
	template<class Self> concept UnboundedArray;
}
```

Satisfied when `Self` is an array type with unknown bounds.

#### Template parameters

- `Self`: The type that will be evaluated. To satisfy this concept, `Self` must be a single-dimensional array type with unknown bounds, or a multi-dimensional array type with its top extent/dimension with unknown bounds.