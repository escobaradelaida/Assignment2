#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random square matrix
void generateRandomMatrix(int*** matrix, int size) {
    srand(time(NULL));

    // Allocate memory for the matrix
    *matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        (*matrix)[i] = (int*)malloc(size * sizeof(int));
    }

    // Fill the matrix with random values
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            (*matrix)[i][j] = rand() % 10; // It would be preferred if the user enters an input less than 10
        }
    }
}

// Function to write a matrix to a file. this function will be called twice to create two separate files for each matrix
void writeMatrixToFile(const char* filename, int** matrix, int size) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    // Write size to the file
    fprintf(file, "%d\n", size);

    // Write matrix elements to the file
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to perform matrix multiplication
void multiplyMatrices(int** matrix1, int** matrix2, int*** result, int size) {
    // Allocate memory for the result matrix
    *result = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        (*result)[i] = (int*)malloc(size * sizeof(int));
    }

    // Perform matrix multiplication
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            (*result)[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                (*result)[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// Function to write a matrix to a file. This will be the third file, matrix3.txt
void writeResultToFile(const char* filename, int** result, int size) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    // Write size to the file
    fprintf(file, "%d\n", size);

    // Write matrix elements to the file
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(file, "%d ", result[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    int size;

    // Check if an integer input is provided
    if (argc == 2) {
        // Use the provided integer from command line
        size = atoi(argv[1]);

        if (size <= 0) {
            printf("Invalid size argument. Please provide a positive integer.\n");
            exit(1);
        }
    } else {
        // Prompt the user for an integer input. We want the user to input an integer that is at least 2 or higher
        printf("Enter the size of the square matrices: ");
        if (scanf("%d", &size) != 1 || size <= 0) {
            printf("Invalid input. Please enter a positive integer.\n");
            exit(1);
        }
    }

    int** matrix1;
    int** matrix2;
    int** result;

    // Generate random matrices
    generateRandomMatrix(&matrix1, size);
    generateRandomMatrix(&matrix2, size);

    // Write the matrices to files
    writeMatrixToFile("matrix1.txt", matrix1, size);
    writeMatrixToFile("matrix2.txt", matrix2, size);

    // Perform the matrix multiplication
    multiplyMatrices(matrix1, matrix2, &result, size);

    // Write the result matrix to a file
    writeResultToFile("matrix3.txt", result, size);

    printf("Matrix multiplication completed. Result matrix written to matrix3.txt\n"); //user will have to open up the matrix.txt to open result

    return 0;
}
