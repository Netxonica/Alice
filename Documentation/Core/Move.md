```css
0.0.1 - 07/02/2026
```

## Requirements

- `Meta/RemoveLvalueReference.hpp`


## Function-like macros

### $move

```cpp
#define $move(...)
```

Always returns the result of the expression given by `...` as an xvalue.

#### Function-like macro parameters

- `...`: The expression to compute and move.