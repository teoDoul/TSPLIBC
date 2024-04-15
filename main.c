#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "distance_calculator.h"
#include "explicit_data.h"
#include "node.h"



// Function to determine the file type based on its suffix
int suffix(char str[100]) {
    char *dot_pos = strrchr(str, '.');
    if (dot_pos != NULL) {
        if (strcmp(dot_pos, ".tsp") == 0) {
            return 1; // TSP
        } else if (strcmp(dot_pos, ".atsp") == 0) {
            return 2; // ATSP
        } else if (strcmp(dot_pos, ".vrp") == 0) {
            return 3; // CVRP
        } else {
            return -1; // Unknown
        }
    } else {
        printf("File does not have a valid suffix\n");
        return -1;
    }
}

int checkDim(char edgeWeightType[50]){
    if(strchr(edgeWeightType,'2') != NULL){
        return 2;
    }else if(strchr(edgeWeightType,'3') != NULL){
        return 3;
    }else{
        return -1;
    }
}



int main() {
    FILE *file, *outputFile;
    char filename[100];
    int numNodes = 0, t;


    // Ask user for the TSPLIB file name
    printf("Enter the TSPLIB file name: ");
    scanf("%s", filename);

    // Open the TSPLIB file
    file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }

    // Determine the file type based on its suffix
    int fileType = suffix(filename);
    if (fileType == -1) {
        fprintf(stderr, "Unknown file type\n");
        fclose(file);
        return 1;
    }

    char buffer[100];
    char edgeWeightType[50];
    int capacity = 0;

    if (fileType == 1 || fileType == 3) {

        // Read the file and extract necessary information
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            if (strstr(buffer, "DIMENSION") != NULL) {
                // Extract the number of nodes from the "DIMENSION" line
                if (sscanf(buffer, "DIMENSION : %d", &numNodes) != 1) {
                    fprintf(stderr, "Error reading the number of nodes.\n");
                    fclose(file);
                    return 1;
                }
                continue;
            }
            if (strstr(buffer, "EDGE_WEIGHT_TYPE") != NULL) {
                // Extract the edge weight type from the "EDGE_WEIGHT_TYPE" line
                if (sscanf(buffer, "EDGE_WEIGHT_TYPE : %s", edgeWeightType) != 1) {
                    fprintf(stderr, "Error reading the edge weight type.\n");
                    fclose(file);
                    return 1;
                }
                break;
            }

        }

        char edgeWeightFormat[50] = "";
        if (strstr(edgeWeightType, "EXPLICIT")) {
            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                if (strstr(buffer, "EDGE_WEIGHT_FORMAT") != NULL) {
                    if (sscanf(buffer, "EDGE_WEIGHT_FORMAT : %s", edgeWeightFormat) != 1) {
                        fprintf(stderr, "Error reading the edge weight format.\n");
                        fclose(file);
                        return 1;
                    }
                }else if (strstr(buffer, "CAPACITY") != NULL) {
                    if (sscanf(buffer, "CAPACITY : %d", &capacity) != 1) {
                        fprintf(stderr, "Error reading the capacity.\n");
                        fclose(file);
                        return 1;
                    }
                    break; // Node coordinates section encountered, break and start reading
                }
            }



            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                if (strstr(buffer, "EDGE_WEIGHT_SECTION") != NULL) {
                    break; // Node coordinates section encountered, break and start reading
                }
            }
            long int filePosition = ftell(file);// Get the current file position

            double **finalMatrix = calloc(numNodes, sizeof(double *));
            for (int i = 0; i < numNodes; i++) {
                finalMatrix[i] = (double *) calloc(numNodes, sizeof(double));
            }


            if (strstr(edgeWeightFormat, "FULL_MATRIX") != NULL) {
                finalMatrix = readFullMatrix(file, numNodes, filePosition); // Read the full explicit matrix
            } else if (strstr(edgeWeightFormat, "UPPER_ROW") != NULL) {
                finalMatrix = readUpperRow(file, numNodes, filePosition); // Read the upper row matrix
            } else if (strstr(edgeWeightFormat, "LOWER_ROW") != NULL) {
                finalMatrix = readLowerRow(file, numNodes, filePosition); // Read the lower row matrix
            } else if (strstr(edgeWeightFormat, "UPPER_COL") != NULL) {
                finalMatrix = readUpperCol(file, numNodes, filePosition); // Read the upper row matrix
            } else if (strstr(edgeWeightFormat, "LOWER_COL") != NULL) {
                finalMatrix = readLowerCol(file, numNodes, filePosition); // Read the lower row matrix
            } else if (strstr(edgeWeightFormat, "UPPER_DIAG_ROW") != NULL) {
                finalMatrix = readUpperDiagRow(file, numNodes, filePosition); // Read the upper row matrix
            } else if (strstr(edgeWeightFormat, "LOWER_DIAG_ROW") != NULL) {
                finalMatrix = readLowerDiagRow(file, numNodes, filePosition); // Read the lower row matrix
            } else if (strstr(edgeWeightFormat, "UPPER_DIAG_COL") != NULL) {
                finalMatrix = readUpperDiagCol(file, numNodes, filePosition); // Read the upper row matrix
            } else if (strstr(edgeWeightFormat, "LOWER_DIAG_COL") != NULL) {
                finalMatrix = readLowerDiagCol(file, numNodes, filePosition); // Read the lower row matrix
            }
            if(fileType == 3) {

                //create the demand matrix
                int *demandMatrix = calloc(numNodes, sizeof(int));


                while (fgets(buffer, sizeof(buffer), file) != NULL) {
                    if (strstr(buffer, "DEMAND_SECTION") != NULL) {
                        filePosition = ftell(file);// Get the current file position
                        demandMatrix = readDemand(file, numNodes, filePosition);

                        break; // Node coordinates section encountered, break and start reading
                    }
                }

                // Print the demand matrix
                printf("Demand Matrix:\n");
                for (int i = 0; i < numNodes; i++) {
                    printf("%d\t", demandMatrix[i]);
                }
                printf("Capacity: %d\n", capacity);
                outputFile = fopen("tourfinal.txt", "w");
                if (outputFile == NULL) {
                    fprintf(stderr, "Error opening file: tourfinal.txt\n");
                    return 1;
                }
                free(demandMatrix);
            }
            // Print the explicit matrix
            printf("Explicit Matrix:\n");
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    printf("%.2lf\t", finalMatrix[i][j]);
                }
                printf("\n");
            }

            //write to file tourfinal.txt
            outputFile = fopen("tourfinal.txt", "w");
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    fprintf(outputFile, "%.2lf\t", finalMatrix[i][j]);
                }
                fprintf(outputFile, "\n");
            }
            // Free allocated memory
            for (int i = 0; i < numNodes; i++) {
                free(finalMatrix[i]);
            }
            free(finalMatrix);
            fclose(file);
            fclose(outputFile);
        } else {
            // Proceed with node coordinates
            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                if (strstr(buffer, "NODE_COORD_SECTION") != NULL) {
                    break; // Node coordinates section encountered, break and start reading
                }
                // Print each line while searching for NODE_COORD_SECTION
                printf("%s", buffer);
            }
            Node *nodeMatrix = malloc(numNodes * sizeof(Node)); // Allocate memory for nodes

            for (int i = 0; i < numNodes; i++) {
                // Read node coordinates
                if (fscanf(file, "%d %lf %lf", &t, &nodeMatrix[i].x, &nodeMatrix[i].y) != 3) {
                    fprintf(stderr, "Error reading node coordinates.\n");
                    fclose(file);
                    free(nodeMatrix); // Free allocated memory
                    return 1;
                }
            }
            // Compute distance matrix based on edge weight type
            double **finalMatrix = (double **) calloc(numNodes, sizeof(double *));
            for (int i = 0; i < numNodes; i++) {
                finalMatrix[i] = (double *) calloc(numNodes, sizeof(double));
            }
            if (strstr(edgeWeightType, "EUC_2D")) {
                for (int i = 0; i < numNodes; i++) {
                    for (int j = 0; j < numNodes; j++) {
                        finalMatrix[i][j] = euclidean2D(nodeMatrix[i], nodeMatrix[j]);
                    }
                }
            } else if (strstr(edgeWeightType, "EUC_3D")) {
                for (int i = 0; i < numNodes; i++) {
                    for (int j = 0; j < numNodes; j++) {
                        finalMatrix[i][j] = euclidean3D(nodeMatrix[i], nodeMatrix[j]);
                    }
                }
            } else if (strstr(edgeWeightType, "MAX_2D")) {
                for (int i = 0; i < numNodes; i++) {
                    for (int j = 0; j < numNodes; j++) {
                        finalMatrix[i][j] = max2D(nodeMatrix[i], nodeMatrix[j]);
                    }
                }
            } else if (strstr(edgeWeightType, "MAX_3D")) {
                for (int i = 0; i < numNodes; i++) {
                    for (int j = 0; j < numNodes; j++) {
                        finalMatrix[i][j] = max3D(nodeMatrix[i], nodeMatrix[j]);
                    }
                }
            } else if (strstr(edgeWeightType, "MAN_2D")) {
                for (int i = 0; i < numNodes; i++) {
                    for (int j = 0; j < numNodes; j++) {
                        finalMatrix[i][j] = manhattan2D(nodeMatrix[i], nodeMatrix[j]);
                    }
                }
            } else if (strstr(edgeWeightType, "MAN_3D")) {
                for (int i = 0; i < numNodes; i++) {
                    for (int j = 0; j < numNodes; j++) {
                        finalMatrix[i][j] = manhattan3D(nodeMatrix[i], nodeMatrix[j]);
                    }
                }
            } else if (strstr(edgeWeightType, "CEIL_2D")) {
                for (int i = 0; i < numNodes; i++) {
                    for (int j = 0; j < numNodes; j++) {
                        finalMatrix[i][j] = ceil2D(nodeMatrix[i], nodeMatrix[j]);
                    }
                }
            }
            if(fileType == 3) {

                //create the demand matrix
                int *demandMatrix = (int *) calloc(numNodes, sizeof(int));


                while (fgets(buffer, sizeof(buffer), file) != NULL) {
                    if (strstr(buffer, "DEMAND_SECTION") != NULL) {
                        int filePosition = ftell(file);// Get the current file position
                        demandMatrix = readDemand(file, numNodes, filePosition);

                        break; // Node coordinates section encountered, break and start reading
                    }
                }

                // Print the demand matrix
                printf("Demand Matrix:\n");
                for (int i = 0; i < numNodes; i++) {
                    printf("%d\t", demandMatrix[i]);
                }
                printf("Capacity: %d\n", capacity);
                outputFile = fopen("tourfinal.txt", "w");
                if (outputFile == NULL) {
                    fprintf(stderr, "Error opening file: tourfinal.txt\n");
                    return 1;
                }
            }
            // Print distance matrix
            printf("Distance Matrix:\n");
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    printf("%.2lf\t", finalMatrix[i][j]);
                }
                printf("\n");
            }

            //write to file tourfinal.txt
            outputFile = fopen("tourfinal.txt", "w");
            if (outputFile == NULL) {
                fprintf(stderr, "Error opening file: tourfinal.txt\n");
                return 1;
            }
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    fprintf(outputFile, "%.2lf\t", finalMatrix[i][j]);
                }
                fprintf(outputFile, "\n");
            }

            // Free allocated memory
            for (int i = 0; i < numNodes; i++) {

                free(finalMatrix[i]);
            }
            free(nodeMatrix);
            free(finalMatrix);
            // Close the file

            fclose(file);
            fclose(outputFile);

            return 101;

        }

    } else{
        // Read the file and extract necessary information
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            if (strstr(buffer, "DIMENSION") != NULL) {
                // Extract the number of nodes from the "DIMENSION" line
                if (sscanf(buffer, "DIMENSION : %d", &numNodes) != 1) {
                    fprintf(stderr, "Error reading the number of nodes.\n");
                    fclose(file);
                    return 1;
                }
                continue;
            } else if (strstr(buffer, "EDGE_WEIGHT_SECTION") != NULL) {
                break; // Node coordinates section encountered, break and start reading
            }
        }


        double **finalMatrix = calloc(numNodes, sizeof(double *));
        for (int i = 0; i < numNodes; i++) {
            finalMatrix[i] = (double *) calloc(numNodes, sizeof(double));
        }
        long int filePosition = ftell(file);// Get the current file position
        filePosition = filePosition;
        finalMatrix = readFullMatrix(file, numNodes, filePosition); // Read the full explicit matrix

        // Print distance matrix
        printf("Distance Matrix:\n");

        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                printf("%.2lf\t", finalMatrix[i][j]);
            }
            printf("\n");
        }


        //write to file tourfinal.txt
        outputFile = fopen("tourfinal.txt", "w");
        if (outputFile == NULL) {
            fprintf(stderr, "Error opening file: tourfinal.txt\n");
            free(finalMatrix);
            return 1;

        }
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                fprintf(outputFile, "%.2lf\t", finalMatrix[i][j]);
            }
            fprintf(outputFile, "\n");
        }

        // Free allocated memory
        for (int i = 0; i < numNodes; i++) {

            free(finalMatrix[i]);
        }

        free(finalMatrix);
        fclose(outputFile);

        // Close the file
        fclose(file);
        return 102;
    }
}
