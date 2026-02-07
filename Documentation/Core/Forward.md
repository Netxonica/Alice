```css
0.0.1 - 07/02/2026
```

## Function-like macros

### $forward

```cpp
#define $forward(...)
```

Returns the result of the expression given by `...` and preserves the value category, except that prvalues become xvalues.

#### Function-like macro parameters

- `...`: The expression to compute and forward.