CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
SRC_LIBS := -lm
CHECK_LIBS := -lcheck -lm

INC_DIR := inc
OUT_DIR := out
SRC_DIR := src
CHECK_DIR := unit_tests

$(shell mkdir -p $(OUT_DIR))

SRC_OBJS := $(OUT_DIR)/matrix.o $(OUT_DIR)/main.o
OBJS_FOR_CHECK := $(OUT_DIR)/matrix.o
CHECK_SUITES := check_square_by_add.o check_square_by_del.o check_raise_matrix.o
CHECK_OBJS := $(addprefix $(OUT_DIR)/, check_main.o check_tools.o $(CHECK_SUITES))
N_CHECK_SUITES := $(words $(CHECK_SUITES))

SRCS := $(wildcard $(SRC_DIR)/*.c)
CHECK_SRCS := $(wildcard $(CHECK_DIR)/*.c)

.PHONY: debug
debug: CFLAGS += -g3 --coverage
debug: debug.lastbuildstate | app.exe

.PHONY: release
release: CFLAGS += -DNDEBUG -g0 -O3
release: release.lastbuildstate | app.exe

%.lastbuildstate:
	make clean
	touch $@

app.exe: $(SRC_OBJS)
	$(CC) $(CFLAGS) -I./inc $^ -o $@ $(SRC_LIBS)

unit_tests.exe: $(CHECK_OBJS) $(OBJS_FOR_CHECK)
	$(CC) $(CFLAGS) -I./inc $^ -o $@ $(CHECK_LIBS)


$(OUT_DIR)/matrix.o: $(SRC_DIR)/matrix.c $(INC_DIR)/matrix.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)

$(OUT_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/matrix.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)


$(OUT_DIR)/check_main.o: $(CHECK_DIR)/check_main.c $(INC_DIR)/check_raise_matrix.h $(INC_DIR)/check_square_by_add.h $(INC_DIR)/check_square_by_del.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)

$(OUT_DIR)/check_raise_matrix.o: $(CHECK_DIR)/check_raise_matrix.c $(INC_DIR)/check_raise_matrix.h $(INC_DIR)/check_tools.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)

$(OUT_DIR)/check_square_by_add.o: $(CHECK_DIR)/check_square_by_add.c $(INC_DIR)/check_square_by_add.h $(INC_DIR)/check_tools.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)

$(OUT_DIR)/check_square_by_del.o: $(CHECK_DIR)/check_square_by_del.c $(INC_DIR)/check_square_by_del.h $(INC_DIR)/check_tools.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)

$(OUT_DIR)/check_tools.o: $(CHECK_DIR)/check_tools.c $(INC_DIR)/check_tools.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)


.PHONY: func_tests
func_tests: debug
	./func_tests/scripts/func_tests.sh
	gcov -r $(SRC_OBJS) -o $(OUT_DIR)
	mv *.gcov $(OUT_DIR)

.PHONY: unit_tests
unit_tests: CFLAGS += -g3 --coverage
unit_tests: unit_tests.exe
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES)
	gcov -r $(CHECK_OBJS) $(OBJS_FOR_CHECK) -o $(OUT_DIR)
	mv *.gcov $(OUT_DIR)

.PHONY: mem_check_func_tests
mem_check_func_tests: debug
	./func_tests/scripts/func_tests.sh --mem_check
	gcov -r $(SRC_OBJS) -o $(OUT_DIR)
	mv *.gcov $(OUT_DIR)

.PHONY: mem_check_unit_tests
mem_check_unit_tests: CFLAGS += -g3 --coverage
mem_check_unit_tests: unit_tests.exe
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) --mem_check
	gcov -r $(CHECK_OBJS) $(OBJS_FOR_CHECK) -o $(OUT_DIR)
	mv *.gcov $(OUT_DIR)

.PHONY: go
go: func_tests
go: unit_tests

.PHONY: mem_check_go
mem_check_go: mem_check_func_tests
mem_check_go: mem_check_unit_tests

.PHONY: clean
clean: clean_coverage
	$(RM) $(OUT_DIR)/*.o $(OUT_DIR)/*.d *.exe *.lastbuildstate

.PHONY: clean_coverage
clean_coverage:
	$(RM) $(OUT_DIR)/*.gcda $(OUT_DIR)/*.gcno $(OUT_DIR)/*.gcov

.PHONY: format
format:
	clang-format -i -style=microsoft $(INC_DIR)/*.h $(CHECK_DIR)/*.c $(SRC_DIR)/*.c
