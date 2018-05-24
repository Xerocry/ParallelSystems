serial:
	gcc -lm -J4 -O3 monte.c serial.c -o serial

pthreads:
	gcc -lm -lpthread -J4 -O3 monte.c pthreads.c -o pthreads

omp:
	gcc -lm -fopenmp -J4 -O3 monte.c omp.c -o omp

all: serial pthreads omp

clean:
	rm omp pthreads serial
