#include "s21_matrix.h"

#include <check.h>
#include <stdlib.h>

// CREATE_MATRIX

START_TEST(create_matrix_1) {
  int rows = 10, cols = 25;
  matrix_t A = {0};
  int ret_val = s21_create_matrix(rows, cols, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (i + j) * rows + 1.5;
      A.matrix[i][j] = elem;
      ck_assert_double_eq_tol(elem, A.matrix[i][j], 1e-06);
    }
  }
  ck_assert_int_eq(A.rows, rows);
  ck_assert_int_eq(A.columns, cols);
  ck_assert_int_eq(ret_val, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_2) {
  int rows = 10, cols = 24;
  matrix_t A = {0};
  int ret_val = s21_create_matrix(rows, cols, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 1000 + i * j + 7.13514654);
      A.matrix[i][j] = elem;
      ck_assert_double_eq_tol(elem, A.matrix[i][j], 1e-06);
    }
  }
  ck_assert_int_eq(A.rows, rows);
  ck_assert_int_eq(A.columns, cols);
  ck_assert_int_eq(ret_val, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_wrong_rows) {
  int rows = 0, cols = 24;
  matrix_t A = {0};
  int ret_val = s21_create_matrix(rows, cols, &A);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_wrong_cols) {
  int rows = 25, cols = -4;
  matrix_t A = {0};
  int ret_val = s21_create_matrix(rows, cols, &A);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_3) {
  int rows = 25, cols = 5;
  int ret_val = s21_create_matrix(rows, cols, NULL);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  // s21_remove_matrix(&A);
}
END_TEST
// is_equal
START_TEST(is_equal) {
  int rows = 5, cols = 4;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 200) / 2.33;
      A.matrix[i][j] = elem;
      B.matrix[i][j] = elem;
    }
  }
  int ret_val = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret_val, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(is_equal_1) {
  int rows = 16, cols = 2;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 200) / 2.33;
      A.matrix[i][j] = elem;
      B.matrix[i][j] = elem;
    }
  }
  int ret_val = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret_val, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(is_equal_no) {
  int rows = 6, cols = 15;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 300) / -42.33;
      A.matrix[i][j] = elem;
      B.matrix[i][j] = elem + 1e-6;
    }
  }
  int ret_val = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret_val, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(is_equal_no_2) {
  int rows_A = 6, cols_A = 15, rows_B = 10, cols_B = 15;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows_A, cols_A, &A);
  s21_create_matrix(rows_B, cols_B, &B);
  for (int i = 0; i < rows_A; i++) {
    for (int j = 0; j < cols_A; j++) {
      double elem = (double)(rand() % 300) / -42.33;
      A.matrix[i][j] = elem;
    }
  }
  for (int i = 0; i < rows_B; i++) {
    for (int j = 0; j < cols_B; j++) {
      double elem = (double)(rand() % 300) / -42.33;
      B.matrix[i][j] = elem + 1e-6;
    }
  }
  int ret_val = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret_val, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(is_equal_no_3) {
  int rows_A = 6, cols_A = 15, rows_B = 10, cols_B = 15;
  matrix_t A = {0};
  s21_create_matrix(rows_A, cols_A, &A);
  for (int i = 0; i < rows_A; i++) {
    for (int j = 0; j < cols_A; j++) {
      double elem = (double)(rand() % 300) / -42.33;
      A.matrix[i][j] = elem;
    }
  }
  int ret_val = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(ret_val, FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

// SUM
START_TEST(sum_matrix_1) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 7, cols = 9;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  s21_create_matrix(rows, cols, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 100) + 2.33, k = 0.0001;
      A.matrix[i][j] = elem;
      B.matrix[i][j] = elem + k;
      check.matrix[i][j] = 2.0 * elem + k;
      k += 1.0;
      ;
    }
  }
  int ret_val = s21_sum_matrix(&A, &B, &result);
  int is_eq = s21_eq_matrix(&result, &check);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
  ck_assert_int_eq(is_eq, SUCCESS);
  ck_assert_int_eq(ret_val, OK);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 7, cols = 9;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  s21_create_matrix(rows, cols, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 100) + 2.33, k = 0.0001;
      A.matrix[i][j] = elem;
      B.matrix[i][j] = elem + k;
      check.matrix[i][j] = 2.0 * elem + k;
      if ((i + j) % 2 == 0) {
        A.matrix[i][j] = 0;
        B.matrix[i][j] = 0;
        check.matrix[i][j] = 0;
      }
      k += 1.0;
    }
  }
  int ret_val = s21_sum_matrix(&A, &B, &result);
  int is_eq = s21_eq_matrix(&result, &check);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
  ck_assert_int_eq(is_eq, SUCCESS);
  ck_assert_int_eq(ret_val, OK);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 7, cols = 9;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  A.rows = -14;
  int ret_val = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_4) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows_A = 7, cols_A = 9, rows_B = 1, cols_B = 2;
  s21_create_matrix(rows_A, cols_A, &A);
  s21_create_matrix(rows_B, cols_B, &B);
  int ret_val = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret_val, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_5) {
  matrix_t A = {0}, B = {0}, result = {0};
  int ret_val = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_6) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 7, cols = 9;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  B.rows = 0;
  int ret_val = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// SUB_MATRIX

