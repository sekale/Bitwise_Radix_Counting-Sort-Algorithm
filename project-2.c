

void sort(int list[], int n)
{
	int max = 0;
	int min = 0;
	int sorted_flag = 1;
	int index_num = 0;
	int count_flag = 0;
	int radix_flag = 0;
	min = list[0];
	max = list[0];
	for(index_num = 0; index_num < n; index_num++)
	{
		if(list[index_num] > list[index_num+1])
		{
			sorted_flag = 0;
			max = list[index_num];
		}	

		if(list[index_num] < list[index_num + 1])
		{
			min = list[index_num];
		}
		
	}

	if(sorted_flag == 1)
		return;
	
	if(min >0 && (max/n) < 5 && max < 1500000)
	{
		TIME(c_sort(unsorted_array_2,MAX_NUMS,max));
	}
	
	else
	{
		TIME(Radix_Sort(unsorted_array,MAX_NUMS));
	}
	

}
