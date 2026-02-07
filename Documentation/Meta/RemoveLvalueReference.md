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

if `Self` is an l-value reference type, returns `Self` without the top-most l-value reference. Otherwise, returns `Self`.

#### Template parameters

- `Self`: The type to remove the top-most l-value reference from, if any.