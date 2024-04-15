#include <stdio.h>
#include <stdlib.h>
#include "explicit_data.h"

// Function to read edge weights from a full matrix
double **readFullMatrix(FILE *file, int numNodes, long int filePosition) {
    double **matrix = (double **) calloc(numNodes, sizeof(double *));
    for (int i = 0; i < numNodes; i++) {
        matrix[i] = (double *) calloc(numNodes, sizeof(double));
    }

    fseek(file, filePosition, SEEK_SET);

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            double t = 0;
            fscanf(file, "%lf", &t);
            matrix[i][j] = t;
        }
    }

    return matrix;
}

// Function to read edge weights from an upper triangular matrix row-wise without diagonal entries
double **readUpperRow(FILE *file, int numNodes, long int filePosition) {
    double **matrix = (double **) calloc(numNodes, sizeof(double *));
    for (int i = 0; i < numNodes; i++) {
        matrix[i] = (double *) calloc(numNodes, sizeof(double));
    }

    fseek(file, filePosition, SEEK_SET);

    for (int i = 0; i < numNodes; i++) {
        for (int j = i + 1; j < numNodes; j++) { // Only read upper triangle
            double t = 0;
            fscanf(file, "%lf", &t);
            matrix[i][j] = t;
        }
    }

    return matrix;
}

// Function to read edge weights from a lower triangular matrix row-wise without diagonal entries
double **readLowerRow(FILE *file, int numNodes, long int filePosition) {
    double **matrix = (double **) calloc(numNodes, sizeof(double *));
    for (int i = 0; i < numNodes; i++) {
        matrix[i] = (double *) calloc(numNodes, sizeof(double));
    }

    fseek(file, filePosition, SEEK_SET);

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < i; j++) { // Only read lower triangle
            double t = 0;
            fscanf(file, "%lf", &t);
            matrix[i][j] = t;
        }
    }

    return matrix;
}

// Function to read edge weights from an upper triangular matrix row-wise including diagonal entries
double **readUpperDiagRow(FILE *file, int numNodes, long int filePosition) {
    double **matrix = (double **) calloc(numNodes, sizeof(double *));
    for (int i = 0; i < numNodes; i++) {
        matrix[i] = (double *) calloc(numNodes, sizeof(double));
    }

    fseek(file, filePosition, SEEK_SET);

    for (int i = 0; i < numNodes; i++) {
        for (int j = i; j < numNodes; j++) { // Read upper triangle with diagonal
            double t = 0;
            fscanf(file, "%lf", &t);
            matrix[i][j] = t;
        }
    }

    return matrix;
}

// Function to read edge weights from a lower triangular matrix row-wise including diagonal entries
double **readLowerDiagRow(FILE *file, int numNodes, long int filePosition) {
    double **matrix = (double **) calloc(numNodes, sizeof(double *));
    for (int i = 0; i < numNodes; i++) {
        matrix[i] = (double *) calloc(numNodes, sizeof(double));
    }

    fseek(file, filePosition, SEEK_SET);

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j <= i; j++) { // Read lower triangle with diagonal
            double t = 0;
            fscanf(file, "%lf", &t);
            matrix[i][j] = t;
        }
    }

    return matrix;
}

// Function to read edge weights from an upper triangular matrix column-wise without diagonal entries
double **readUpperCol(FILE *file, int numNodes, long int filePosition) {
    double **matrix = (double **) calloc(numNodes, sizeof(double *));
    for (int i = 0; i < numNodes; i++) {
        matrix[i] = (double *) calloc(numNodes, sizeof(double));
    }

    fseek(file, filePosition, SEEK_SET);

    for (int j = 0; j < numNodes; j++) {
        for (int i = 0; i < j; i++) { // Read upper triangle
            double t = 0;
            fscanf(file, "%lf", &t);
            matrix[i][j] = t;
        }
    }

    return matrix;
}

// Function to read edge weights from a lower triangular matrix column-wise without diagonal entries
double **readLowerCol(FILE *file, int numNodes, long int filePosition) {
    double **matrix = (double **) calloc(numNodes, sizeof(double *));
    for (int i = 0; i < numNodes; i++) {
        matrix[i] = (double *) calloc(numNodes, sizeof(double));
    }

    fseek(file, filePosition, SEEK_SET);

    for (int j = 0; j < numNodes; j++) {
        for (int i = j + 1; i < numNodes; i++) { // Read lower triangle
            double t = 0;
            fscanf(file, "%lf", &t);
            matrix[i][j] = t;
        }
    }

    return matrix;
}

// Function to read edge weights from an upper triangular matrix column-wise including diagonal entries
double **readUpperDiagCol(FILE *file, int numNodes, long int filePosition) {
    double **matrix = (double **) calloc(numNodes, sizeof(double *));
    for (int i = 0; i < numNodes; i++) {
        matrix[i] = (double *) calloc(numNodes, sizeof(double));
    }

    fseek(file, filePosition, SEEK_SET);

    for (int j = 0; j < numNodes; j++) {
        for (int i = j; i < numNodes; i++) { // Read upper triangle with diagonal
            double t = 0;
            fscanf(file, "%lf", &t);
            matrix[i][j] = t;
        }
    }

    return matrix;
}

// Function to read edge weights from a lower triangular matrix column-wise including diagonal entries
double **readLowerDiagCol(FILE *file, int numNodes, long int filePosition) {
    double **matrix = (double **) calloc(numNodes, sizeof(double *));
    for (int i = 0; i < numNodes; i++) {
        matrix[i] = (double *) calloc(numNodes, sizeof(double));
    }

    fseek(file, filePosition, SEEK_SET);

    for (int j = 0; j < numNodes; j++) {
        for (int i = 0; i <= j; i++) { // Read lower triangle with diagonal
            double t = 0;
            fscanf(file, "%lf", &t);
            matrix[i][j] = t;
        }
    }

    return matrix;
}

//read demand matrix
int *readDemand(FILE *file, int numNodes, long int filePosition) {
    int *demand = (int *) calloc(numNodes, sizeof(int));

    fseek(file, filePosition, SEEK_SET);

    for (int i = 0; i < numNodes; i++) {
        int t = 0, a;
        char buffer[100];
        fgets(buffer, 100, file);
        sscanf(buffer, "%d %d", &a, &t);
        demand[i] = t;
    }

    return demand;
}
