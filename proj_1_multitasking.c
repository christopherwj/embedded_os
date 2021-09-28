#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

typedef unsigned long long ull_t;

pid_t mainId;
ull_t N[] = {(ull_t)1e8, (ull_t)1e9, (ull_t)1e10};
unsigned tasks[] = {16,2,4,8};

void sum_N(ull_t n, unsigned tasks){
	pid_t creatorId;
	int pipefd[2];
	clock_t start, end;
	ull_t total = 0;
	uint64_t sum = 0;
	ull_t max = n;
	ull_t min = 0;
	ull_t range;
	pipe(pipefd);
	
	start = clock();
	for(unsigned i = 1; i < tasks; i = i * 2){
		creatorId = getpid();
		fork();
		range = (max-min)/2;
		if(creatorId != getpid())
			min = max-range;
		else
			max = max-range;
	}

	for(ull_t i = min; i < max; i++){
		sum += i;
	}
	write(pipefd[1], &sum, (size_t)8);
	close(pipefd[1]);
	if(getpid() != mainId) exit(0);
	if(getpid() == mainId){
		wait(NULL);
		for(unsigned i = 0; i < tasks; i++){
			wait(NULL);
			ssize_t r;
			r = read(pipefd[0], &sum, (size_t)8);
			total += sum;
		}
		end = clock();
		printf("N: %llu Value: %llu Threads: %d Time Spent: %f\n", n, total, tasks, (double)(end-start)/CLOCKS_PER_SEC);
	}
}

int main(int argc, char *argv[]){
	mainId = getpid();
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 1; j++){
			sum_N(N[i], tasks[j]);
		}
	}
	return 0;
}
