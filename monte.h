#ifndef MONTE_H
#define MONTE_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h> // only for memset

typedef struct {
	double x;
	double y;
} Point;

typedef struct {
	Point center;
	double radius;
} Circle;

typedef struct {
	Point topLeft;
	Point botRight;
} Square;

double smaller(double current, double new);
double bigger(double current, double new);
Square getBorders(Circle circle[], int numOfCircles);
int isInside(Point point, Circle circle);
int countCircles(int args);
int parseCircles(Circle circle[], int numberOfCircles, char* argv[]);
Point getRandomPoint(Square borders, struct random_data *buf, int32_t *result);
int hitMonteCarlo(Square borders, Circle circles[], int numOfCircles, int tries, int* result);

#endif
