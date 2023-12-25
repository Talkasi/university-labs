CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
SRC_LIBS := -lm
CHECK_LIBS := -lcheck -lm

INC_DIR := inc
OUT_DIR := out
SRC_DIR := src
CHECK_DIR := unit_tests

$(shell mkdir -p $(OUT_DIR))

OBJS_FOR_CHECK := $(OUT_DIR)/my_snprintf.o
SRC_OBJS := $(OBJS_FOR_CHECK) $(OUT_DIR)/main.o
CHECK_SUITES := check_my_snprintf.o
CHECK_OBJS := $(addprefix $(OUT_DIR)/, check_main.o $(CHECK_SUITES))
N_CHECK_SUITES := $(words $(CHECK_SUITES))

SRCS := $(wildcard $(SRC_DIR)/*.c)
CHECK_SRCS := $(wildcard $(CHECK_DIR)/*.c)

unit_tests.exe: $(CHECK_OBJS) $(OBJS_FOR_CHECK)
	$(CC) $(CFLAGS) -I./inc $^ -o $@ $(CHECK_LIBS)

$(OUT_DIR)/my_snprintf.o: $(SRC_DIR)/my_snprintf.c $(INC_DIR)/my_snprintf.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)

$(OUT_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/my_snprintf.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)


$(OUT_DIR)/check_main.o: $(CHECK_DIR)/check_main.c $(INC_DIR)/check_my_snprintf.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)

$(OUT_DIR)/check_my_snprintf.o: $(CHECK_DIR)/check_my_snprintf.c $(INC_DIR)/check_my_snprintf.h $(INC_DIR)/my_snprintf.h
	$(CC) $(CFLAGS) -I./inc -c $< -o $@ $(SRC_LIBS)


.PHONY: unit_tests
unit_tests: CFLAGS += -g3 --coverage
unit_tests: unit_tests.exe
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES)
	gcov -r $(CHECK_OBJS) $(OBJS_FOR_CHECK) -o $(OUT_DIR)
	mv *.gcov $(OUT_DIR)

.PHONY: mem_check_unit_tests
mem_check_unit_tests: CFLAGS += -g3 --coverage
mem_check_unit_tests: unit_tests.exe
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) --mem_check
	gcov -r $(CHECK_OBJS) $(OBJS_FOR_CHECK) -o $(OUT_DIR)
	mv *.gcov $(OUT_DIR)

.PHONY: clean
clean:
	$(RM) $(OUT_DIR)/*.o $(OUT_DIR)/*.d *.exe
	$(RM) $(OUT_DIR)/*.gcda $(OUT_DIR)/*.gcno $(OUT_DIR)/*.gcov

.PHONY: format
format:
	clang-format -i -style=microsoft $(INC_DIR)/*.h $(CHECK_DIR)/*.c $(SRC_DIR)/*.c