START_TEST(sub_matrix_1) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 7, cols = 9;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  s21_create_matrix(rows, cols, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 100) + 2.33, k = 0.0001;
      A.matrix[i][j] = elem;
      B.matrix[i][j] = 2 * elem + k;
      check.matrix[i][j] = -elem - k;
      k += 1.0;
    }
  }
  int ret_val = s21_sub_matrix(&A, &B, &result);
  int is_eq = s21_eq_matrix(&result, &check);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
  ck_assert_int_eq(is_eq, SUCCESS);
  ck_assert_int_eq(ret_val, OK);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 18, cols = 14;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  s21_create_matrix(rows, cols, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 100) + 2024.204, k = 0.0501;
      A.matrix[i][j] = elem;
      B.matrix[i][j] = 3.0 * elem + k;
      check.matrix[i][j] = -2.0 * elem - k;
      k += 1.45;
    }
  }
  int ret_val = s21_sub_matrix(&A, &B, &result);
  int is_eq = s21_eq_matrix(&result, &check);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
  ck_assert_int_eq(is_eq, SUCCESS);
  ck_assert_int_eq(ret_val, OK);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 4, cols = 45;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  A.rows = -1;
  int ret_val = s21_sub_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

START_TEST(sub_matrix_4) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 4, cols = 45;
  A.rows = rows, B.rows = rows, A.columns = cols, B.columns = cols;
  int ret_val = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

START_TEST(sub_matrix_5) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 4, cols = 45;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  B.columns = -75;
  int ret_val = s21_sub_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

START_TEST(sub_matrix_6) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 4, cols = 45;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  B.columns = 46;
  int ret_val = s21_sub_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(ret_val, CALCULATION_ERROR);
}
END_TEST

START_TEST(sub_matrix_7) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows_A = 18, cols_A = 14, rows_B = 2, cols_B = 2;
  s21_create_matrix(rows_A, cols_A, &A);
  s21_create_matrix(rows_B, cols_B, &B);

  for (int i = 0; i < rows_A; i++) {
    for (int j = 0; j < cols_A; j++) {
      double elem = (double)(rand() % 100) + 2024.204, k = 0.0501;
      A.matrix[i][j] = elem;
      k += 1.45;
    }
  }

  for (int i = 0; i < rows_B; i++) {
    for (int j = 0; j < cols_B; j++) {
      B.matrix[i][j] = i;
    }
  }

  int ret_val = s21_sub_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(ret_val, CALCULATION_ERROR);
}
END_TEST

// MULT_NUMBER

START_TEST(mult_number_1) {
  matrix_t A = {0}, check = {0}, result = {0};
  int rows = 4, cols = 45;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &check);
  double number = 7.63;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 500) + 3.006013;
      A.matrix[i][j] = elem;
      check.matrix[i][j] = elem * number;
    }
  }
  int ret_val = s21_mult_number(&A, number, &result);
  int is_eq = s21_eq_matrix(&result, &check);
  ck_assert_int_eq(ret_val, OK);
  ck_assert_int_eq(is_eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t A = {0}, check = {0}, result = {0};
  int rows = 87, cols = 7;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &check);
  double number = -3.651;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double elem = (double)(rand() % 500 * 3) + 9.999999;
      A.matrix[i][j] = elem;
      check.matrix[i][j] = elem * number;
    }
  }
  int ret_val = s21_mult_number(&A, number, &result);
  int is_eq = s21_eq_matrix(&result, &check);
  ck_assert_int_eq(ret_val, OK);
  ck_assert_int_eq(is_eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t A = {0}, check = {0}, result = {0};
  int rows = 87, cols = 7;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &check);
  A.columns *= -1;
  double number = 4;
  int ret_val = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_4) {
  matrix_t A = {0}, check = {0}, result = {0};
  int rows = 87, cols = 7;
  double number = 4;
  int ret_val = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_5) {
  matrix_t A = {0}, check = {0}, result = {0};
  int rows = 1, cols = 1;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &check);
  A.columns = 0, A.rows = 0;
  double number = 4;
  int ret_val = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
}
END_TEST

