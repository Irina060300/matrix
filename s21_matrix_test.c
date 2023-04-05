
// #include "s21_matrix.h"

// #include <check.h>
// #include <errno.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/types.h>
// #include <time.h>
// #include <unistd.h>

// unsigned int seed = 0;

// START_TEST(create_matrix) {
//   const int rows = rand_r(&seed) % 100 + 1;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t m = {0};
//   s21_create_matrix(rows, cols, &m);
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       m.matrix[i][j] = 0;
//       ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-06);
//     }
//   }
//   ck_assert_int_eq(m.rows, rows);
//   ck_assert_int_eq(m.columns, cols);
//   s21_remove_matrix(&m);
// }
// END_TEST

// START_TEST(not_rows) {
//   const int rows = 0;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t m = {0};
//   ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
// }
// END_TEST

// START_TEST(not_cols) {
//   const int cols = 0;
//   const int rows = rand_r(&seed) % 100 + 1;
//   matrix_t m = {0};
//   ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
// }
// END_TEST

// START_TEST(eq_matrix) {
//   const int rows = rand_r(&seed) % 100 + 1;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t A = {0}, B = {0};
//   s21_create_matrix(rows, cols, &A);
//   s21_create_matrix(rows, cols, &B);
//   double k = 0.1;
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500.2542 + k;
//       A.matrix[i][j] = rand_val;
//       B.matrix[i][j] = rand_val;
//       k += 0.000001;
//     }
//   }
//   ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
// }
// END_TEST

// START_TEST(not_eq_matrix) {
//   const int rows = rand_r(&seed) % 100 + 1;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t A = {0}, B = {0};
//   s21_create_matrix(rows, cols, &A);
//   s21_create_matrix(rows, cols, &B);
//   double k = 0.1;
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500 + k;
//       A.matrix[i][j] = rand_val;
//       B.matrix[i][j] = rand_val + 0.0001;
//       k += 0.000001;
//     }
//   }
//   ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
// }
// END_TEST

// START_TEST(not_rows_eq_matrix) {
//   const int rows = rand_r(&seed) % 100 + 1;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t A = {0}, B = {0};
//   s21_create_matrix(rows, cols, &A);
//   s21_create_matrix(rows + 10, cols, &B);
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500;
//       A.matrix[i][j] = rand_val;
//     }
//   }
//   for (int i = 0; i < rows + 10; i++) {
//     for (int j = 0; j < cols; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500;
//       B.matrix[i][j] = rand_val;
//     }
//   }
//   ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
// }
// END_TEST

// START_TEST(sum_matrix) {
//   const int rows = rand_r(&seed) % 100 + 1;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t A = {0}, B = {0}, check = {0}, result = {0};
//   s21_create_matrix(rows, cols, &A);
//   s21_create_matrix(rows, cols, &B);
//   s21_create_matrix(rows, cols, &check);
//   double k = 0.1;
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500 + k;
//       A.matrix[i][j] = rand_val;
//       B.matrix[i][j] = rand_val + 0.015;
//       check.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
//       k += 0.000001;
//     }
//   }
//   s21_sum_matrix(&A, &B, &result);
//   ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&check);
// }
// END_TEST

// START_TEST(sub_matrix) {
//   const int rows = rand_r(&seed) % 100 + 1;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t A = {0}, B = {0}, check = {0}, result = {0};
//   s21_create_matrix(rows, cols, &A);
//   s21_create_matrix(rows, cols, &B);
//   s21_create_matrix(rows, cols, &check);
//   double k = 0.1;
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500 + k;
//       A.matrix[i][j] = rand_val;
//       B.matrix[i][j] = rand_val + k;
//       check.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
//       k += 0.000001;
//     }
//   }
//   s21_sub_matrix(&A, &B, &result);
//   ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&check);
// }
// END_TEST

// START_TEST(mult_number) {
//   const int rows = rand_r(&seed) % 100 + 1;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t A = {0}, check = {0}, result = {0};
//   s21_create_matrix(rows, cols, &A);
//   s21_create_matrix(rows, cols, &check);
//   double k = 0.1;
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500 + k;
//       A.matrix[i][j] = rand_val;
//       check.matrix[i][j] = rand_val * 0.345;
//       k += 0.000001;
//     }
//   }
//   s21_mult_number(&A, 0.345, &result);
//   ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&check);
// }
// END_TEST

