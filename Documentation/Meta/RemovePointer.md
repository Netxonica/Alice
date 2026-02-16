```css
	0.0.1 - 16/02/2026
```

## Type aliases

### Alice::Meta:RemovePointer

```cpp
namespace Alice::Meta
{
	template<class Self> using RemovePointer;
}
```

If `Self`'s top type is a possibly `const` and/or `volatile` qualified pointer, returns `Self` with such pointer removed. Otherwise, it returns `Self`.

#### Template parameters

- `Self`: The type to remove the top-most pointer from, if any.