#include "s21_matrix.h"
#include <stdio.h>
#include <stdlib.h>
int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int err = SUCCESS;
    result->matrix = malloc(sizeof(double *)* rows);
    if (result->matrix) {
        for (int i = 0; i < rows; i++) {
            result->matrix[i] = malloc(sizeof(double) * columns);
        }
        result->columns = columns;
        result->rows = rows;
    } else err = FAILURE;
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
int main() {
    matrix_t A, B, result;
    int rows_a = 4, cols_a = 4, rows_b = 3, cols_b = 3;
    s21_create_matrix(rows_a, cols_a, &A);
    // s21_create_matrix(rows_b, cols_b, &B);
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_a; j++) {
            A.matrix[i][j] =rand() % 20;
        }
    }
    // for (int i = 0; i < rows_b; i++) {
    //     for (int j = 0; j < cols_b; j++) {
    //         B.matrix[i][j] = (double) (rand() % 50) / 2;
    //     }
    // }
    // int res = s21_sub_matrix(&A, &B, &result);
    //s21_transpose(&A, &result);
    print_matrix(A);

    double ros = 0;
    int max_size = 4;
    mat_det(&A, 4, &ros, max_size); 
    printf("RESSS %lf", ros);
    // print_matrix(B);
    //print_matrix(result);
    return 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int err = SUCCESS;
    err = is_eq_size(A, B);
    if (err) {
        int rows = A->rows, cols = A->columns;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (A->matrix[i][j] != B->matrix[i][j]) {
                    err = FAILURE;
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
    } else err = FAILURE;
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
    int err = SUCCESS, correct_A = is_correct_matrix(A), correct_B = is_correct_matrix(B), is_eq = 0;
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
            } else err = FAILURE;
        } else err = FAILURE;
    } else err = FAILURE;
    return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err = SUCCESS, correct_A = is_correct_matrix(A), correct_B = is_correct_matrix(B), is_eq = 0;
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
            } else err = FAILURE;
        } else err = FAILURE;
    } else err = FAILURE;
    return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int err = SUCCESS, correct_A = is_correct_matrix(A);
    if (correct_A) {
        int rows = A->rows, cols = A->columns;
        if (s21_create_matrix(rows, cols, result)) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) 
                    result->matrix[i][j] = A->matrix[i][j] * number;
            }
        } else err = FAILURE;
    } else err = FAILURE;
    return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err = SUCCESS, correct_A = is_correct_matrix(A), correct_B = is_correct_matrix(B);
    if (correct_A && correct_B) {
        int rows_a = A->rows, rows_b = B->rows, cols_a = A->columns, cols_b = B->columns;
        if (cols_a == rows_b) {
            int eq = rows_b;
            double sum = 0;
            if (s21_create_matrix(rows_a, cols_b, result)) {
                for (int i = 0; i < rows_a; i++) {
                    for (int j = 0; j < cols_b; j++) {
                        sum = 0;
                        for (int k = 0; k < eq; k++) {
                            sum += A->matrix[i][k]* B->matrix[k][j];
                        }
                        result->matrix[i][j] = sum;
                    }
                }
            } else err = FAILURE;
        } else err = FAILURE;
    } else err = FAILURE;
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
        } else err = FAILURE;
    } else err = FAILURE;
    return err;
}

double two_det (matrix_t *mat) { return mat->matrix[0][0]* mat->matrix[1][1] 
- mat->matrix[1][0]* mat->matrix[0][1];}

void cut_matrix(int no, matrix_t *tmp, matrix_t *mat, int size) {
    int i_tmp = 0, j_tmp = 0;
    for (int i = 0; i < size; i++) {
        j_tmp = 0;
        for (int j = 0; j < size; j++) {
            if (i != 0 && j != no) {
                tmp->matrix[i_tmp][j_tmp] = mat->matrix[i][j];
                j_tmp++;
            }
        }
        if (i != 0) i_tmp++;
    }
    //print_matrix(*tmp);
}

void mat_det (matrix_t *mat, int size, double *result, int max_size) {
    matrix_t tmp; 
    int tmp_size = 0;
    static double res;
    int flag = 0;
    for (int i = 0; i < size; i++) {
        tmp_size = size - 1;
        s21_create_matrix(tmp_size, tmp_size, &tmp);
        if (size > 2) {
            cut_matrix(i, &tmp, mat, size);
            mat_det (&tmp, tmp_size, result, max_size);
        }
        if (tmp_size == 2) {
            double two_de = two_det(&tmp);
            if (i % 2 != 0) res += mat->matrix[0][i] * two_de;
            else res -= mat->matrix[0][i] * two_de;
            //print_matrix(tmp);
            s21_remove_matrix(&tmp);
            //printf("%lf\n", res);
        }
        if (size == max_size) {
            printf("mat[0] = %lf\n", mat->matrix[0][i]);
            if (i % 2 == 0) (*result) +=  mat->matrix[0][i]* res;
            else (*result) -=  mat->matrix[0][i]*res;
            printf("%lf\n", *result / mat->matrix[0][i]);
        }
    }
}

// void det(matrix_t *matrix_t, int size_matrix, double *result) {
    


// }

int s21_determinant(matrix_t *A, double *result) {
    int err = SUCCESS, correct = is_correct_matrix(A);
    if (correct) {
        int rows = A->rows, cols = A->columns;
        if (rows == cols) {

        } else err = FAILURE;
    } else err = FAILURE;
    return err;
}
int s21_calc_complements(matrix_t *A, matrix_t *result) {


}
