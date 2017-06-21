#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>


#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NUMBERS 0
#define THREADS 1
#define SEED 2
#define MODE 3

#define ENABLE_FILE_OUTPUT 1        // Output in "Results.dat":1 / Terminal:0

typedef struct
{
    int sort_from;
    int sort_to;
    int tid;
} Thread_arguments;

pthread_mutex_t mutex;
int * random_array;


/* prints the array in format: { a b c } */
void printArray(const int * array, int size)
{
    printf("{");
    for(int i = 0; i < size; i++){
        printf(" %d", array[i]);
    }
    
    printf(" }\n");
}


/* If enabled ( mode == 1 ) redirects output of the program to a file named "results.dat" */
void enableFileOutput(int mode)
{
    if( mode == 1){
        
        char * file = "results.dat";

        int out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (out < 0)
        {
            printf("\nError creating file:'%s'", file);
            return;
        }
        
        dup2(out, STDOUT_FILENO);
        close(out);
    }
}


/* Extracts the numbers of the arguments string
 * ex: argv = {"-a=10", "-b=5", "-c=1"} then 
 * int *store = "10, 5, 1" */
void extractNums(int argc, char **argv, int *store)
{
    /* for each string in argv */
    for(int i = 1; i < argc; i++){
        char *str = argv[i];
        char *ptr = str;

        /* while there are more characters to process */
        while (*ptr) {
            /* upon finding a digit */
            if (isdigit(*ptr)) { 
                long val = strtol(ptr, &ptr, 10); /* read a number */
                store[i-1] = val;
            /* otherwise, move on to the next character */   
            } else { 
                ptr++;
            }
        }
    }
}


/* Terminates the main function if cmd input
 * -threads wasnt 1,2,4 or 8 */
void verifyThreads(int threads)
{
    if(threads == 1 || threads == 2 || threads == 4 || threads == 8){
        return;
    }
    
    printf("ERROR: Wrong number of threads selected!\n");
    exit(-1);
}


/* Creates an array containing random numbers based on
 * the -numbers and -seed arguments given in the cmd */
void createArray(int **array, int size, int seed)
{
    /* create the random generator */
    srand((unsigned)seed);
    *array = malloc(sizeof(int) * size);
    
    for(int i = 0; i < size; i++){
        (*array)[i] =  rand() % 100;
    }
    
}


/* Divides the random array into subarrays for the threads.
 * Each cell of sort_from will contain the 'start pointer'
 * of the subarray inside of the random array it must sort.
 * 
 * e.g sort_array = { 0, 5 } with a random array of 10 numbers and 2 threads
 * means that thread[0] will sort from 0 to 4(sort_array[1] - 1)
 * while the last thread[1] will sort from 5 to the end of the random array. */
void divide_array(int *sort_from, int threads, int rdm_arr_size)
{
    int offset = rdm_arr_size / threads;
    sort_from[0] = 0;
    
    for(int i = 1; i < threads; i++){
        sort_from[i] = sort_from[i-1] + offset;
    }
    
}


/* Will be from quickSort to sort the arrays
 * (no synchro on writing in the array) */
