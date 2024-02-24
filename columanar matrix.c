#include <stdio.h>

void createColumnarMatrix(int rows, int cols, int matrix[rows][cols]) {
    int num = 1;

    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            matrix[row][col] = num;
            num++;
        }
    }
}

void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("%d\t", matrix[row][col]);
        }
        printf("\n");
    }
}

int main() {
    // Example usage
    int rows = 3;
    int cols = 4;
    int columnarMatrix[rows][cols];

    createColumnarMatrix(rows, cols, columnarMatrix);
    printMatrix(rows, cols, columnarMatrix);

    return 0;
}
