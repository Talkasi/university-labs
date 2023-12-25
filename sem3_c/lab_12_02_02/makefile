CC := gcc

INC_DIR := inc
OUT_DIR := out
SRC_DIR := src
LIB_DIR := lib
CHECK_DIR := unit_tests

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion
SRC_LIBS := -lm
CHECK_LIBS := -lcheck -lm

$(shell mkdir -p $(OUT_DIR))

CHECK_SUITES := check_init_arr_by_fib.o check_init_by_first_unique.o
CHECK_OBJS := $(addprefix $(OUT_DIR)/, check_main.o $(CHECK_SUITES))
N_CHECK_SUITES := $(words $(CHECK_SUITES))

.PHONY: make_lib
make_lib: $(LIB_DIR)/libarr.so

.PHONY: mem_check_go
mem_check_go: unit_tests_mem_check

$(LIB_DIR)/libarr.so: $(OUT_DIR)/libarr.o 
	gcc -o $@ -shared $<

$(OUT_DIR)/libarr.o: $(LIB_DIR)/libarr.c $(INC_DIR)/libarr.h
	$(CC) $(CFLAGS) -fPIC -I./$(INC_DIR) -c $< -o $@ $(SRC_LIBS)

.PHONY: unit_tests
unit_tests: $(LIB_DIR)/libarr.so unit_tests.exe
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./$(LIB_DIR) \
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) unit_tests.exe

unit_tests.exe: $(CHECK_OBJS)
	$(CC) $(CFLAGS) -I./inc $^ -o $@ $(CHECK_LIBS) -L./$(LIB_DIR) -larr

$(OUT_DIR)/check_main.o: $(CHECK_DIR)/check_main.c $(INC_DIR)/check_suites.h 
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(CHECK_LIBS)

$(OUT_DIR)/check_init_arr_by_fib.o: $(CHECK_DIR)/check_init_arr_by_fib.c $(INC_DIR)/check_suites.h
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(CHECK_LIBS)

$(OUT_DIR)/check_init_by_first_unique.o: $(CHECK_DIR)/check_init_by_first_unique.c $(INC_DIR)/check_suites.h
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(CHECK_LIBS)

.PHONY: unit_tests_mem_check
unit_tests_mem_check: unit_tests.exe
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./$(LIB_DIR) \
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) unit_tests.exe --mem_check

.PHONY: clean
clean: clean_coverage
	$(RM) $(OUT_DIR)/*.o $(OUT_DIR)/*.d *.exe *.lastbuildstate

.PHONY: clean_coverage
clean_coverage:
	$(RM) $(OUT_DIR)/*.gcda $(OUT_DIR)/*.gcno $(OUT_DIR)/*.gcov

.PHONY: clean_global
clean_global: clean
	$(RM) */*.so */*.a

.PHONY: format
format:
	clang-format -i -style=microsoft $(INC_DIR)/*.h ./*/*.c