// START_TEST(mult_matrix) {
//   const int rows = rand_r(&seed) % 100 + 1;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t A = {0}, B = {0}, check = {0}, result = {0};
//   s21_create_matrix(rows, cols, &A);
//   s21_create_matrix(cols, rows + 10, &B);
//   s21_create_matrix(A.rows, B.columns, &check);
//   double k = 0.1;
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500 + k;
//       A.matrix[i][j] = rand_val;
//       k += 0.000001;
//     }
//   }
//   for (int i = 0; i < cols; i++) {
//     for (int j = 0; j < rows; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500 + k;
//       B.matrix[i][j] = rand_val + k + 0.32;
//       k += 0.000001;
//     }
//   }
//   for (int i = 0; i < A.rows; i++) {
//     for (int j = 0; j < B.columns; j++) {
//       check.matrix[i][j] = 0;
//       for (int s = 0; s < A.columns; s++) {
//         check.matrix[i][j] += A.matrix[i][s] * B.matrix[s][j];
//       }
//     }
//   }

//   s21_mult_matrix(&A, &B, &result);
//   ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&check);
// }
// END_TEST

// START_TEST(transpose_matrix) {
//   const int rows = rand_r(&seed) % 100 + 1;
//   const int cols = rand_r(&seed) % 100 + 1;
//   matrix_t A = {0}, check = {0}, result = {0};
//   s21_create_matrix(rows, cols, &A);
//   s21_create_matrix(cols, rows, &check);
//   double k = 0.1;
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       double rand_val = rand_r(&seed) % 3001 - 1500 + k;
//       A.matrix[i][j] = rand_val;
//       check.matrix[j][i] = rand_val;
//       k += 0.000001;
//     }
//   }
//   s21_transpose(&A, &result);
//   ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&check);
// }
// END_TEST

// START_TEST(calc_complements_mat) {
//   matrix_t A = {0}, check = {0}, result = {0};
//   s21_create_matrix(3, 3, &A);
//   s21_create_matrix(3, 3, &check);
//   A.matrix[0][0] = 1;
//   A.matrix[0][1] = 2;
//   A.matrix[0][2] = 3;
//   A.matrix[1][0] = 0;
//   A.matrix[1][1] = 4;
//   A.matrix[1][2] = 2;
//   A.matrix[2][0] = 5;
//   A.matrix[2][1] = 2;
//   A.matrix[2][2] = 1;

//   check.matrix[0][0] = 0;
//   check.matrix[0][1] = -10;
//   check.matrix[0][2] = -20;
//   check.matrix[1][0] = -4;
//   check.matrix[1][1] = -14;
//   check.matrix[1][2] = -8;
//   check.matrix[2][0] = -8;
//   check.matrix[2][1] = 2;
//   check.matrix[2][2] = 4;

//   s21_calc_complements(&A, &result);
//   ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

//   s21_remove_matrix(&A);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&check);
// }
// END_TEST

// START_TEST(determinant_mat) {
//   matrix_t A = {0};
//   s21_create_matrix(3, 3, &A);
//   A.matrix[0][0] = 1;
//   A.matrix[0][1] = 2;
//   A.matrix[0][2] = 3;
//   A.matrix[1][0] = 0;
//   A.matrix[1][1] = 4;
//   A.matrix[1][2] = 2;
//   A.matrix[2][0] = 5;
//   A.matrix[2][1] = 2;
//   A.matrix[2][2] = 1;
//   double result = 0;
//   s21_determinant(&A, &result);
//   ck_assert_int_eq(result, -40);
//   s21_remove_matrix(&A);
// }
// END_TEST

// START_TEST(inverse_mat) {
//   matrix_t A = {0}, check = {0}, result = {0};
//   s21_create_matrix(3, 3, &A);
//   s21_create_matrix(3, 3, &check);
//   A.matrix[0][0] = 1;
//   A.matrix[0][1] = 2;
//   A.matrix[0][2] = 3;
//   A.matrix[1][0] = 0;
//   A.matrix[1][1] = 4;
//   A.matrix[1][2] = 2;
//   A.matrix[2][0] = 5;
//   A.matrix[2][1] = 2;
//   A.matrix[2][2] = 1;

