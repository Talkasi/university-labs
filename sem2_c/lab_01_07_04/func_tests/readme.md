# Lab_01_07_01 tests
## Input data
- double x, eps: _**parameters to compute functions with**_.
## Output data
- double _**absolute_error**_, _**relative_error**_.
## Positive tests
- `x` is zero, 1 element in `s` function is computed;
- Four elements in `s` function are computed;
- Four elements in `s` function are computed, x and eps are different from the previous test;
- Zero elements in `s` function are computed, (first element in `s` - 1 is not computed, it is set by default).
## Negative tests
- `|x|` is bigger than `1` or equal `1`;
- `eps` is a wrong value;
- One of the parameters is not a number;
- File is empty.
