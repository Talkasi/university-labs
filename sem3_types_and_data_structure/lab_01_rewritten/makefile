CC:=gcc
C_FLAGS:=-Wall -Wextra -Werror -Wfloat-equal

SRC_DIR:=./src
INC_DIR:=./inc
TMP_DIR:=./tmp
TST_DIR:=./tst

$(shell mkdir -p $(TMP_DIR))

.PHONY: test_all
test_all: div_tester.exe
test_all: mul_tester.exe
test_all: in_out_tester.exe
test_all: cmp_tester.exe
test_all: sub_tester.exe
test_all:
	touch $(TMP_DIR)/test_in.txt $(TMP_DIR)/test_out.txt
	python3 $(TST_DIR)/tester.py


./div_tester.exe: $(TMP_DIR)/div_tester_main.o $(TMP_DIR)/big_nums.o
	$(CC) $(C_FLAGS) -I$(INC_DIR) $^ -o $@

./mul_tester.exe: $(TMP_DIR)/mul_tester_main.o $(TMP_DIR)/big_nums.o
	$(CC) $(C_FLAGS) -I$(INC_DIR) $^ -o $@

./in_out_tester.exe: $(TMP_DIR)/in_out_tester_main.o $(TMP_DIR)/big_nums.o
	$(CC) $(C_FLAGS) -I$(INC_DIR) $^ -o $@

./cmp_tester.exe: $(TMP_DIR)/cmp_tester_main.o $(TMP_DIR)/big_nums.o
	$(CC) $(C_FLAGS) -I$(INC_DIR) $^ -o $@

./sub_tester.exe: $(TMP_DIR)/sub_tester_main.o $(TMP_DIR)/big_nums.o
	$(CC) $(C_FLAGS) -I$(INC_DIR) $^ -o $@


$(TMP_DIR)/big_nums.o: $(SRC_DIR)/big_nums.c $(INC_DIR)/big_nums.h 
	$(CC) $(C_FLAGS) -I$(INC_DIR) -c $< -o $@

$(TMP_DIR)/div_tester_main.o: $(TST_DIR)/div_tester_main.c $(INC_DIR)/big_nums.h 
	$(CC) $(C_FLAGS) -I$(INC_DIR) -c $< -o $@

$(TMP_DIR)/mul_tester_main.o: $(TST_DIR)/mul_tester_main.c $(INC_DIR)/big_nums.h 
	$(CC) $(C_FLAGS) -I$(INC_DIR) -c $< -o $@

$(TMP_DIR)/in_out_tester_main.o: $(TST_DIR)/in_out_tester_main.c $(INC_DIR)/big_nums.h 
	$(CC) $(C_FLAGS) -I$(INC_DIR) -c $< -o $@

$(TMP_DIR)/cmp_tester_main.o: $(TST_DIR)/cmp_tester_main.c $(INC_DIR)/big_nums.h 
	$(CC) $(C_FLAGS) -I$(INC_DIR) -c $< -o $@

$(TMP_DIR)/sub_tester_main.o: $(TST_DIR)/sub_tester_main.c $(INC_DIR)/big_nums.h 
	$(CC) $(C_FLAGS) -I$(INC_DIR) -c $< -o $@


.PHONY: clean
clean:
	rm -d $(TMP_DIR)/* *.exe *.out
