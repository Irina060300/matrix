#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = SUCCESS;
  result->matrix = malloc(sizeof(double *) * rows);
  if (result->matrix) {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = malloc(sizeof(double) * columns);
    }
    result->columns = columns;
    result->rows = rows;
  } else
    err = FAILURE;
  return err;
}
void print_matrix(matrix_t res) {
  if (res.matrix && is_correct_matrix(&res)) {
    for (int i = 0; i < res.rows; i++) {
      for (int j = 0; j < res.columns; j++) {
        printf("%7.3lf ", res.matrix[i][j]);
      }
      printf("\n");
    }
    printf("\n");
  } else {
    printf("Что-то пошло не так...\n");
  }
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
}
// int main() {
//     // matrix_t A, result;
//     // int rows_a = 3, cols_a = 3;
//     // s21_create_matrix(rows_a, cols_a, &A);
//     // A.matrix[0][0] = 1;
//     // A.matrix[0][1] = 2;
//     // A.matrix[0][2] = 3;
//     // A.matrix[1][0] = 0;
//     // A.matrix[1][1] = 4;
//     // A.matrix[1][2] = 2;
//     // A.matrix[2][0] = 5;
//     // A.matrix[2][1] = 2;
//     // A.matrix[2][2] = 1;
//     // // s21_create_matrix(rows_b, cols_b, &B);
//     // // for (int i = 0; i < rows_a; i++) {
//     // //     for (int j = 0; j < cols_a; j++) {
//     // //         A.matrix[i][j] =rand() % 15;
//     // //     }
//     // // }
//     // // for (int i = 0; i < rows_b; i++) {
//     // //     for (int j = 0; j < cols_b; j++) {
//     // //         B.matrix[i][j] = (double) (rand() % 50) / 2;
//     // //     }
//     // // }
//     // // int res = s21_sub_matrix(&A, &B, &result);
//     // //s21_transpose(&A, &result);
//     // print_matrix(A);

//     // // double ros = 0;
//     // // // int max_size = 5;
//     // // ros = det(&A, 3);
//     // //printf("RESSS %lf", ros);
//     // s21_inverse_matrix(&A, &result);
//     // print_matrix(result);
//     // s21_remove_matrix(&A);
//     // s21_remove_matrix(&result);
//     // // print_matrix(B);
//     unsigned int seed = 0;
//     const int rows = rand_r(&seed) % 100 + 1;
//     const int cols = rand_r(&seed) % 100 + 1;
//     matrix_t A = {0}, B = {0}, check = {0}, result = {0};
//     s21_create_matrix(rows, cols, &A);
//     s21_create_matrix(rows, cols, &B);
//     s21_create_matrix(rows, cols, &check);
//     double k = 0.1;
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             double rand_val = (double) (rand_r(&seed) % 3001 - 1500 + k);
//             A.matrix[i][j] = rand_val;
//             B.matrix[i][j] = rand_val + 0.015;
//             check.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
//             k += 0.000001;
//         }
//     }
//     s21_sum_matrix(&A, &B, &result);
//     int c = s21_eq_matrix(&check, &result);
//     printf("%d\n", c);
//     // print_matrix(check);
//     // print_matrix(result);
//     return 0;
// }

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err = SUCCESS;
  err = is_eq_size(A, B);
  if (err) {
    int rows = A->rows, cols = A->columns;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (fabs(A->matrix[i][j]) < 1e-300 && fabs(B->matrix[i][j]) < 1e-300)
          continue;
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-16) {
          err = FAILURE;
          // printf("A[%d][%d] = %.16lf, B[%d][%d] = %.16lf\n", i, j,
          // A->matrix[i][j], i, j, B->matrix[i][j]);
          break;
        }
      }
    }
  }
  return err;
}
int is_correct_matrix(matrix_t *mat) {
  int err = SUCCESS;
  if (mat) {
    if (!(mat->matrix && mat->columns > 0 && mat->rows > 0)) err = FAILURE;
  } else
    err = FAILURE;
  return err;
}
int is_eq_size(matrix_t *A, matrix_t *B) {
  int err = SUCCESS;
  if (A->columns != B->columns || A->rows != B->rows) {
    err = FAILURE;
  }
  return err;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = SUCCESS, correct_A = is_correct_matrix(A),
      correct_B = is_correct_matrix(B), is_eq = 0;
  if (correct_A && correct_B) {
    is_eq = is_eq_size(A, B);
    if (is_eq) {
      int rows = A->rows, cols = A->columns;
      if (s21_create_matrix(rows, cols, result)) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else
        err = FAILURE;
    } else
      err = FAILURE;
  } else
    err = FAILURE;
  return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = SUCCESS, correct_A = is_correct_matrix(A),
      correct_B = is_correct_matrix(B), is_eq = 0;
  if (correct_A && correct_B) {
    is_eq = is_eq_size(A, B);
    if (is_eq) {
      int rows = A->rows, cols = A->columns;
      if (s21_create_matrix(rows, cols, result)) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else
        err = FAILURE;
    } else
      err = FAILURE;
  } else
    err = FAILURE;
  return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = SUCCESS, correct_A = is_correct_matrix(A);
  if (correct_A) {
    int rows = A->rows, cols = A->columns;
    if (s21_create_matrix(rows, cols, result)) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
          if (fabs(A->matrix[i][j]) > 1e-300)
            result->matrix[i][j] = A->matrix[i][j] * number;
      }
    } else
      err = FAILURE;
  } else
    err = FAILURE;
  return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = SUCCESS, correct_A = is_correct_matrix(A),
      correct_B = is_correct_matrix(B);
  if (correct_A && correct_B) {
    int rows_a = A->rows, rows_b = B->rows, cols_a = A->columns,
        cols_b = B->columns;
    if (cols_a == rows_b) {
      int eq = rows_b;
      double sum = 0;
      if (s21_create_matrix(rows_a, cols_b, result)) {
        for (int i = 0; i < rows_a; i++) {
          for (int j = 0; j < cols_b; j++) {
            sum = 0;
            for (int k = 0; k < eq; k++) {
              sum += A->matrix[i][k] * B->matrix[k][j];
            }
            result->matrix[i][j] = sum;
          }
        }
      } else
        err = FAILURE;
    } else
      err = FAILURE;
  } else
    err = FAILURE;
  return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = SUCCESS, correct = is_correct_matrix(A);
  if (correct) {
    int rows = A->columns, cols = A->rows;
    if (s21_create_matrix(rows, cols, result)) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    } else
      err = FAILURE;
  } else
    err = FAILURE;
  return err;
}

