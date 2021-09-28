#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NO_OF_THREADS 4
#define MAX_NO_OF_ELEMENTS 1000000000

typedef struct arg_data {
    int thread_number;
} arg_data;

//shared data on which threads will work concurrently
//array which will be summed
static int arr[MAX_NO_OF_ELEMENTS];

//sum variable that will store the total sum
static unsigned long long int sum;

void* worker_sum(void* arg)
{
    arg_data* current_thread_data = (arg_data*)arg;
 
    printf("Current thread no is : %d\n", current_thread_data->thread_number);
 
    int endpart = (current_thread_data->thread_number) * ((MAX_NO_OF_ELEMENTS) / MAX_NO_OF_THREADS);
    int startpart = endpart - (MAX_NO_OF_ELEMENTS / MAX_NO_OF_THREADS);

    printf("Here we will sum %d to %d\n", arr[startpart], arr[endpart]);

    unsigned long long int current_thread_sum = 0;
    for (int i = startpart; i < endpart; i++) {
        current_thread_sum += arr[i];
    }
    //sum += (current_thread_data->thread_number % MAX_NO_OF_THREADS ? current_thread_sum : current_thread_sum - 1);
    sum += current_thread_sum;
    return NULL;
}

int main()
{
    //let the array consists of first MAX_NO_OF_ELEMENTS integers, 
    //1 to MAX_NO_OF_ELEMENTS
    for (unsigned long long i = 1; i <= MAX_NO_OF_ELEMENTS; i++)
        arr[i] = i;
    
    //pthread objects
    pthread_t id[MAX_NO_OF_THREADS];
    
    //argument data to send in worker functions
    arg_data arg_arr[MAX_NO_OF_THREADS];
    
    //total number of threads we will create
    int no_of_threads = MAX_NO_OF_THREADS;
    printf("Creating %d number of threads...\n", no_of_threads);

    clock_t start, end;
    double cpu_time_taken;

    start = clock();

    int thread_no;
    //creating the child threads
    for (thread_no = 1; thread_no <= MAX_NO_OF_THREADS; thread_no++) {
        arg_arr[thread_no - 1].thread_number = thread_no;
        pthread_create(&id[thread_no - 1], NULL, worker_sum, &arg_arr[thread_no - 1]);
    }
    
    //joining the threads one by one
    for (int i = 1; i <= MAX_NO_OF_THREADS; i++)
        pthread_join(id[i - 1], NULL);

    end = clock();
    cpu_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("All child threads has finished their works...\n");

    printf("Total sum: %llu\n", sum);

    printf("Time taken to sum all the numbers are %lf\n", cpu_time_taken);

    return 0;
}
