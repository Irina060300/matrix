CFLAGS = -Wall -Wextra -Werror -g -lm
GCOV=-fprofile-arcs -ftest-coverage -fPIC

all: build
build: s21_matrix

s21_matrix:
	gcc ${CFLAGS} s21_matrix.c -o s21_matrix
	./s21_matrix

test: 
	gcc s21_matrix_test.c -c
	gcc ${GCOV} ${CFLAGS} -lcheck -pthread -lm -L. s21_matrix.c s21_matrix_test.o
	./a.out

clean: 
	rm -rf *.o *.out *.gch *.dSYM *.gcov *.gcda *.gcno *.a test *.css *.html vgcore* main report *.info *.gz *.log
rebuild: clean build