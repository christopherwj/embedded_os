#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

float sum(unsigned long long sum_to_value){

    clock_t start;
    clock_t end;
    float cpu_time_used;
    unsigned long long sum = 0;

    //int arr[sum_to_value];

    //start the clock to measuring time 
    start = clock();

    //make it non-inclusive for the last element
    sum_to_value = sum_to_value -1;

    /* baseline sum to 9999999 */
#ifndef USE_EFFICIENT_ALGORITHM
    for (unsigned long long i = 0; i < sum_to_value; i++) {
        sum += sum + i;
    }
#endif

#ifdef USE_EFFICIENT_ALGORITHM /* better way */
    sum = (sum_to_value * (sum_to_value + 1))/2;
    printf("%llu\n", sum);
#endif

    //stop the clock measuring time
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    return cpu_time_used;
}

int main(int argc, char** argv){
	float test1 = sum(1e8);
	printf("Test 1x10^8 took %f\n", test1);

	float test2 = sum(1e9);
	printf("Test 1x10^9 took %f\n", test2);

	float test3 = sum(1e10);
	printf("Test 1x10^10 took %f\n", test3);

	printf("The total sum is:%f\n", test3);
	return 0;
}
