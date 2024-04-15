#ifndef UNTITLED_EXPLICIT_DATA_H
#define UNTITLED_EXPLICIT_DATA_H

// Function to read full explicit matrix from a TSPLIB file
double **readFullMatrix(FILE *file, int numNodes,long int filePosition);
double **readUpperRow(FILE *file, int numNodes,long int filePosition);
double **readLowerRow(FILE *file, int numNodes,long int filePosition);
double **readUpperDiagRow(FILE *file, int numNodes,long int filePosition);
double **readLowerDiagRow(FILE *file, int numNodes,long int filePosition);
double **readUpperCol(FILE *file, int numNodes,long int filePosition);
double **readLowerCol(FILE *file, int numNodes,long int filePosition);
double **readUpperDiagCol(FILE *file, int numNodes,long int filePosition);
double **readLowerDiagCol(FILE *file, int numNodes,long int filePosition);
int *readDemand(FILE *file, int numNodes, long int filePosition);
double **makeSymmetrical(double **matrix, int numNodes);

#endif //UNTITLED_EXPLICIT_DATA_H
