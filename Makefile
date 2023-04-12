
CFLAGS =-Wall -Wextra -Werror -g
GCOV =-fprofile-arcs -ftest-coverage -fPIC
OS=$(shell uname)
ifeq (${OS}, Linux)
	TEST_FLAGS = -lcheck -pthread -lrt -lm -L.
else
	TEST_FLAGS = -lcheck
endif

all: s21_matrix.a

gcov_report: test
	lcov -t "matrix_h" -o matrix_h.info -c -d .
	genhtml -o report matrix_h.info

ifeq (${OS}, Linux)
		cd report && firefox index.html
else
		cd report && open index.html
endif

test: s21_matrix.a
	gcc s21_matrix_test.c -c
	gcc ${CFLAGS} ${TEST_FLAGS} ${GCOV} s21_matrix.c s21_matrix_test.o -o s21_matrix_test
	./s21_matrix_test

s21_matrix.a: s21_matrix.o
	ar rc libs21_matrix.a *.o
	ranlib libs21_matrix.a
	cp libs21_matrix.a s21_matrix.a

s21_matrix.o: s21_matrix.c
	gcc ${CFLAGS} -c s21_matrix.c

.PHONY: all build clean rebuild

clean:
	rm -rf *.o *.out *.gch *.dSYM *.gcov *.gcda *.gcno *.a s21_matrix_test *.css *.html vgcore* report *.info *.gz *.log

rebuild: clean s21_matrix.a

