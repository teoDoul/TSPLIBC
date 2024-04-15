#include "distance_calculator.h"
#include <math.h>


// Euclidean distances
double euclidean2D(Node a, Node b) {
    double dij = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    return round(dij);

}

double euclidean3D(Node a, Node b) {
    double xd = fabs(a.x - b.x);
    double yd = fabs(a.y - b.y);
    double zd = fabs(a.z - b.z);
    double dij = round(xd + yd + zd);
    return dij;
}

// Maximum distances
double max2D(Node a, Node b) {
    double xd = fabs(a.x - b.x);
    double yd = fabs(a.y - b.y);
    double dij = fmax(xd, yd);
    return dij;
}

double max3D(Node a, Node b) {
    double xd = fabs(a.x - b.x);
    double yd = fabs(a.y - b.y);
    double zd = fabs(a.z - b.z);
    double dij = fmax(xd, fmax(yd, zd));
    return dij;
}

// Manhattan distances
double manhattan2D(Node a, Node b) {
    return fabs(a.x - b.x) + fabs(a.y - b.y);
}

double manhattan3D(Node a, Node b) {
    double xd = fabs(a.x - b.x);
    double yd = fabs(a.y - b.y);
    double zd = fabs(a.z - b.z);
    double dij = fmax(xd, fmax(yd, zd));
    return round(dij);
}

// Ceil distances
double ceil2D(Node a, Node b) {
    double euclideanDistance = euclidean2D(a, b);
    return ceil(euclideanDistance);
}
