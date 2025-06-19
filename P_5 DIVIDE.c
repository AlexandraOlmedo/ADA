#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_power_of_two(int n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

int** allocate_matrix(int n) {
    int** mat = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        mat[i] = calloc(n, sizeof(int));
    return mat;
}

void free_matrix(int n, int** mat) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void generate_matrix(int n, int** A, int** B) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
}

void traditional_mult(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
}

void add(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Divide and Conquer Multiplication
void dac_mult(int n, int** A, int** B, int** C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;

    // Submatrices
    int** A11 = allocate_matrix(newSize);
    int** A12 = allocate_matrix(newSize);
    int** A21 = allocate_matrix(newSize);
    int** A22 = allocate_matrix(newSize);

    int** B11 = allocate_matrix(newSize);
    int** B12 = allocate_matrix(newSize);
    int** B21 = allocate_matrix(newSize);
    int** B22 = allocate_matrix(newSize);

    int** C11 = allocate_matrix(newSize);
    int** C12 = allocate_matrix(newSize);
    int** C21 = allocate_matrix(newSize);
    int** C22 = allocate_matrix(newSize);

    int** temp1 = allocate_matrix(newSize);
    int** temp2 = allocate_matrix(newSize);

    // Dividir matrices A y B
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }

    // C11 = A11*B11 + A12*B21
    dac_mult(newSize, A11, B11, temp1);
    dac_mult(newSize, A12, B21, temp2);
    add(newSize, temp1, temp2, C11);

    // C12 = A11*B12 + A12*B22
    dac_mult(newSize, A11, B12, temp1);
    dac_mult(newSize, A12, B22, temp2);
    add(newSize, temp1, temp2, C12);

    // C21 = A21*B11 + A22*B21
    dac_mult(newSize, A21, B11, temp1);
    dac_mult(newSize, A22, B21, temp2);
    add(newSize, temp1, temp2, C21);

    // C22 = A21*B12 + A22*B22
    dac_mult(newSize, A21, B12, temp1);
    dac_mult(newSize, A22, B22, temp2);
    add(newSize, temp1, temp2, C22);

    // Combinar C11..C22 en C
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }

    free_matrix(newSize, A11); free_matrix(newSize, A12); free_matrix(newSize, A21); free_matrix(newSize, A22);
    free_matrix(newSize, B11); free_matrix(newSize, B12); free_matrix(newSize, B21); free_matrix(newSize, B22);
    free_matrix(newSize, C11); free_matrix(newSize, C12); free_matrix(newSize, C21); free_matrix(newSize, C22);
    free_matrix(newSize, temp1); free_matrix(newSize, temp2);
}

// Strassen’s Multiplication
void strassen_mult(int n, int** A, int** B, int** C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int** A11 = allocate_matrix(newSize);
    int** A12 = allocate_matrix(newSize);
    int** A21 = allocate_matrix(newSize);
    int** A22 = allocate_matrix(newSize);

    int** B11 = allocate_matrix(newSize);
    int** B12 = allocate_matrix(newSize);
    int** B21 = allocate_matrix(newSize);
    int** B22 = allocate_matrix(newSize);

    int** M1 = allocate_matrix(newSize);
    int** M2 = allocate_matrix(newSize);
    int** M3 = allocate_matrix(newSize);
    int** M4 = allocate_matrix(newSize);
    int** M5 = allocate_matrix(newSize);
    int** M6 = allocate_matrix(newSize);
    int** M7 = allocate_matrix(newSize);

    int** tempA = allocate_matrix(newSize);
    int** tempB = allocate_matrix(newSize);

    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }

    add(newSize, A11, A22, tempA);
    add(newSize, B11, B22, tempB);
    strassen_mult(newSize, tempA, tempB, M1);

    add(newSize, A21, A22, tempA);
    strassen_mult(newSize, tempA, B11, M2);

    subtract(newSize, B12, B22, tempB);
    strassen_mult(newSize, A11, tempB, M3);

    subtract(newSize, B21, B11, tempB);
    strassen_mult(newSize, A22, tempB, M4);

    add(newSize, A11, A12, tempA);
    strassen_mult(newSize, tempA, B22, M5);

    subtract(newSize, A21, A11, tempA);
    add(newSize, B11, B12, tempB);
    strassen_mult(newSize, tempA, tempB, M6);

    subtract(newSize, A12, A22, tempA);
    add(newSize, B21, B22, tempB);
    strassen_mult(newSize, tempA, tempB, M7);

    int** C11 = allocate_matrix(newSize);
    int** C12 = allocate_matrix(newSize);
    int** C21 = allocate_matrix(newSize);
    int** C22 = allocate_matrix(newSize);

    add(newSize, M1, M4, tempA);
    subtract(newSize, tempA, M5, tempB);
    add(newSize, tempB, M7, C11);

    add(newSize, M3, M5, C12);
    add(newSize, M2, M4, C21);

    add(newSize, M1, M3, tempA);
    subtract(newSize, tempA, M2, tempB);
    add(newSize, tempB, M6, C22);

    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }

    free_matrix(newSize, A11); free_matrix(newSize, A12); free_matrix(newSize, A21); free_matrix(newSize, A22);
    free_matrix(newSize, B11); free_matrix(newSize, B12); free_matrix(newSize, B21); free_matrix(newSize, B22);
    free_matrix(newSize, M1); free_matrix(newSize, M2); free_matrix(newSize, M3); free_matrix(newSize, M4);
    free_matrix(newSize, M5); free_matrix(newSize, M6); free_matrix(newSize, M7);
    free_matrix(newSize, C11); free_matrix(newSize, C12); free_matrix(newSize, C21); free_matrix(newSize, C22);
    free_matrix(newSize, tempA); free_matrix(newSize, tempB);
}

int main() {
    int n;
    printf("Introduce el tamaño de la matriz (potencia de 2): ");
    scanf("%d", &n);

    if (!is_power_of_two(n)) {
        printf("Error: El número no es potencia de 2.\n");
        return 1;
    }

    srand(time(NULL));
    int** A = allocate_matrix(n);
    int** B = allocate_matrix(n);
    int** C = allocate_matrix(n);

    generate_matrix(n, A, B);

    clock_t start, end;

    start = clock();
    traditional_mult(n, A, B, C);
    end = clock();
    printf("Tiempo Tradicional: %.6f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    dac_mult(n, A, B, C);
    end = clock();
    printf("Tiempo Divide and Conquer: %.6f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    strassen_mult(n, A, B, C);
    end = clock();
    printf("Tiempo Strassen: %.6f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    free_matrix(n, A);
    free_matrix(n, B);
    free_matrix(n, C);

    return 0;
}
