#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h> // only for memset
#include <stdint.h>

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
    for (int i = 0; i < numOfCircles; i++){
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

int hitMonteCarlo(Square borders, Circle circles[], int numOfCircles, int tries){
    int hits = 0;
    Point randomPoint;
    struct random_data buf;
    memset(&buf, 0, sizeof(buf));
    int32_t result=8;
    char state[256];

    initstate_r(0, state, sizeof(state), &buf); // 0 as a Seed =/
    for( int i = 0; i < tries; i++){
        for( int j = 0; j < numOfCircles; j++){
            randomPoint = getRandomPoint(borders, &buf, &result);
            if(isInside(randomPoint, circles[j]) == 0 ){
                hits++;
                break;
            }
        }
    }
    return hits;
}

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
    parseCircles(circles, numOfCircles, argv);
    Square borders;

    borders = getBorders(circles, numOfCircles);
    printf("top-left corner: %f,%f\nbot-right corner: %f,%f\n",
           borders.topLeft.x,
           borders.topLeft.y,
           borders.botRight.x,
           borders.botRight.y);

    int iterations = 2000000000;
    int circlesHits;
    circlesHits = hitMonteCarlo(borders, circles, numOfCircles, iterations);

    double ratio, circlesArea;
    ratio = circlesHits / (double)iterations;
    circlesArea = ratio * (borders.botRight.x-borders.topLeft.x) * (borders.topLeft.y-borders.botRight.y);

    printf("circles area is %f \n", circlesArea);

    free(circles);
    return 0;
}