//   check.matrix[0][0] = 0;
//   check.matrix[0][1] = -0.1;
//   check.matrix[0][2] = 0.2;
//   check.matrix[1][0] = -0.25;
//   check.matrix[1][1] = 0.35;
//   check.matrix[1][2] = 0.05;
//   check.matrix[2][0] = 0.5;
//   check.matrix[2][1] = -0.2;
//   check.matrix[2][2] = -0.1;

//   s21_inverse_matrix(&A, &result);
//   ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&check);
// }
// END_TEST

// START_TEST(inverse_mat_2) {
//   matrix_t A = {0}, check = {0}, result = {0};
//   s21_create_matrix(3, 3, &A);
//   s21_create_matrix(3, 3, &check);
//   A.matrix[0][0] = 2;
//   A.matrix[0][1] = 5;
//   A.matrix[0][2] = 7;
//   A.matrix[1][0] = 6;
//   A.matrix[1][1] = 3;
//   A.matrix[1][2] = 4;
//   A.matrix[2][0] = 5;
//   A.matrix[2][1] = -2;
//   A.matrix[2][2] = -3;

//   check.matrix[0][0] = 1;
//   check.matrix[0][1] = -1;
//   check.matrix[0][2] = 1;
//   check.matrix[1][0] = -38;
//   check.matrix[1][1] = 41;
//   check.matrix[1][2] = -34;
//   check.matrix[2][0] = 27;
//   check.matrix[2][1] = -29;
//   check.matrix[2][2] = 24;

//   s21_inverse_matrix(&A, &result);
//   ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&check);
// }
// END_TEST

// int main(void) {
//   Suite *s1 = suite_create("Core");
//   TCase *tc1_1 = tcase_create("Core");
//   SRunner *sr = srunner_create(s1);
//   int nf;

//   suite_add_tcase(s1, tc1_1);
//   tcase_add_test(tc1_1, create_matrix);
//   tcase_add_test(tc1_1, not_rows);
//   tcase_add_test(tc1_1, not_cols);
//   tcase_add_test(tc1_1, eq_matrix);
//   tcase_add_test(tc1_1, not_eq_matrix);
//   tcase_add_test(tc1_1, not_rows_eq_matrix);

//   tcase_add_test(tc1_1, sub_matrix);
//   tcase_add_test(tc1_1, mult_number);
//   tcase_add_test(tc1_1, mult_matrix);

//   tcase_add_test(tc1_1, inverse_mat);
//   tcase_add_test(tc1_1, sum_matrix);
//   tcase_add_test(tc1_1, determinant_mat);
//   tcase_add_test(tc1_1, inverse_mat_2);

//   tcase_add_test(tc1_1, transpose_matrix);
//   tcase_add_test(tc1_1, calc_complements_mat);

//   srunner_set_fork_status(sr, CK_NOFORK);
//   srunner_run_all(sr, CK_ENV);
//   nf = srunner_ntests_failed(sr);
//   srunner_free(sr);

//   return nf == 0 ? 0 : 1;
// }


/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "test.check" instead.
 */

#include <check.h>

#include "s21_matrix.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

unsigned int seed = 0;

START_TEST(create_matrix) {
const int rows = rand_r(&seed) % 100 + 1;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t m = {0};
s21_create_matrix(rows, cols, &m);
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        m.matrix[i][j] = 0;
        ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-06);
    }
}
ck_assert_int_eq(m.rows, rows);
ck_assert_int_eq(m.columns, cols);
s21_remove_matrix(&m);
}
END_TEST

START_TEST(not_rows) {
const int rows = 0;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t m = {0};
ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

START_TEST(not_cols) {
const int cols = 0;
const int rows = rand_r(&seed) % 100 + 1;
matrix_t m = {0};
ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

START_TEST(eq_matrix) {
const int rows = rand_r(&seed) % 100 + 1;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t A = {0}, B = {0};
s21_create_matrix(rows, cols, &A);
s21_create_matrix(rows, cols, &B);
double k = 0.1;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500 + k;
        A.matrix[i][j] = rand_val;
        B.matrix[i][j] = rand_val;
        k += 0.000001;
    }
}
ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
s21_remove_matrix(&A);
s21_remove_matrix(&B);
}
END_TEST

START_TEST(not_eq_matrix) {
const int rows = rand_r(&seed) % 100 + 1;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t A = {0}, B = {0};
s21_create_matrix(rows, cols, &A);
s21_create_matrix(rows, cols, &B);
double k = 0.1;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500 + k;
        A.matrix[i][j] = rand_val;
        B.matrix[i][j] = rand_val + 0.0001;
        k += 0.000001;
    }
}
ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
s21_remove_matrix(&A);
s21_remove_matrix(&B);
}
END_TEST

