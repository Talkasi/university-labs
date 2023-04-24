# Mct_01_02_02 tests
## Input data
- Number of elements in an array `n`. Should be bigger than `0` and less than `1025`;
- Number `n` integer elements of an array;
- `number` to insert after each two-digit element.
## Output data
- Аn array with the square elements from the given array, and with a `number` inserted after each two-digit element;
## Positive tests
- Length of the given array is `1`, element is not square or two-digit;
- Length of the given array is `1`, element is two-digit non-square;
- Length of the given array is `1`, element is two-digit square;
- Length of the given array is `1`, element is one-digit square;
- There are ten two-digit elements in the given array, length of the array is ten;
- There aren't square elements in the given array;
- There are square elements in the given array, but there aren't two-digit elements;
- Number to insert is negative.
## Negative tests
- Number of elements of the given array is negative;
- Number of elements of the given array is zero;
- Number of elements of the given array is bigger than 1024;
- There are fewer elements in the given array than `n`;
- `number` to insert is not a number;
- File is empty.
