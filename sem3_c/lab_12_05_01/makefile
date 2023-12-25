CC := gcc

INC_DIR := inc
OUT_DIR := out
SRC_DIR := src
CHECK_DIR := unit_tests

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion
SRC_LIBS := -lm
CHECK_LIBS := -lcheck -lm

$(shell mkdir -p $(OUT_DIR))

CHECK_SUITES := check_key.o check_mysort.o
CHECK_SUITES_DLFCN := check_key_dlfcn.o check_mysort_dlfcn.o
CHECK_OBJS := $(addprefix $(OUT_DIR)/, check_main.o $(CHECK_SUITES))
CHECK_OBJS_DLFCN := $(addprefix $(OUT_DIR)/, check_main.o $(CHECK_SUITES_DLFCN))
N_CHECK_SUITES := $(words $(CHECK_SUITES))


.PHONY: go
go: func_tests_all unit_tests_all

.PHONY: mem_check_go
mem_check_go: func_tests_mem_check_all unit_tests_mem_check_all


.PHONY: all
all: static_app.exe dyn1_app.exe dyn2_app.exe

.PHONY: unit_all
unit_tests_all: static_unit_tests dyn1_unit_tests dyn2_unit_tests


static_app.exe: $(OUT_DIR)/main.o $(SRC_DIR)/libarr_stat.a
	$(CC) $(CFLAGS) -I./$(INC_DIR) $< -o $@ $(SRC_LIBS) -L./$(SRC_DIR) -larr_stat

dyn1_app.exe: $(OUT_DIR)/main.o $(SRC_DIR)/libarr_dyn.so
	$(CC) $(CFLAGS) -I./$(INC_DIR) $< -o $@ $(SRC_LIBS) -L./$(SRC_DIR) -larr_dyn

dyn2_app.exe: $(OUT_DIR)/main_dlfcn.o $(SRC_DIR)/libarr_dyn.so
	$(CC) $(CFLAGS) -I./$(INC_DIR) $< -o $@ $(SRC_LIBS) -ldl


# Static lib block
$(SRC_DIR)/libarr_stat.a: $(OUT_DIR)/my_arr_stat.o
	ar cr $@ $<
	ranlib $@

$(OUT_DIR)/my_arr_stat.o: $(SRC_DIR)/my_arr.c $(INC_DIR)/my_arr.h
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(SRC_LIBS)


# Dynamic lib block
$(SRC_DIR)/libarr_dyn.so: $(OUT_DIR)/my_arr_dyn.o 
	gcc -o $@ -shared $<

$(OUT_DIR)/my_arr_dyn.o: $(SRC_DIR)/my_arr.c $(INC_DIR)/my_arr.h
	$(CC) $(CFLAGS) -fPIC -I./$(INC_DIR) -c $< -o $@ $(SRC_LIBS)


