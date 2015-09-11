/*----------------------------------ECE368 - Project 2 - Sorting Competition----------------------------*/

/*-----------Name : Siddhant Ekale------------PUID : 0026277745*-----------*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<sys/time.h>

#define TIME(fun) do {\
struct timeval start, end, diff;\
gettimeofday(&start, NULL);\
fun;\
gettimeofday(&end, NULL);\
timersub(&end, &start, &diff);\
printf("Time taken: %ld.%06ld sec.\n",(long int)diff.tv_sec, (long int)diff.tv_usec);\
} while(0)


void sort(int list[], int n);
void Radix_Sort(int * pData, int count);
void i_sort(int *list, int n);
void c_sort(int *list, int n,int max_val);

void Radix_Sort(int * pData, int count)
{

    int * temp_arr = malloc(sizeof(int)*count);
    int index_num[4][256] ={{0,}};
    unsigned int *pdest_val, *psource_val, *ptemp_val;
    size_t i,j,m,n;
    unsigned int u;
    
    for(i = 0; i < count; i++){
        u = pData[i];
        for(j = 0; j < 4; j++){
            if(j != 3)
                index_num[j][(int)(u & 0xff)]++;
            else
                index_num[j][(int)((u^0x80) & 0xff)]++;
            u >>= 8;
        }
    }
    for(j = 0; j < 4; j++){
        n = 0;
        for(i = 0; i < 256; i++){
            m = index_num[j][i];
            index_num[j][i] = n;
            n += m;
        }
    }
    pdest_val = (unsigned int *)temp_arr;
    psource_val = (unsigned int *)pData;
    for(j = 0; j < 4; j++){
        for(i = 0; i < count ; i++){
            u = psource_val[i];
            if(j != 3)
                m = (int)(u >> (j<<3)) & 0xff;
            else
                m = (int)((u >> (j<<3))^0x80) & 0xff;
            pdest_val[index_num[j][m]++] = u;
        }
        ptemp_val = psource_val;
        psource_val = pdest_val;
        pdest_val = ptemp_val;
    }
    free(temp_arr);
 // The above function is a similar implementation of an algorithm/code researched online.   
}


//------------------------Insertion Sort Algorithm------------------------

void i_sort(int *list, int n)
{
    int index_num = 0;
    int cmp_index = 0;
    int temp = 0;
    while(index_num < n)
    {
        cmp_index = index_num + 1;
        while(list[index_num] > list[cmp_index] && cmp_index > 0)
        {
            temp = list[index_num];
            list[index_num] = list[cmp_index];
            list[cmp_index] = temp;
            cmp_index--;
        }
        index_num++;
    }
}

//------------------------------------Counting Sort Algorithm----------------------------------

//-----------Maximum of all numbers is found in this algorithm-------------
/*int max_of_num(int *list, int n)
{
    int index_num = 0;
    int max = 0;
    max = list[index_num];
    for(index_num = 0; index_num < n; index_num++)
    {
        if(list[index_num] > max)
            max = list[index_num];
    }
    return max;
}*/
//--------------------------------------------------------------------------


/*void c_sort(int *list, int n) //Sort that counts and modifies the list..
 {
 int current = 0;
 int max = 0;
 
 max = max_of_num(list,n);
 
 int *count_array = calloc(max + 1, sizeof(int)); //Allocates memory with all zeroes
 
 for(current = 0; current < n ; current++)
 {
 count_array[list[current]]++; // Increments the index of the number in the array
 }
 
 
 int num = 0;
 current = 0;
 while(current <= n)
 {
 while(count_array[num] > 0)
 {
 list[current] = num; //The original list gets the current number
 count_array[num]--; //Count_Array[current] value reduces by one as the number is inserted into the list
 current++; //Now the list's next index is reached
 
 if(current > n)
 {
 break;
 }
 }
 num++;
 }
 //free(count_array);
 }*/

void c_sort(int *list, int n,int max_val)
{
    int current = 0;
    int max = max_val;
    int *counting_array = calloc(max+1, sizeof(int)); 
    
    for(current = 0; current < n; current ++)
	{
        counting_array[list[current]]++;
    }
    
    int num = 0;
    current = 0;
    
    while(current < n)
	{
        while(counting_array[num] > 0)
		{
            list[current] = num;
            counting_array[num]--;
            current++;
        }
        num++;
    }
	free(counting_array);
	
}
//------------------------------------------------------------------------------------------------------




void sort(int list[], int n)
{
	int max = 0;
	int min = 0;
	int sorted_flag = 1;
	int index_num = 0;
	min = list[0];
	max = list[0];
	for(index_num = 0; index_num < n - 1; index_num++)
	{
		if(list[index_num] > list[index_num+1])
		{
			sorted_flag = 0;
		}	

		if(list[index_num + 1] > max)
		{
			max = list[index_num + 1];
		}
		if(list[index_num + 1] < min)
		{
			min = list[index_num + 1];
		}
		
	}

	if(sorted_flag == 1)
		return;

	if(min >= 0 && (max/n) <= 5 && max < 1500000)
	{
		c_sort(list,n,max);
	}
	
	else
	{
		Radix_Sort(list,n);
	}
	

}

/*int main()
{
	int *unsorted_array;
	int i = 0;
	unsorted_array = malloc(MAX_NUMS * sizeof(int));
	srand(time(NULL));
    
	for(i = 0; i < MAX_NUMS; i++)
	{
	unsorted_array[i] = rand() % 1500;
        //if(unsorted_array[i] % 7 == 0)
        //{
         // unsorted_array[i] *= -1;
        //}
	}
	TIME(sort(unsorted_array,MAX_NUMS));

	for(i = 0; i < MAX_NUMS - 1; i++)
	{
		if(unsorted_array[i] > unsorted_array[i+1])
		printf("\nUnsorted");
	}
	printf("\nSorted");

return(0);	
}

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
    //int va = *(const int*) a;
    //int vb = *(const int*) b;
    //return (va > vb) - (va < vb);
}*/