// MULT_MATRIX

START_TEST(mult_matrix_1) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 3, cols = 3;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  s21_create_matrix(rows, cols, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
      A.matrix[i][j] = (double)(rand() % 3000) + 0.001;
    ;
  }
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++)
      B.matrix[i][j] = (double)(rand() % 3000) + 0.75;
  }
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < A.columns; k++) {
        check.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }
  int ret_val = s21_mult_matrix(&A, &B, &result);
  int is_eq = s21_eq_matrix(&result, &check);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
  ck_assert_int_eq(is_eq, SUCCESS);
  ck_assert_int_eq(ret_val, OK);
}
END_TEST

START_TEST(mult_matrix_2) {
  matrix_t A = {0}, B = {0}, check = {0}, result = {0};
  int rows = 15, cols = 15;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  s21_create_matrix(rows, cols, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
      A.matrix[i][j] = (double)(rand() % 3000) + 0.0071;
    ;
  }
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++)
      B.matrix[i][j] = (double)(rand() % 3000) + 0.7585;
  }
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < A.columns; k++) {
        check.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }
  int ret_val = s21_mult_matrix(&A, &B, &result);
  int is_eq = s21_eq_matrix(&result, &check);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
  ck_assert_int_eq(is_eq, SUCCESS);
  ck_assert_int_eq(ret_val, OK);
}
END_TEST

START_TEST(mult_matrix_3) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 15, cols = 14;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  int ret_val = s21_mult_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(ret_val, CALCULATION_ERROR);
}
END_TEST

START_TEST(mult_matrix_4) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 15, cols = 15;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  B.columns = 0;
  int ret_val = s21_mult_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

START_TEST(mult_matrix_5) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 15, cols = 15;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  A.rows = -3;
  int ret_val = s21_mult_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

