T_SRCS     = tests/check_s21_set.cpp \
             tests/s21_vector_test.cpp \
			 tests/map_test.cpp \
			 tests/test_list.cpp \
			 tests/stackTests.cpp \
			 tests/queueTests.cpp \
			 tests/arrayTests.cpp \
			 tests/s21_multiset_test.cpp

T_NAME     = tests/check_s21_set.check \
             tests/s21_vector_test.check \
			 tests/map_test.check \
			 tests/test_list.check \
			 tests/stackTests.check \
			 tests/queueTests.check \
			 tests/arrayTests.check \
			 tests/s21_multiset_test.check

REPORT_DIR = report
LCOV_INFO  = coverage.info

OS = $(shell uname)
ifeq ($(OS), Linux)
	LINUX_LIBS= -lsubunit -lrt -lpthread -lm
	MEMTEST= vg
	COMPILER        = g++ -std=c++17
else
	LINUX_LIBS=
	MEMTEST= leaks
	COMPILER        = gcc -std=c++17 -lstdc++
endif

CXX         = $(COMPILER)
gcov  : CXX = $(COMPILER) --coverage -DGCOV
debug : CXX = $(COMPILER) -g
vg    : CXX = $(COMPILER) -ggdb3
CFLAGS      = -I.
checkW : CFLAGS      = -I. -Wall -Wextra -Werror -Wshadow
LIBCHECK    = -lgtest -lgtest_main

all: test

re: clean all

gcov: re test

checkW: re

debug: re test

gcov_report:
	@make -i gcov
	@lcov -o $(LCOV_INFO) -c -d . --no-external
	@genhtml -o $(REPORT_DIR) $(LCOV_INFO)
	@open $(REPORT_DIR)/index.html

%.check: %.cpp
	@$(CXX) $< $(LIBCHECK) -o $@ $(LINUX_LIBS) -L.

test: clean $(T_NAME)
	@for t_name in $(notdir $(T_NAME)); do \
		./tests/$$t_name; \
	done

mem: $(MEMTEST)

leaks: clean $(T_NAME)
	@for t_name in $(notdir $(T_NAME)); do \
		CK_FORK=no leaks --atExit -- ./tests/$$t_name; \
	done

vg: clean $(T_NAME)
	for t_name in $(notdir $(T_NAME)); do \
		CK_FORK=no valgrind \
				--leak-check=full  --show-leak-kinds=all \
				--track-origins=yes --verbose \
				--log-file=valgrind_$$t_name.txt ./tests/$$t_name; \
	done

clean:
	@rm -rf *.o *.a *.gcno */*.gcno *.gcda */*.gcda *.gcov */*.gcov $(T_NAME) *coverage** report tests/coverage** tests/*.dSYM valgrind*.*

cpplint:
	@python3 ../materials/linters/cpplint.py  --quiet --extension=cpp,h,inl $(T_SRCS) *.h *.inl

cppcheck:
	@cppcheck -q --std=c++17 --enable=all --language=c++ --suppressions-list=suppressions.cfg $(T_SRCS) *.h *.inl

check: cpplint cppcheck mem
	@make -i checkW
