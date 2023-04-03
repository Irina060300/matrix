#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0

enum  enum_error{
    OK,
    INCORRECT_MATRIX,
    CALCULATION_ERROR
};
void print_matrix(matrix_t res);
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int is_eq_size(matrix_t *A, matrix_t *B);
int is_correct_matrix(matrix_t *mat);
void cut_matrix(int no_i, int no_j, matrix_t *tmp, matrix_t *mat, int size);
void mat_det (matrix_t *mat, int size, double *result, int max_size);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
double det(matrix_t *mat, int size_matrix);
#endif  //  S21_MATRIX_H