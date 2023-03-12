# Lab_01_06_04 tests
## Input data
- double xq, yq, xr, yr, xp, yp: _**coordinates of points `q`, `r` and `p`**_;
## Output data
- `0` or `1`: _**`1` if `p` is on the `qr` line segment otherwise `0`**_.
## Positive tests
- Straight line: `y = const`, point is on the line segment;
- Straight line: `y = const`, point isn't on the line segment;
- Straight line: `x = const`, point is on the line segment;
- Straight line: `x = const`, point isn't on the line segment;
- Test with real numbers;
- Test with line segment crossing axes.
## Negative tests
- `xq` is not a number;
- `yq` is not a number;
- `xr` is not a number;
- `yr` is not a number;
- `xp` is not a number;
- `yp` is not a number;
- There is no line segment with given data;
- File is empty.