START_TEST(not_rows_eq_matrix) {
const int rows = rand_r(&seed) % 100 + 1;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t A = {0}, B = {0};
s21_create_matrix(rows, cols, &A);
s21_create_matrix(rows + 10, cols, &B);
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500;
        A.matrix[i][j] = rand_val;
    }
}
for (int i = 0; i < rows + 10; i++) {
    for (int j = 0; j < cols; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500;
        B.matrix[i][j] = rand_val;
    }
}
ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
s21_remove_matrix(&A);
s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix) {
const int rows = rand_r(&seed) % 100 + 1;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t A = {0}, B = {0}, check = {0}, result = {0};
s21_create_matrix(rows, cols, &A);
s21_create_matrix(rows, cols, &B);
s21_create_matrix(rows, cols, &check);
double k = 0.1;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500 + k;
        A.matrix[i][j] = rand_val;
        B.matrix[i][j] = rand_val + 0.015;
        check.matrix[i][j] = 2 * rand_val + 0.015;
        k += 0.000001;
    }
}
s21_sum_matrix(&A, &B, &result);
ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
s21_remove_matrix(&A);
s21_remove_matrix(&B);
s21_remove_matrix(&result);
s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_matrix) {
const int rows = rand_r(&seed) % 100 + 1;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t A = {0}, B = {0}, check = {0}, result = {0};
s21_create_matrix(rows, cols, &A);
s21_create_matrix(rows, cols, &B);
s21_create_matrix(rows, cols, &check);
double k = 0.1;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500 + k;
        A.matrix[i][j] = rand_val;
        B.matrix[i][j] = rand_val + k;
        check.matrix[i][j] = -k;
        k += 0.000001;
    }
}
s21_sub_matrix(&A, &B, &result);
ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
s21_remove_matrix(&A);
s21_remove_matrix(&B);
s21_remove_matrix(&result);
s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number) {
const int rows = rand_r(&seed) % 100 + 1;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t A = {0}, check = {0}, result = {0};
s21_create_matrix(rows, cols, &A);
s21_create_matrix(rows, cols, &check);
double k = 0.1;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500 + k;
        A.matrix[i][j] = rand_val;
        check.matrix[i][j] = rand_val * 0.345;
        k += 0.000001;
    }
}
s21_mult_number(&A, 0.345, &result);
ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
s21_remove_matrix(&A);
s21_remove_matrix(&result);
s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix) {
const int rows = rand_r(&seed) % 100 + 1;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t A = {0}, B = {0}, check = {0}, result = {0};
s21_create_matrix(rows, cols, &A);
s21_create_matrix(cols, rows + 10, &B);
s21_create_matrix(A.rows, B.columns, &check);
double k = 0.1;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500 + k;
        A.matrix[i][j] = rand_val;
        k += 0.000001;
    }
}
for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500 + k;
        B.matrix[i][j] = rand_val + k + 0.32;
        k += 0.000001;
    }
}
for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
        check.matrix[i][j] = 0;
        for (int s = 0; s < A.columns; s++) {
            check.matrix[i][j] += A.matrix[i][s] * B.matrix[s][j];
        }
    }
}

s21_mult_matrix(&A, &B, &result);
ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
s21_remove_matrix(&A);
s21_remove_matrix(&B);
s21_remove_matrix(&result);
s21_remove_matrix(&check);
}
END_TEST

START_TEST(transpose_matrix) {
const int rows = rand_r(&seed) % 100 + 1;
const int cols = rand_r(&seed) % 100 + 1;
matrix_t A = {0}, check = {0}, result = {0};
s21_create_matrix(rows, cols, &A);
s21_create_matrix(cols, rows, &check);
double k = 0.1;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        double rand_val = rand_r(&seed) % 3001 - 1500 + k;
        A.matrix[i][j] = rand_val;
        check.matrix[j][i] = rand_val;
        k += 0.000001;
    }
}
s21_transpose(&A, &result);
ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
s21_remove_matrix(&A);
s21_remove_matrix(&result);
s21_remove_matrix(&check);
}
END_TEST

