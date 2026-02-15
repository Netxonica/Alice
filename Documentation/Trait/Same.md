```css
0.0.1 - 15/02/2026
```

## Concepts

### Alice::Trait::Same

```cpp
namespace Alice::Trait
{
	template<class Self, class T> concept Same;
}
```

Satisfied when `Self` and `T` represent strictly the same type:

- **Strict Identity:** The types must match exactly, including `const`, `volatile`, and/or reference qualifiers.
    
- **Aliases:** Type aliases that resolve to the same underlying type are considered identical.

#### Template parameters

- `Self`: The primary type being evaluated.
- `T`: The target type to compare against.