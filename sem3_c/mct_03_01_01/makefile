CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
SRC_LIBS := -lm
CHECK_LIBS := -lcheck -lm

INC_DIR := inc
OUT_DIR := out
SRC_DIR := src
CHECK_DIR := unit_tests

$(shell mkdir -p $(OUT_DIR))

SRC_OBJS := $(OUT_DIR)/arr.o $(OUT_DIR)/main.o

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


$(OUT_DIR)/arr.o: $(SRC_DIR)/arr.c $(INC_DIR)/arr.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)

$(OUT_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/arr.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)

.PHONY: func_tests
func_tests: debug
	./func_tests/scripts/func_tests.sh
	gcov -r $(SRC_OBJS) -o $(OUT_DIR)
	mv *.gcov $(OUT_DIR)

.PHONY: mem_check_func_tests
mem_check_func_tests: debug
	./func_tests/scripts/func_tests.sh --mem_check
	gcov -r $(SRC_OBJS) -o $(OUT_DIR)
	mv *.gcov $(OUT_DIR)

.PHONY: clean
clean: clean_coverage
	$(RM) $(OUT_DIR)/*.o $(OUT_DIR)/*.d *.exe *.lastbuildstate

.PHONY: clean_coverage
clean_coverage:
	$(RM) $(OUT_DIR)/*.gcda $(OUT_DIR)/*.gcno $(OUT_DIR)/*.gcov

.PHONY: format
format:
	clang-format -i -style=microsoft $(INC_DIR)/*.h $(SRC_DIR)/*.c