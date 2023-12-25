# Lab_06_01 tests
## Usage
- `program FILE FIELD [KEY]`
## Positive tests
- `Test_01`: `KEY` argument is not set, there is one record in the file;
- `Test_02`: `KEY` argument is not set, records in the file are already sorted by all fields;
- `Test_03`: `KEY` argument is not set, records in the file are already sorted by the given field;
- `Test_04`: `KEY` argument is not set, records in the file are not sorted by the given field;
- `Test_05`: `KEY` argument is set, there is one record in the file, and it is suitable;
- `Test_06`: `KEY` argument is set, there is one non-suitable record in the file;
- `Test_07`: `KEY` argument is set, records in the file are already sorted, there aren't suitable records in the file;
- `Test_08`: `KEY` argument is set, records in the file are already sorted, there is one suitable record in the file;
- `Test_09`: `KEY` argument is set, records in the file are already sorted, there are several suitable records in the file;
- `Test_10`: `KEY` argument is set, records in the file are not sorted, there aren't any suitable records in the file;
- `Test_11`: `KEY` argument is set, records in the file are not sorted, there are suitable records in the file.
## Negative tests
- `Test_01`: Number of the parameters is less than needed;
- `Test_02`: Number of the parameters is bigger than needed;
- `Test_03`: Wrong file name;
- `Test_04`: Wrong field name;
- `Test_05`: File is empty;
- `Test_06`: File has wrong number of lines;
- `Test_07`: There are more records in the file than `MAX_NRECORDS`;
- `Test_08`: Wrong year in the file;
- `Test_09`: Wrong year is stored in the key parameter.