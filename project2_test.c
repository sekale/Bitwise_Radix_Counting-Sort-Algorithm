#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<sys/time.h>

#include "header.h"

#define MAX_NUMS 1000000
#define TIME(fun) do {\
struct timeval start, end, diff;\
gettimeofday(&start, NULL);\
fun;\
gettimeofday(&end, NULL);\
timersub(&end, &start, &diff);\
printf("Time taken: %ld.%06ld sec.\n",(long int)diff.tv_sec, (long int)diff.tv_usec);\
} while(0)
int cmp(const void* a, const void* b);
int main()
{
	int *unsorted_array;
	int i = 0;
	unsorted_array = malloc(MAX_NUMS * sizeof(int));
	srand(time(NULL));
    
	for(i = 0; i < MAX_NUMS; i++)
	{
	unsorted_array[i] = rand();
        //if(unsorted_array[i] % 7 == 0)
        //{
         // unsorted_array[i] *= -1;
        //}
	}
	//((qsort(unsorted_array,MAX_NUMS,sizeof(int),cmp)));
	TIME(sort(unsorted_array,MAX_NUMS));

	for(i = 0; i < MAX_NUMS - 1; i++)
	{
		if(unsorted_array[i] > unsorted_array[i+1])
		printf("\nUnsorted");
	}
	printf("\nSorted");
	free(unsorted_array);
return(0);	
}

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
    //int va = *(const int*) a;
    //int vb = *(const int*) b;
    //return (va > vb) - (va < vb);
}
