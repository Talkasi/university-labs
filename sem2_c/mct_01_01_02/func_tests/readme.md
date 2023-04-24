# Mct_01_01_02 tests
## Input data
- `x`, `eps` to calculate the functions.
## Output data
- Sum of elements of the numerical sequence in exponential form;
- Function value at point `x`: `f(x) = cos(arcsin(x))`.
## Positive tests
- `x` is close to `1`, `eps` is `10**(-4)`;
- `x` is close to `1`, `eps` is `10**(-8)`;
- `x` is `1`: `f(x)` is zero;
- `x` is `0`: `f(x)` is one;
- `x` is `-1`: `f(x)` is zero;
- `x` is close to `-1`, `eps` is `10**(-8)`;
- `x` is close to `-1`, `eps` is `10**(-4)`;
- `x` is bigger than `1`: `f(x)` is nan;
- `x` is smaller than `-1`: `f(x)` is nan;
- `x` is close to `0`, `eps` is `10**(-20)`;
## Negative tests
- `eps` is less than zero;
- `eps` equals to zero;
- `x` is not a number;
- `eps` is not a number;
- File is empty.
