#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


float sum(int sum_to_value){

int i = 0;
clock_t start, end;
float cpu_time_used;

int arr[sum_to_value];

//start the clock to measuring time 
start = clock();

//baseline sum to 9999999
for (int i = 0; i < sum_to_value; i++)
    sum += arr[i];
// while (i < sum_to_value-1){
// 	i++;
// }

//stop the clock measuring time
end = clock();

cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
return cpu_time_used;
}


int main(){

float test1 = sum(100000000);
printf("Test 1x10^8 took %f\n", test1);

float test2 = sum(1000000000);
printf("Test 1x10^9 took %f\n", test2);

float test3 = sum(10000000000);
printf("Test 1x10^10 took %f\n", test3);

return 0;

}



//gcc test.c -o test.o
//./gcc test.c
