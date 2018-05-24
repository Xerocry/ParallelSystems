#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "monte.h"


int main(int argc, char *argv[]){
	printf("Number of args: %d\n", argc);
	int numOfCircles = countCircles(argc-1); // set first argument aside (it's program name)
	printf("Number of circles: %d\n", numOfCircles);
	if(numOfCircles == 0){
		fprintf(stderr, "You should give at least one circle (X and Y of center and radius)\n");
		return 1;
	}
		
	Point point;
	Circle* circles;
	circles = malloc(numOfCircles * sizeof(Circle));
	if (circles == NULL){
		fprintf(stderr, "Error while allocating memory\n");
		exit(4);
	}
	parseCircles(circles, numOfCircles, argv);
	Square borders;
	
	borders = getBorders(circles, numOfCircles);
	printf("top-left corner: %f,%f\nbot-right corner: %f,%f\n",
		borders.topLeft.x,
		borders.topLeft.y,
		borders.botRight.x,
		borders.botRight.y);

	int iterations = 2000000000;
	int* circlesHits;
	circlesHits = malloc(1);
	if (circlesHits == NULL){
		fprintf(stderr, "Error while allocating memory\n");
		exit(4);
	}
	if(hitMonteCarlo(borders, circles, numOfCircles, iterations, circlesHits + 0 )){
		fprintf(stderr, "Error in function hitMonteCarlo\n");
		return 2;
	}
		

	double ratio, circlesArea;
	ratio = circlesHits[0] / (double)iterations;
	circlesArea = ratio * (borders.botRight.x-borders.topLeft.x) * (borders.topLeft.y-borders.botRight.y);

	printf("circles area is %f \n", circlesArea);

	free(circles);
	free(circlesHits);
	return 0;
}
