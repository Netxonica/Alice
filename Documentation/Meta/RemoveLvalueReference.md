```css
0.0.1 - 07/02/2026
```

## Type aliases

### Alice::Meta::RemoveLvalueReference

```cpp
namespace Alice::Meta
{
	template<class Self> using RemoveLvalueReference;
}
```

If `Self`'s top type is an lvalue reference, returns `Self` with such lvalue reference removed. Otherwise, it returns `Self`.

#### Template parameters

- `Self`: The type to remove the top-most l-value reference from, if any.