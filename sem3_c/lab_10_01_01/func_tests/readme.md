# Lab_10_01 tests
## Usage
- `program IN_FILE OUT_FILE`
## Positive tests
- There is information about only one car in the IN_FILE;
- There is information about two cars in the IN_FILE;
- There is information about three cars in the IN_FILE;
- There is no duplicates of the first car's model in the IN_FILE, list is sorted, there are more than 2 nodes;
- There is no duplicates of the first car's model in the IN_FILE, list is unsorted, there are more than 2 nodes;
- There is a duplicate of the first car's model in the IN_FILE, list is sorted, there are more than 2 nodes;
- There is a duplicate of the first car's model in the IN_FILE, list is unsorted, there are more than 2 nodes;
## Negative tests
- Number of arguments is less than expected;
- Number of arguments is bigger than expected;
- Unable to open IN_FILE;
- IN_FILE is empty;
- Wrong data in the IN_FILE.
