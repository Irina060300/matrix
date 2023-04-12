#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = OK;
  if (result) {
    if (rows > 0 && columns > 0) {
      result->matrix = malloc(sizeof(double *) * rows);
      if (result->matrix) {
        for (int i = 0; i < rows; i++) {
          result->matrix[i] = malloc(sizeof(double) * columns);
        }
        result->columns = columns;
        result->rows = rows;
      } else {
        err = INCORRECT_MATRIX;
      }
    } else
      err = INCORRECT_MATRIX;
  } else
    err = INCORRECT_MATRIX;
  return err;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->columns = 0;
  A->rows = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err = SUCCESS, correct_A = is_correct_matrix(A),
      correct_B = is_correct_matrix(B);
  if (correct_A && correct_B) {
    err = is_eq_size(A, B);
    if (err) {
      int rows = A->rows, cols = A->columns;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          if (fabs(A->matrix[i][j]) < 1e-300 && fabs(B->matrix[i][j]) < 1e-300)
            continue;
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
            err = FAILURE;
            break;
          }
        }
      }
    }
  } else
    err = FAILURE;
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
  int err = OK, correct_A = is_correct_matrix(A),
      correct_B = is_correct_matrix(B), is_eq = 0;
  if (correct_A && correct_B) {
    is_eq = is_eq_size(A, B);
    if (is_eq) {
      int rows = A->rows, cols = A->columns;
      if (s21_create_matrix(rows, cols, result) == OK) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else
        err = INCORRECT_MATRIX;
    } else
      err = CALCULATION_ERROR;
  } else
    err = INCORRECT_MATRIX;
  return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = OK, correct_A = is_correct_matrix(A),
      correct_B = is_correct_matrix(B), is_eq = 0;
  if (correct_A && correct_B) {
    is_eq = is_eq_size(A, B);
    if (is_eq) {
      int rows = A->rows, cols = A->columns;
      if (s21_create_matrix(rows, cols, result) == OK) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else
        err = INCORRECT_MATRIX;
    } else
      err = CALCULATION_ERROR;
  } else
    err = INCORRECT_MATRIX;
  return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = OK, correct_A = is_correct_matrix(A);
  if (correct_A) {
    int rows = A->rows, cols = A->columns;
    if (s21_create_matrix(rows, cols, result) == OK) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
          if (fabs(A->matrix[i][j]) > 1e-300)
            result->matrix[i][j] = A->matrix[i][j] * number;
      }
    } else
      err = INCORRECT_MATRIX;
  } else
    err = INCORRECT_MATRIX;
  return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = OK, correct_A = is_correct_matrix(A),
      correct_B = is_correct_matrix(B);
  if (correct_A && correct_B) {
    int rows_a = A->rows, rows_b = B->rows, cols_a = A->columns,
        cols_b = B->columns;
    if (cols_a == rows_b) {
      int eq = rows_b;
      double sum = 0;
      if (s21_create_matrix(rows_a, cols_b, result) == OK) {
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
        err = INCORRECT_MATRIX;
    } else
      err = CALCULATION_ERROR;
  } else
    err = INCORRECT_MATRIX;
  return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = OK, correct = is_correct_matrix(A);
  if (correct) {
    int rows = A->columns, cols = A->rows;
    if (s21_create_matrix(rows, cols, result) == OK) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    } else
      err = INCORRECT_MATRIX;
  } else
    err = INCORRECT_MATRIX;
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
  int err = OK, correct = is_correct_matrix(A);
  if (correct) {
    int rows = A->rows, cols = A->columns;
    if (rows == cols) {
      *result = det(A, rows);
    } else
      err = CALCULATION_ERROR;
  } else
    err = INCORRECT_MATRIX;
  return err;
}
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = OK, correct = is_correct_matrix(A);
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
          if ((i + j) % 2 != 0) result->matrix[i][j] *= -1;
        }
      }
      s21_remove_matrix(&tmp);
    } else
      err = CALCULATION_ERROR;
  } else
    err = INCORRECT_MATRIX;
  return err;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = OK, correct = is_correct_matrix(A);
  if (correct) {
    int rows = A->rows, cols = A->columns;
    if (rows == cols) {
      double determ;
      determ = det(A, rows);
      if (fabs(determ) < 1e-60)
        err = CALCULATION_ERROR;
      else {
        matrix_t minor_matrix, transposed_minmat;
        s21_calc_complements(A, &minor_matrix);
        s21_transpose(&minor_matrix, &transposed_minmat);
        double koef = 1.0 / determ;
        s21_mult_number(&transposed_minmat, koef, result);
        s21_remove_matrix(&minor_matrix);
        s21_remove_matrix(&transposed_minmat);
      }
    } else
      err = CALCULATION_ERROR;
  } else
    err = INCORRECT_MATRIX;
  return err;
}