# Normal main
$(OUT_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(SRC_LIBS)

# DLFCN main
$(OUT_DIR)/main_dlfcn.o: $(SRC_DIR)/main_dlfcn.c
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(SRC_LIBS)


.PHONY: static_unit_tests
static_unit_tests: $(SRC_DIR)/libarr_stat.a static_unit_tests.exe

.PHONY: dyn1_unit_tests
dyn1_unit_tests: $(SRC_DIR)/libarr_dyn.so dyn1_unit_tests.exe

.PHONY: dyn2_unit_tests
dyn2_unit_tests: $(SRC_DIR)/libarr_dyn.so dyn2_unit_tests.exe


static_unit_tests.exe: $(CHECK_OBJS)
	$(CC) $(CFLAGS) -I./inc $^ -o $@ $(CHECK_LIBS) -L./$(SRC_DIR) -larr_stat

dyn1_unit_tests.exe: $(CHECK_OBJS)
	$(CC) $(CFLAGS) -I./inc $^ -o $@ $(CHECK_LIBS) -L./$(SRC_DIR) -larr_dyn

dyn2_unit_tests.exe: $(CHECK_OBJS_DLFCN)
	$(CC) $(CFLAGS) -I./inc $^ -o $@ $(CHECK_LIBS) -ldl


$(OUT_DIR)/check_main.o: $(CHECK_DIR)/check_main.c $(INC_DIR)/check_key.h $(INC_DIR)/check_mysort.h 
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(CHECK_LIBS)

$(OUT_DIR)/check_key.o: $(CHECK_DIR)/check_key.c $(INC_DIR)/check_key.h $(INC_DIR)/my_arr.h
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(CHECK_LIBS)

$(OUT_DIR)/check_mysort.o: $(CHECK_DIR)/check_mysort.c $(INC_DIR)/check_mysort.h $(INC_DIR)/my_arr.h
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(CHECK_LIBS)

$(OUT_DIR)/check_key_dlfcn.o: $(CHECK_DIR)/check_key_dlfcn.c $(INC_DIR)/check_key.h
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(CHECK_LIBS)

$(OUT_DIR)/check_mysort_dlfcn.o: $(CHECK_DIR)/check_mysort_dlfcn.c $(INC_DIR)/check_mysort.h
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@ $(CHECK_LIBS)


.PHONY: func_tests_all
func_tests_all: func_tests_static func_tests_dyn1 func_tests_dyn2

.PHONY: func_tests_static
func_tests_static: static_app.exe
	./func_tests/scripts/func_tests.sh static_app.exe

.PHONY: func_tests_dyn1
func_tests_dyn1: dyn1_app.exe
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./$(SRC_DIR) \
	./func_tests/scripts/func_tests.sh dyn1_app.exe

.PHONY: func_tests_dyn2
func_tests_dyn2: dyn2_app.exe
	./func_tests/scripts/func_tests.sh dyn2_app.exe


.PHONY: func_tests_mem_check_all
func_tests_mem_check_all: func_tests_mem_check_static func_tests_mem_check_dyn1 func_tests_mem_check_dyn2

.PHONY: func_tests_mem_check_static
func_tests_mem_check_static: static_app.exe
	./func_tests/scripts/func_tests.sh static_app.exe --mem_check

.PHONY: func_tests_mem_check_dyn1
func_tests_mem_check_dyn1: dyn1_app.exe
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./$(SRC_DIR) \
	./func_tests/scripts/func_tests.sh dyn1_app.exe --mem_check

.PHONY: func_tests_mem_check_dyn2
func_tests_mem_check_dyn2: dyn2_app.exe
	./func_tests/scripts/func_tests.sh dyn2_app.exe --mem_check


.PHONY: unit_tests_all
unit_tests_all: unit_tests_static unit_tests_dyn1 unit_tests_dyn2

.PHONY: unit_tests_static
unit_tests_static: static_unit_tests.exe
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) static_unit_tests.exe

.PHONY: unit_tests_dyn1
unit_tests_dyn1: dyn1_unit_tests.exe
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./$(SRC_DIR) \
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) dyn1_unit_tests.exe

.PHONY: unit_tests_dyn2
unit_tests_dyn2: dyn2_unit_tests.exe
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./$(SRC_DIR) \
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) dyn2_unit_tests.exe


.PHONY: unit_tests_mem_check_all
unit_tests_mem_check_all: unit_tests_mem_check_static unit_tests_mem_check_dyn1 unit_tests_mem_check_dyn2

.PHONY: unit_tests_mem_check_static
unit_tests_mem_check_static: static_unit_tests.exe
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) static_unit_tests.exe --mem_check

.PHONY: unit_tests_mem_check_dyn1
unit_tests_mem_check_dyn1: dyn1_unit_tests.exe
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./$(SRC_DIR) \
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) dyn1_unit_tests.exe --mem_check

.PHONY: unit_tests_mem_check_dyn2
unit_tests_mem_check_dyn2: dyn2_unit_tests.exe
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./$(SRC_DIR) \
	./unit_tests/scripts/unit_tests.sh $(N_CHECK_SUITES) dyn2_unit_tests.exe --mem_check


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
	clang-format -i -style=microsoft $(INC_DIR)/*.h $(CHECK_DIR)/*.c $(SRC_DIR)/*.c
