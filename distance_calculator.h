#ifndef DISTANCE_CALCULATOR_H
#define DISTANCE_CALCULATOR_H

#include "node.h"

// Euclidean distances
double euclidean2D(Node a, Node b);
double euclidean3D(Node a, Node b);

// Maximum distances
double max2D(Node a, Node b);
double max3D(Node a, Node b);

// Manhattan distances
double manhattan2D(Node a, Node b);
double manhattan3D(Node a, Node b);

// Ceil distances
double ceil2D(Node a, Node b);

#endif
