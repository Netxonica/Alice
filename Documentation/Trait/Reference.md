```css
0.0.1 - 21/02/2026
```

## Concepts

### Alice::Trait::Reference

```cpp
namespace Alice::Trait
{
	template<class Self> concept Reference;
}
```

Satisfied when `Self` is a reference type.

#### Template parameters

- `Self`: The type that will be evaluated. To satisfy this concept, `Self` must be an lvalue or rvalue reference.