double two_det(matrix_t *mat) {
  double res = mat->matrix[0][0] * mat->matrix[1][1] -
               mat->matrix[1][0] * mat->matrix[0][1];
  if (fabs(res) < 1e-30) res = 0;
  return res;
}

void cut_matrix(int no_i, int no_j, matrix_t *tmp, matrix_t *mat, int size) {
  int i_tmp = 0, j_tmp = 0;
  for (int i = 0; i < size; i++) {
    j_tmp = 0;
    for (int j = 0; j < size; j++) {
      if (i != no_i && j != no_j) {
        tmp->matrix[i_tmp][j_tmp] = mat->matrix[i][j];
        j_tmp++;
      }
    }
    if (i != no_i) i_tmp++;
  }
  // print_matrix(*tmp);
}

double det(matrix_t *mat, int size_matrix) {
  if (size_matrix == 1)
    return mat->matrix[0][0];
  else if (size_matrix == 2)
    return two_det(mat);
  else {
    double determ = 0.0, sign = 1;
    matrix_t tmp;
    s21_create_matrix(size_matrix, size_matrix, &tmp);
    for (int j = 0; j < size_matrix; j++) {
      cut_matrix(0, j, &tmp, mat, size_matrix);
      determ += sign * mat->matrix[0][j] * det(&tmp, size_matrix - 1);
      sign = -sign;
    }
    s21_remove_matrix(&tmp);
    return determ;
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int err = SUCCESS, correct = is_correct_matrix(A);
  if (correct) {
    int rows = A->rows, cols = A->columns;
    if (rows == cols) {
      *result = det(A, rows);
    } else
      err = FAILURE;
  } else
    err = FAILURE;
  return err;
}
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = SUCCESS, correct = is_correct_matrix(A);
  if (correct) {
    int rows = A->rows, cols = A->columns;
    if (rows == cols) {
      matrix_t tmp;
      s21_create_matrix(rows, cols, &tmp);
      s21_create_matrix(rows, cols, result);
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          cut_matrix(i, j, &tmp, A, rows);
          result->matrix[i][j] = det(&tmp, rows - 1);
        }
      }
      s21_remove_matrix(&tmp);
    } else
      err = FAILURE;
  } else
    err = FAILURE;
  return err;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = SUCCESS, correct = is_correct_matrix(A);
  if (correct) {
    int rows = A->rows, cols = A->columns;
    if (rows == cols) {
      double determ;
      determ = det(A, 3);

      if (fabs(determ) < 1e-60)
        err = FAILURE;
      else {
        matrix_t minor_matrix, transposed_minmat;
        s21_calc_complements(A, &minor_matrix);
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
            if ((i + j) % 2 == 1) minor_matrix.matrix[i][j] *= -1;
          }
        }

        s21_transpose(&minor_matrix, &transposed_minmat);
        double koef = 1.0 / determ;
        s21_mult_number(&transposed_minmat, koef, result);
        s21_remove_matrix(&minor_matrix);
        s21_remove_matrix(&transposed_minmat);
      }
    } else
      err = FAILURE;
  } else
    err = FAILURE;
  return err;
}