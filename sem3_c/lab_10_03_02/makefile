CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
SRC_LIBS := -lm
CHECK_LIBS := -lcheck -lm

SRC_OBJS := associative_array_impl_2.o
CHECK_SUITES := check_assoc_array_insert.o check_assoc_array_clear.o check_assoc_array_find.o check_assoc_array_min.o check_assoc_array_max.o check_assoc_array_remove.o
CHECK_OBJS := $(addprefix , check_main.o $(CHECK_SUITES))
N_CHECK_SUITES := $(words $(CHECK_SUITES))

SRCS := $(wildcard *.c)

.PHONY: unit_tests
unit_tests: CFLAGS += -g3
unit_tests: unit_tests.exe
	./unit_tests.exe

unit_tests.exe: $(CHECK_OBJS) $(SRC_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_LIBS)

associative_array_impl_1.o: associative_array_impl_2.c check_assoc_array_suites.h
	$(CC) $(CFLAGS) -c $< -o $@ $(SRC_LIBS)

check_main.o: check_main.c check_assoc_array_suites.h
	$(CC) $(CFLAGS) -c $< -o $@ $(SRC_LIBS)

check_assoc_array_insert.o: check_assoc_array_insert.c check_assoc_array_suites.h
	$(CC) $(CFLAGS) -c $< -o $@ $(SRC_LIBS)

check_assoc_array_clear.o: check_assoc_array_clear.c check_assoc_array_suites.h
	$(CC) $(CFLAGS) -c $< -o $@ $(SRC_LIBS)

check_assoc_array_find.o: check_assoc_array_find.c check_assoc_array_suites.h
	$(CC) $(CFLAGS) -c $< -o $@ $(SRC_LIBS)

check_assoc_array_min.o: check_assoc_array_min.c check_assoc_array_suites.h
	$(CC) $(CFLAGS) -c $< -o $@ $(SRC_LIBS)

check_assoc_array_max.o: check_assoc_array_max.c check_assoc_array_suites.h
	$(CC) $(CFLAGS) -c $< -o $@ $(SRC_LIBS)

check_assoc_array_remove.o: check_assoc_array_remove.c check_assoc_array_suites.h
	$(CC) $(CFLAGS) -c $< -o $@ $(SRC_LIBS)

.PHONY: mem_check_unit_tests
mem_check_unit_tests: CFLAGS += -g3
mem_check_unit_tests: unit_tests.exe
	valgrind -q --leak-check=full ./unit_tests.exe

.PHONY: clean
clean:
	$(RM) *.o *.exe

.PHONY: format
format:
	clang-format -i -style=microsoft *.h *.c