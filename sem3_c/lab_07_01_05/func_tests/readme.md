# Lab_07_01_05 tests
## Usage
- app.exe IN_FILE OUT_FILE [f]
* IN_FILE - name of the file with in data;
* OUT_FILE - name of the file where to write the answer;
* f - key for filtering, is optional.
## Positive tests
- filter key is not set, numbers in the file are already sorted;
- filter key is not set, to sort a file the last number should become the first one;
- filter key is not set, to sort a file the first number should become the last one;
- filter key is not set, multiple steps is needed to sort a file;
- filter key is set, each number before the last one should not be removed;
- filter key is set, one number should remain after filtering;
- filter key is set, several numbers should remain after filtering.
## Negative tests
- wrong number of parameters;
- filter key is wrong;
- there is no file with the given IN_FILE name;
- given IN_FILE is empty;
- given IN_FILE doesn't contain numbers, but contain other symbol;
- there are not only numbers in IN_FILE file;
- in the end of the IN_FILE is not a number;
- there are no numbers left after filtering the array.
