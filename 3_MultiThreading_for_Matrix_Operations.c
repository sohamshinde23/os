#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int n, **matrix1, **matrix2, **resultantMatrix;

void *takeInput(void *args) {
    int **ptr = (int **)args;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter element at index %d, %d: ", i, j);
            scanf("%d", &ptr[i][j]);
        }
    }
    return NULL;
}

void *printMatrix(void *args) {
    int **ptr = (int **)args;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", ptr[i][j]);
        }
        printf("\n");
    }
    return NULL;
}

void *addMatrix(void *args) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultantMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return NULL;
}

void *subMatrix(void *args) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultantMatrix[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return NULL;
}

void *multiplyMatrix(void *args) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;  // Reset sum for each element
            for (int k = 0; k < n; k++) {
                sum += (matrix1[i][k] * matrix2[k][j]);
            }
            resultantMatrix[i][j] = sum;
        }
    }
    return NULL;
}

int main() {
    printf("Enter rows/columns of matrix: ");
    scanf("%d", &n);

    // Allocate memory for matrices
    matrix1 = (int **)malloc(sizeof(int *) * n);
    matrix2 = (int **)malloc(sizeof(int *) * n);
    resultantMatrix = (int **)malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++) {
        matrix1[i] = (int *)malloc(sizeof(int) * n);
        matrix2[i] = (int *)malloc(sizeof(int) * n);
        resultantMatrix[i] = (int *)malloc(sizeof(int) * n);
    }

    pthread_t t1, t2;

    printf("\n\nFor matrix 1:\n");
    pthread_create(&t1, NULL, takeInput, (void *)matrix1);
    pthread_join(t1, NULL);

    printf("\n\nFor matrix 2:\n");
    pthread_create(&t2, NULL, takeInput, (void *)matrix2);
    pthread_join(t2, NULL);

    printf("\n\nMatrix 1:\n");
    pthread_create(&t1, NULL, printMatrix, (void *)matrix1);
    pthread_join(t1, NULL);

    printf("\n\nMatrix 2:\n");
    pthread_create(&t2, NULL, printMatrix, (void *)matrix2);
    pthread_join(t2, NULL);

    pthread_t threadForAddition, threadForSubtraction, threadForMatrixMultiplication;

    pthread_create(&threadForAddition, NULL, addMatrix, NULL);
    pthread_join(threadForAddition, NULL);
    printf("\nAddition of 2 matrices:\n");
    pthread_create(&threadForAddition, NULL, printMatrix, (void *)resultantMatrix);
    pthread_join(threadForAddition, NULL);

    pthread_create(&threadForSubtraction, NULL, subMatrix, NULL);
    pthread_join(threadForSubtraction, NULL);
    printf("\nSubtraction of 2 matrices:\n");
    pthread_create(&threadForSubtraction, NULL, printMatrix, (void *)resultantMatrix);
    pthread_join(threadForSubtraction, NULL);

    pthread_create(&threadForMatrixMultiplication, NULL, multiplyMatrix, NULL);
    pthread_join(threadForMatrixMultiplication, NULL);
    printf("\nMatrix Multiplication of 2 matrices:\n");
    pthread_create(&threadForMatrixMultiplication, NULL, printMatrix, (void *)resultantMatrix);
    pthread_join(threadForMatrixMultiplication, NULL);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
        free(resultantMatrix[i]);
    }

    free(matrix1);
    free(matrix2);
    free(resultantMatrix);

    return 0;
}