int partition_unlocked( int a[], int l, int r) {
    
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;

   while(1){
       do ++i; while( a[i] <= pivot && i <= r );
       do --j; while( a[j] > pivot );
       if( i >= j ) break;
       t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}


/* Will be from quickSort to sort the arrays
 * (synchro on writing in the array) */
int partition_locked( int a[], int l, int r) {
    
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;

   while(1){
       do ++i; while( a[i] <= pivot && i <= r );
       do --j; while( a[j] > pivot );
       
       if( i >= j ) break;
       pthread_mutex_lock(&mutex);      // lock the part where the thread is writing on the array
       t = a[i]; a[i] = a[j]; a[j] = t;
       pthread_mutex_unlock(&mutex);
   }
   t = a[l]; a[l] = a[j]; a[j] = t;     // unlock the part where the thread is writing on the array
   return j;
}


/* quickSort
 * if mode = 1 then partition_locked will be used, which will prevent more than 1 thread to write in the array */
void quickSort( int a[], int l, int r, int mode)
{
   int j;

   if( l < r ) {
       
       if(mode == 1){
           j = partition_locked( a, l, r);
           quickSort( a, l, j-1, 1);
           quickSort( a, j+1, r, 1);
       }else{
           j = partition_unlocked( a, l, r);
           quickSort( a, l, j-1, 0);
           quickSort( a, j+1, r, 0);
       }
   }

}


/* Returns the index of the cell with the minimum value */
int min(int *array, int size)
{
    int min = array[0];
    int min_index = 0;
    
    for(int i = 1; i < size; i++){
        if(array[i] < min){
            min = array[i];
            min_index = i;
        }
    }

    return min_index;
}


/*Returns the index of the cell with the maximum value */
int max(int *array, int size)
{
    int max = array[0];
    int max_index = 0;
    
    for(int i = 1; i < size; i++){
        if(array[i] > max){
            max = array[i];
            max_index = i;
        }
    }

    return max_index;
}


/* used by mere */
void merge(int arr[], int l, int m, int r)
{
    //indexes for subarrays
	int i, j, k;
    //for array 1
	int n1 = m - l + 1;
    //for array 2
	int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* Merges the sub-arrays inside of the initial array. */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}


/* absolute synchronization sort(Policy 1) */
void *absSynchSort(void *args)
{
    Thread_arguments *data = (Thread_arguments *) args;
    
    pthread_mutex_lock(&mutex);
    quickSort(random_array, data->sort_from, data->sort_to, 0);
    pthread_mutex_unlock(&mutex);
    
    printf("Thread[%d] : sort[ %d to %d ]\n", data->tid, data->sort_from, data->sort_to);
    pthread_exit(0);
}


/* medium synchronization sort(Policy 2) */
void *medSynchSort(void *args)
{
    Thread_arguments *data = (Thread_arguments *) args;
    
    quickSort(random_array, data->sort_from, data->sort_to, 1);
    
    printf("Thread[%d] : sort[ %d to %d ]\n", data->tid, data->sort_from, data->sort_to);
    pthread_exit(0);
}


/* no synchronization sort(Policy 3) */
void *noSynchSort(void *args)
{
    Thread_arguments *data = (Thread_arguments *) args;
    
    quickSort(random_array, data->sort_from, data->sort_to, 0);
    
    printf("Thread[%d] : sort[ %d to %d ]\n", data->tid, data->sort_from, data->sort_to);
    pthread_exit(0);
}


int main(int argc, char **argv)
{
    struct timeval start, end;
    int elapsedTime;
    
    /* Start the timer */
    gettimeofday(&start, NULL);
    
    int cmd_args[4];
    
    /* Write output to "results.dat" */
    enableFileOutput(ENABLE_FILE_OUTPUT);
    
    /* Create the random Array */
    extractNums(argc, argv, cmd_args);
    verifyThreads(cmd_args[THREADS]);
    createArray(&random_array, cmd_args[NUMBERS], cmd_args[SEED]);
    
    //printf("\nInitial array = ");
    //printArray(random_array, cmd_args[NUMBERS]);
    
    /* Create the division array */
    int sort_from[cmd_args[THREADS]];
    divide_array(sort_from, cmd_args[THREADS], cmd_args[NUMBERS]);
    
    pthread_t threads[cmd_args[THREADS]];
    Thread_arguments args[cmd_args[THREADS]];
    
    if(cmd_args[MODE] == 1){
        printf("\n--ABSOLUTE SYNCHRONIZATION SORT--\n");
        
        for(int i = 0; i < cmd_args[THREADS]; i++){
            
            /* If its the last thread, sort_to must be the end of the array - 1 */
            if(i == cmd_args[THREADS] - 1){
                args[i].sort_from = sort_from[i];           // sort from
                args[i].sort_to = cmd_args[NUMBERS] - 1;    // sort to
                args[i].tid = i;                            // thread_id
                
            /* Or else sort_to must be 1 item before the start of the next sort_from */
            }else{
                args[i].sort_from = sort_from[i];           // sort from
                args[i].sort_to = sort_from[i + 1] - 1;     // sort to
                args[i].tid = i;                            // thread_id
            }
            
            if(pthread_create(&threads[i], 0, absSynchSort, &args[i])){
                printf("ERROR: Couldnt create threads in noSynchSort!\n");
            }
        }
        
    }else if(cmd_args[MODE] == 2){
        printf("\n--MEDIUM SYNCHRONIZATION SORT--\n");
        
        for(int i = 0; i < cmd_args[THREADS]; i++){
            
            /* If its the last thread, sort_to must be the end of the array - 1 */
            if(i == cmd_args[THREADS] - 1){
                args[i].sort_from = sort_from[i];           // sort from
                args[i].sort_to = cmd_args[NUMBERS] - 1;    // sort to
                args[i].tid = i;                            // thread_id
                
            /* Or else sort_to must be 1 item before the start of the next sort_from */
            }else{
                args[i].sort_from = sort_from[i];           // sort from
                args[i].sort_to = sort_from[i + 1] - 1;     // sort to
                args[i].tid = i;                            // thread_id
            }
            
            if(pthread_create(&threads[i], 0, medSynchSort, &args[i])){
                printf("ERROR: Couldnt create threads in noSynchSort!\n");
            }
        }
        
    }else if(cmd_args[MODE] == 3){
        printf("\n--NO SYNCHRONIZATION SORT--\n");
        
        for(int i = 0; i < cmd_args[THREADS]; i++){
            
            /* If its the last thread, sort_to must be the end of the array - 1 */
            if(i == cmd_args[THREADS] - 1){
                args[i].sort_from = sort_from[i];           // sort from
                args[i].sort_to = cmd_args[NUMBERS] - 1;    // sort to
                args[i].tid = i;                            // thread_id
                
            /* Or else sort_to must be 1 item before the start of the next sort_from */
            }else{
                args[i].sort_from = sort_from[i];           // sort from
                args[i].sort_to = sort_from[i + 1] - 1;     // sort to
                args[i].tid = i;                            // thread_id
            }
            
            if(pthread_create(&threads[i], 0, noSynchSort, &args[i])){
                printf("ERROR: Couldnt create threads in noSynchSort!\n");
            }
        }
        
    }else{
        printf("ERROR: There is no such mode!\n");
        exit(-1);
    }
    
    for(int i = 0; i < cmd_args[THREADS]; i++){
        pthread_join(threads[i], 0);
    }
    printf("\nSuccessfully waited for all threads to finish...\n");
    //printf("Inital Array before Merge = ");
    //printArray(random_array, cmd_args[NUMBERS]);
    
    printf("Merging initial array...\n");
    
    quickSort(random_array, 0, cmd_args[NUMBERS], 0);
    
    /* Stop the timer and set the elapsed time */
    gettimeofday(&end, NULL);
    elapsedTime = (end.tv_usec - start.tv_usec) * 1000;         /* microseconds to ns */
    
    //printf("\nSorted array = ");
    //printArray(random_array, cmd_args[NUMBERS]);
    printf("Time elapsed = %d ns\n", elapsedTime);
    printf("Program Terminated!\n");
    printf("\n--------------------------------------------------------------------------\n");
    printf("//////////////////////////////////////////////////////////////////////////\n");
    printf("--------------------------------------------------------------------------\n");
    
    free(random_array);
	return 0;
}