START_TEST(calc_complements_mat) {
matrix_t A = {0}, check = {0}, result = {0};
s21_create_matrix(3, 3, &A);
s21_create_matrix(3, 3, &check);
A.matrix[0][0] = 1;
A.matrix[0][1] = 2;
A.matrix[0][2] = 3;
A.matrix[1][0] = 0;
A.matrix[1][1] = 4;
A.matrix[1][2] = 2;
A.matrix[2][0] = 5;
A.matrix[2][1] = 2;
A.matrix[2][2] = 1;

check.matrix[0][0] = 0;
check.matrix[0][1] = 10;
check.matrix[0][2] = -20;
check.matrix[1][0] = 4;
check.matrix[1][1] = -14;
check.matrix[1][2] = 8;
check.matrix[2][0] = -8;
check.matrix[2][1] = -2;
check.matrix[2][2] = 4;

s21_calc_complements(&A, &result);
ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

s21_remove_matrix(&A);
s21_remove_matrix(&result);
s21_remove_matrix(&check);
}
END_TEST

START_TEST(determinant_mat) {
matrix_t A = {0};
s21_create_matrix(3, 3, &A);
A.matrix[0][0] = 1;
A.matrix[0][1] = 2;
A.matrix[0][2] = 3;
A.matrix[1][0] = 0;
A.matrix[1][1] = 4;
A.matrix[1][2] = 2;
A.matrix[2][0] = 5;
A.matrix[2][1] = 2;
A.matrix[2][2] = 1;
double result = 0;
s21_determinant(&A, &result);
ck_assert_int_eq(result, -40);
s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_mat) {
matrix_t A = {0}, check = {0}, result = {0};
s21_create_matrix(3, 3, &A);
s21_create_matrix(3, 3, &check);
A.matrix[0][0] = 1;
A.matrix[0][1] = 2;
A.matrix[0][2] = 3;
A.matrix[1][0] = 0;
A.matrix[1][1] = 4;
A.matrix[1][2] = 2;
A.matrix[2][0] = 5;
A.matrix[2][1] = 2;
A.matrix[2][2] = 1;

check.matrix[0][0] = 0;
check.matrix[0][1] = -0.1;
check.matrix[0][2] = 0.2;
check.matrix[1][0] = -0.25;
check.matrix[1][1] = 0.35;
check.matrix[1][2] = 0.05;
check.matrix[2][0] = 0.5;
check.matrix[2][1] = -0.2;
check.matrix[2][2] = -0.1;

s21_inverse_matrix(&A, &result);
ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
s21_remove_matrix(&A);
s21_remove_matrix(&result);
s21_remove_matrix(&check);
}
END_TEST

START_TEST(inverse_mat_2) {
matrix_t A = {0}, check = {0}, result = {0};
s21_create_matrix(3, 3, &A);
s21_create_matrix(3, 3, &check);
A.matrix[0][0] = 2;
A.matrix[0][1] = 5;
A.matrix[0][2] = 7;
A.matrix[1][0] = 6;
A.matrix[1][1] = 3;
A.matrix[1][2] = 4;
A.matrix[2][0] = 5;
A.matrix[2][1] = -2;
A.matrix[2][2] = -3;

check.matrix[0][0] = 1;
check.matrix[0][1] = -1;
check.matrix[0][2] = 1;
check.matrix[1][0] = -38;
check.matrix[1][1] = 41;
check.matrix[1][2] = -34;
check.matrix[2][0] = 27;
check.matrix[2][1] = -29;
check.matrix[2][2] = 24;

s21_inverse_matrix(&A, &result);
ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
s21_remove_matrix(&A);
s21_remove_matrix(&result);
s21_remove_matrix(&check);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, create_matrix);
    tcase_add_test(tc1_1, not_rows);
    tcase_add_test(tc1_1, not_cols);
    tcase_add_test(tc1_1, eq_matrix);
    tcase_add_test(tc1_1, not_eq_matrix);
    tcase_add_test(tc1_1, not_rows_eq_matrix);

    tcase_add_test(tc1_1, sub_matrix);
    tcase_add_test(tc1_1, mult_number);
    tcase_add_test(tc1_1, mult_matrix);

    tcase_add_test(tc1_1, inverse_mat);
    tcase_add_test(tc1_1, sum_matrix);
    tcase_add_test(tc1_1, determinant_mat);
    tcase_add_test(tc1_1, inverse_mat_2);

    tcase_add_test(tc1_1, transpose_matrix);
    tcase_add_test(tc1_1, calc_complements_mat);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
