```css
0.0.1 - 17/02/2026
```

## Function-like macros

### $stringify

```cpp
#define $stringify(prefix, ...)
```

Generates an string literal with `prefix` as the encoding prefix, and `...` as the content/characters.

#### Function-like parameters

- `prefix`: The optional encoding prefix for the generated string literal. If it's left empty, it will generate an string literal without an encoding prefix.
- `...`: The optional content that will constitute the generated string literal. If it's left empty, it will generate an empty string literal (only the null character will be present).