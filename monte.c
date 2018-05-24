#include "monte.h"

double smaller(double current, double new){
	if(new < current) return new;
	return current;
}

double bigger(double current, double new){
	if(new > current) return new;
	return current;
}

Square getBorders(Circle circle[], int numOfCircles){
	Square borders;

	borders.topLeft.x	= circle[0].center.x - circle[0].radius;
	borders.topLeft.y	= circle[0].center.y + circle[0].radius;
	borders.botRight.x	= circle[0].center.x + circle[0].radius;
	borders.botRight.y	= circle[0].center.y - circle[0].radius;

	for (int i = 1; i < numOfCircles - 1 ; i++){
		borders.topLeft.x	= smaller(borders.topLeft.x,	circle[i].center.x - circle[i].radius);
		borders.topLeft.y	= bigger(borders.topLeft.y,		circle[i].center.y + circle[i].radius);
		borders.botRight.x	= bigger(borders.botRight.x,	circle[i].center.x + circle[i].radius);
		borders.botRight.y	= smaller(borders.botRight.y,	circle[i].center.y - circle[i].radius);
	}
	return borders;
}

int isInside(Point point, Circle circle){
	double xLength = point.x - circle.center.x; 
	double yLength = point.y - circle.center.y; 
	double Distance = sqrt(xLength*xLength + yLength*yLength);
	if(Distance <= circle.radius) return 0;
	return 1;
}

int countCircles(int args){
	if( args == 0) return 0;
	if( args % 3 == 0 ) return (args / 3);
	return 0;
}

int parseCircles(Circle circle[], int numberOfCircles, char* argv[]){
	for(int i = 0; i < numberOfCircles; i++){
		circle[i].center.x	= atof(argv[3*i+1]);
		circle[i].center.y	= atof(argv[3*i+2]);
		circle[i].radius	= atof(argv[3*i+3]);
	}
	return 0;
}	

Point getRandomPoint(Square borders, struct random_data *buf, int32_t *result){
	Point point;
	double random;
	if(random_r(buf, result) != 0){
		fprintf( stderr, "Error occurred in attempt to generate random x for a point\n");
		point.x = (double)0;
		point.y = (double)0;
		return point;
	}
	random = *result;
	point.x = borders.topLeft.x + (borders.botRight.x - borders.topLeft.x) * random / (double)(RAND_MAX);
	if(random_r(buf, result) != 0){
		fprintf( stderr, "Error occurred in attempt to generate random y for a point\n");
		point.y = (double)0;
		return point;
	}
	random = *result;
	point.y = borders.botRight.y + (borders.topLeft.y - borders.botRight.y) * random / (double)(RAND_MAX);
	return point;
}

int hitMonteCarlo(Square borders, Circle circles[], int numOfCircles, int tries, int *resultingHits){
	int hits = 0;
	Point randomPoint;
	struct random_data buf;
	memset(&buf, 0, sizeof(buf));
	int32_t result=8;
	char state[256];

	initstate_r(*resultingHits, state, sizeof(state), &buf); 
	for( int i = 0; i < tries; i++){
		for( int j = 0; j < numOfCircles; j++){
			randomPoint = getRandomPoint(borders, &buf, &result);
			if(isInside(randomPoint, circles[j]) == 0 ){
				hits++;	
				break;	
			}
		}
	}
	*resultingHits = hits;
	return 0;
}
