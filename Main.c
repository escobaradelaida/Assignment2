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
            (*matrix)[i][j] = rand() % 10; // Adjust the range as needed
        }
    }
}

// Function to write a matrix to a file
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

int main(int argc, char* argv[]) {
    if (argc == 2) {
        // Case: Generate random matrices based on an integer input
        int size = atoi(argv[1]);

        if (size <= 0) {
            printf("Invalid size argument. Please provide a positive integer.\n");
            exit(1);
        }

        int** matrix1;
        int** matrix2;

        // Generate random matrices
        generateRandomMatrix(&matrix1, size);
        generateRandomMatrix(&matrix2, size);

        // Write the matrices to files
        writeMatrixToFile("matrix1.txt", matrix1, size);
        writeMatrixToFile("matrix2.txt", matrix2, size);

        int** result;
        multiplyMatrices(matrix1, matrix2, &result, size);

        // Clean up: free allocated memory
        // ...

    } else {
        printf("Invalid number of command line arguments.\n");
        printf("Usage: %s size\n", argv[0]);
        return 1; // Exit with an error code
    }

    return 0;
}