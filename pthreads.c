#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include "monte.h"

typedef struct {
	Square *borders;
	Circle *circles;
	int *numOfCircles;
	int iterations;
	int *circlesHits;
}thread_args;

static void* thread_monte(void *arg){
		thread_args * argsStruct = arg;
		
		if(hitMonteCarlo(*(argsStruct->borders), argsStruct->circles, *(argsStruct->numOfCircles), argsStruct->iterations, argsStruct->circlesHits + 0 )){
			fprintf(stderr, "Error in function hitMonteCarlo\n");
		}
		pthread_exit(NULL);

}

int main(int argc, char *argv[]){
	printf("Number of args: %d\n", argc);
	int numOfCircles = countCircles(argc-2); // set first argument aside (it's program name) + second - number of threads
	printf("Number of circles: %d\n", numOfCircles);
	if(numOfCircles == 0){
		fprintf(stderr, "You should give at least one circle (X and Y of center and radius)\n");
		return 1;
	}

	int numberOfThreads = atof(argv[1]);
	if ( numberOfThreads == 0 ) exit(3);
	printf("Number of threads: %d\n", numberOfThreads);
		
	Point point;
	Circle* circles;
	circles = malloc(numOfCircles * sizeof(Circle));
	if (circles == NULL){
		fprintf(stderr, "Error while allocating memory\n");
		exit(4);
	}
	parseCircles(circles, numOfCircles, &argv[1]);
	Square borders;
	
	borders = getBorders(circles, numOfCircles);
	printf("top-left corner: %f,%f\nbot-right corner: %f,%f\n",
		borders.topLeft.x,
		borders.topLeft.y,
		borders.botRight.x,
		borders.botRight.y);

	pthread_t* threadsArray;
	threadsArray = malloc(numberOfThreads * sizeof(pthread_t));
	if (threadsArray  == NULL){
		fprintf(stderr, "Error while allocating memory\n");
		exit(4);
	}

	int iterations = 2000000000;
	int* circlesHits;
	circlesHits = malloc(numberOfThreads * sizeof(int));
	if (circlesHits == NULL){
		fprintf(stderr, "Error while allocating memory\n");
		exit(4);
	}

	for (int i=0; i < numberOfThreads; i++)
		circlesHits[i]=i+1;

	thread_args *ThreadArgs;
	ThreadArgs= malloc(sizeof(thread_args) * numberOfThreads);
	if (ThreadArgs == NULL){
		fprintf(stderr, "Error while allocating memory\n");
		exit(4);
	}
	for(int i = 0; i < numberOfThreads; i++){
		ThreadArgs[i].circles = circles;
		ThreadArgs[i].borders = &borders;
		ThreadArgs[i].numOfCircles = &numOfCircles;
		ThreadArgs[i].iterations = iterations / numberOfThreads;
		ThreadArgs[i].circlesHits = &circlesHits[i];
		pthread_create(threadsArray + i , NULL, *thread_monte, &ThreadArgs[i]);
	}

	int totalCirclesHits = 0;
	for(int i = 0; i < numberOfThreads; i++){
		int status = 0;
		status = pthread_join(*(threadsArray + i ), NULL);
		if( status != 0){
			fprintf( stderr, "Failed to join thread %i with error %i", i, status);	
			return 3;
		}
		totalCirclesHits = totalCirclesHits + circlesHits[i];
	}
	free(threadsArray);
	free(ThreadArgs);

	double ratio, circlesArea;
	ratio = totalCirclesHits / (double)iterations;
	circlesArea = ratio * (borders.botRight.x-borders.topLeft.x) * (borders.topLeft.y-borders.botRight.y);

	printf("circles area is %f \n", circlesArea);

	free(circles);
	free(circlesHits);
	return 0;
}
