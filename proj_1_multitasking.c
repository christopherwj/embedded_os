#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

pid_t mainId;
unsigned long long int N[] = {100000000, 1000000000, 10000000000};
unsigned int tasks[] = {2,4,8};


void sumOfN(unsigned long long int n, unsigned int tasks){
	//printf("\n\n\n%llu\n\n\n", n);
	pid_t creatorId;
	int pipefd[2];
	clock_t start, end;
	double timeUsed;
	unsigned int long long total = 0;
	unsigned long long int sum = 0;
	unsigned long long int max = n;
	unsigned long long int min = 0;
	unsigned long long int range;
	pipe(pipefd);
	
	start = clock();
	// Create n tasks.
	for(int i = 1; i < tasks; i = i * 2){
		creatorId = getpid();
		fork();
		range = (max-min)/2;
		if(creatorId != getpid()) min = max-range;
		else max = max-range;
	}

	for(unsigned long long int i = min; i < max; i++){
		sum += i;
	}
	write(pipefd[1], &sum, sizeof(sum));
	close(pipefd[1]);

//	printf("ID: %d Range: %llu %llu %llu Total: %llu\n", getpid(), min, max, range, sum);
	if(getpid() != mainId) exit(0);
//	printf("Main ID: %d\n", mainId);
	if(getpid() == mainId){
		wait(NULL);
		for(int i = 0; i < tasks; i++){
			read(pipefd[0], &sum, sizeof(sum));
			total += sum;
		}
		end = clock();
		printf("N: %llu Value: %llu Threads: %d Time Spent: %f\n", n, total, tasks, (double)(end-start)/CLOCKS_PER_SEC);
	}
}



int main(int argc, char *argv[]){
	mainId = getpid();
	for(int i = 0; i < sizeof(N)/sizeof(N[0]); i++){
		for(int j = 0; j < sizeof(tasks)/sizeof(tasks[0]); j++){
			sumOfN(N[i], tasks[j]);
		}
	}
	return 0;
}
