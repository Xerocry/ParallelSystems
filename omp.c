#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <omp.h>
#include "monte.h"

typedef struct {
	Square *borders;
	Circle *circles;
	int *numOfCircles;
	int iterations;
	int *circlesHits;
}thread_args;

static int thread_monte(void *arg){
		thread_args * argsStruct = arg;
		
		if(hitMonteCarlo(*(argsStruct->borders), argsStruct->circles, *(argsStruct->numOfCircles), argsStruct->iterations, argsStruct->circlesHits + 0 )){
			fprintf(stderr, "Error in function hitMonteCarlo\n");
			return 1;
		}
		return 0;
}

int main(int argc, char *argv[]){
	printf("Number of args: %d\n", argc);
	int numOfCircles = countCircles(argc-2); // set first argument aside (it's program name) + second - number of threads
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
	parseCircles(circles, numOfCircles, &argv[1]);

	int numberOfThreads = atof(argv[1]);
	if ( numberOfThreads == 0 ) exit(3);
	printf("Number of threads: %d\n", numberOfThreads);
	Square borders;
	
	borders = getBorders(circles, numOfCircles);
	printf("top-left corner: %f,%f\nbot-right corner: %f,%f\n",
		borders.topLeft.x,
		borders.topLeft.y,
		borders.botRight.x,
		borders.botRight.y);

	int tid;

	int iterations = 2000000000;
	int* circlesHits;
	circlesHits = malloc(numberOfThreads);
	if (circlesHits == NULL){
		fprintf(stderr, "Error while allocating memory\n");
		exit(4);
	}

	thread_args threadArgsTemplate;
	threadArgsTemplate.circles = circles;
	threadArgsTemplate.borders = &borders;
	threadArgsTemplate.numOfCircles = &numOfCircles;
	threadArgsTemplate.iterations = iterations / numberOfThreads;

	for (int i=0; i < numberOfThreads; i++)
		circlesHits[i]=i+1;

	#pragma omp parallel num_threads(numberOfThreads) private(tid)
	{
		thread_args *ThreadArgs = malloc(sizeof(thread_args));
		if (ThreadArgs == NULL){
			fprintf(stderr, "Error while allocating memory\n");
			exit(4);
		}

			ThreadArgs->circles = circles;
			ThreadArgs->borders = &borders;
			ThreadArgs->numOfCircles = &numOfCircles;
			ThreadArgs->iterations = iterations / numberOfThreads;

		ThreadArgs->circlesHits = &circlesHits[omp_get_thread_num()];
		thread_monte(ThreadArgs);
		#pragma omp barrier
		free(ThreadArgs);
	}

	printf("THIS \n");
	int totalCirclesHits = 0;
	for(int i = 0; i < numberOfThreads; i++){
		int status = 0;
		printf("Hits for thread %d: %d\n", i, circlesHits[i]);
		totalCirclesHits = totalCirclesHits + circlesHits[i];
	}

	double ratio, circlesArea;
	ratio = totalCirclesHits / (double)iterations;
	circlesArea = ratio * (borders.botRight.x-borders.topLeft.x) * (borders.topLeft.y-borders.botRight.y);

	printf("circles area is %f \n", circlesArea);

	free(circles);
	return 0;
}