START_TEST(mult_matrix_6) {
  matrix_t A = {0}, B = {0}, result = {0};
  int ret_val = s21_mult_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

// CALC_COMPLEMENTS

START_TEST(calc_complements_1) {
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

  int ret_val = s21_calc_complements(&A, &result);
  ck_assert_int_eq(ret_val, OK);
  int eq = s21_eq_matrix(&result, &check);
  ck_assert_int_eq(eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 5, &A);
  int ret_val = s21_calc_complements(&A, &result);
  ck_assert_int_eq(ret_val, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  A.rows = -3;
  int ret_val = s21_calc_complements(&A, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_4) {
  matrix_t A = {0}, result = {0};
  int ret_val = s21_calc_complements(&A, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

//  TRANSPOSE

START_TEST(transpose_1) {
  matrix_t A = {0}, check = {0}, result = {0};
  int rows = 4, cols = 2;
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(cols, rows, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = (double)(i + j);
    }
  }

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      check.matrix[i][j] = (double)(i + j);
    }
  }
  int ret_val = s21_transpose(&A, &result);
  int eq = s21_eq_matrix(&result, &check);
  ck_assert_int_eq(ret_val, OK);
  ck_assert_int_eq(eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A = {0}, check = {0}, result = {0};
  int rows = 4, cols = 9;
  s21_create_matrix(rows, cols, &A);
  A.rows = 0;
  int ret_val = s21_transpose(&A, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t A = {0}, check = {0}, result = {0};
  int rows = 4, cols = 9;
  int ret_val = s21_transpose(&A, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

// DETERMINANT

START_TEST(determinant_1) {
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
  int ret_val = s21_determinant(&A, &result);
  ck_assert_int_eq(ret_val, OK);
  ck_assert_int_eq(result, -40);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 4, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[1][3] = 3;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.matrix[2][3] = 2;
  double result = 0;
  int ret_val = s21_determinant(&A, &result);
  ck_assert_int_eq(ret_val, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  matrix_t A = {0};
  double result = 0;
  int ret_val = s21_determinant(&A, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

// INVERSE_MATRIX
START_TEST(inverse_matrix_1) {
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

  int ret_val = s21_inverse_matrix(&A, &result);
  int eq = s21_eq_matrix(&check, &result);
  ck_assert_int_eq(ret_val, OK);
  ck_assert_int_eq(eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(inverse_matrix_2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 0;
  int ret_val = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(ret_val, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_3) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 1, &A);
  A.matrix[0][0] = 0;
  A.matrix[1][0] = 0;
  int ret_val = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(ret_val, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_4) {
  matrix_t A = {0}, result = {0};
  ;
  int ret_val = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

START_TEST(inverse_matrix_5) {
  matrix_t A = {0}, check = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &check);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;

  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  check.matrix[0][0] = -2;
  check.matrix[0][1] = 1;

  check.matrix[1][0] = 1.5;
  check.matrix[1][1] = -0.5;

  int ret_val = s21_inverse_matrix(&A, &result);
  int eq = s21_eq_matrix(&check, &result);
  ck_assert_int_eq(ret_val, OK);
  ck_assert_int_eq(eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST
int main(void) {
  Suite *s = suite_create("MATIX_FUNCTIONS");
  SRunner *sr = srunner_create(s);

  TCase *tc_inverse_matrix = tcase_create("inverse_matrix");
  suite_add_tcase(s, tc_inverse_matrix);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_1);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_2);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_3);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_4);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_5);

  TCase *tc_determinant = tcase_create("determinant");
  suite_add_tcase(s, tc_determinant);
  tcase_add_test(tc_determinant, determinant_1);
  tcase_add_test(tc_determinant, determinant_2);
  tcase_add_test(tc_determinant, determinant_3);

  TCase *tc_transpose = tcase_create("transpose");
  suite_add_tcase(s, tc_transpose);
  tcase_add_test(tc_transpose, transpose_1);
  tcase_add_test(tc_transpose, transpose_2);
  tcase_add_test(tc_transpose, transpose_3);

  TCase *tc_calc_complements = tcase_create("calc_complements");
  suite_add_tcase(s, tc_calc_complements);
  tcase_add_test(tc_calc_complements, calc_complements_1);
  tcase_add_test(tc_calc_complements, calc_complements_2);
  tcase_add_test(tc_calc_complements, calc_complements_3);
  tcase_add_test(tc_calc_complements, calc_complements_4);

  TCase *tc_mult_matrix = tcase_create("mult_matrix");
  suite_add_tcase(s, tc_mult_matrix);
  tcase_add_test(tc_mult_matrix, mult_matrix_1);
  tcase_add_test(tc_mult_matrix, mult_matrix_2);
  tcase_add_test(tc_mult_matrix, mult_matrix_3);
  tcase_add_test(tc_mult_matrix, mult_matrix_4);
  tcase_add_test(tc_mult_matrix, mult_matrix_5);
  tcase_add_test(tc_mult_matrix, mult_matrix_6);

  TCase *tc_mult_number = tcase_create("mult_number");
  suite_add_tcase(s, tc_mult_number);
  tcase_add_test(tc_mult_number, mult_number_1);
  tcase_add_test(tc_mult_number, mult_number_2);
  tcase_add_test(tc_mult_number, mult_number_3);
  tcase_add_test(tc_mult_number, mult_number_4);
  tcase_add_test(tc_mult_number, mult_number_5);

  TCase *tc_sub_matrix = tcase_create("sub_matrix");
  suite_add_tcase(s, tc_sub_matrix);
  tcase_add_test(tc_sub_matrix, sub_matrix_1);
  tcase_add_test(tc_sub_matrix, sub_matrix_2);
  tcase_add_test(tc_sub_matrix, sub_matrix_3);
  tcase_add_test(tc_sub_matrix, sub_matrix_4);
  tcase_add_test(tc_sub_matrix, sub_matrix_5);
  tcase_add_test(tc_sub_matrix, sub_matrix_6);
  tcase_add_test(tc_sub_matrix, sub_matrix_7);

  TCase *tc_create = tcase_create("create_matrix");
  suite_add_tcase(s, tc_create);
  tcase_add_test(tc_create, create_matrix_1);
  tcase_add_test(tc_create, create_matrix_2);
  tcase_add_test(tc_create, create_matrix_3);
  tcase_add_test(tc_create, create_matrix_wrong_cols);
  tcase_add_test(tc_create, create_matrix_wrong_rows);

  TCase *tc_is_equal = tcase_create("is_equal");
  suite_add_tcase(s, tc_is_equal);
  tcase_add_test(tc_is_equal, is_equal);
  tcase_add_test(tc_is_equal, is_equal_1);
  tcase_add_test(tc_is_equal, is_equal_no);
  tcase_add_test(tc_is_equal, is_equal_no_2);
  tcase_add_test(tc_is_equal, is_equal_no_3);
  TCase *tc_sum_matrix = tcase_create("sum_matrix");
  suite_add_tcase(s, tc_sum_matrix);
  tcase_add_test(tc_sum_matrix, sum_matrix_1);
  tcase_add_test(tc_sum_matrix, sum_matrix_2);
  tcase_add_test(tc_sum_matrix, sum_matrix_3);
  tcase_add_test(tc_sum_matrix, sum_matrix_4);
  tcase_add_test(tc_sum_matrix, sum_matrix_5);
  tcase_add_test(tc_sum_matrix, sum_matrix_6);

  srunner_run_all(sr, CK_VERBOSE);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}