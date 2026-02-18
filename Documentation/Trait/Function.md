```css
0.0.1 - 18/02/2026
```

## Concepts

### Alice::Trait::Function

```cpp
namespace Alice::Trait
{
	template<class Self> concept Function;
}
```

Satisfied when `Self` is a possibly reference, `volatile`, and/or `const` qualified function type.

#### Template parameters

- `Self`: The type that will be evaluated. To satisfy this concept, it shouldn't be a pointer or a reference to a function, a lambda, a function call operator overload, nor a member function pointer.