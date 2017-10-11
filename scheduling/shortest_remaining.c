#include <stdio.h>
#include <stdlib.h>

void shortest_job_first(int *at,int *bt,int n)
{
	int i, time = 0;
	int *wt = (int *)(malloc(sizeof(int)*n));
	int *lt = (int *)(malloc(sizeof(int)*n));
	for(i = 0;i<n;i++)
	{
		lt[i] = at[i];
		wt[i] = 0;
	}

	int remains = n;
	while(remains)
	{
		int j = 0;
		int index = 0;
		int time_ = -1;
		int flag = 1;
		for(j = 0;j<n;j++)
		{
			if(at[j] <= time && bt[j] >0)
			{
				if(flag == 1)
				{
					index = j;
					time_ = bt[j];
					flag = 0;
				}
				else if( time_ > bt[j])
				{
					index = j;
					time_ = bt[j];
				}
			}
		}

		if(flag == 0)
		{
			//a process has been found
			wt[index] += time - lt[index];
			lt[index] = time+1;
			time++;
			bt[index]--;
			if(bt[index] == 0)
				remains--;
		}
		else
			time++;

	}

	int sum = 0;
	for(i=0;i<n;i++)
	{
		printf("\nwaiting times : %d\n",(wt[i]));
		sum = sum+ wt[i];
		
	}
	printf("\navg waiting times : %f\n",(float)((float)(sum)/(float)(n)));

}

int main()
{
	int n,i;
	printf("\nEnter number of processes : ");
	scanf("%d",&n);

	int *at = (int*)(malloc(sizeof(int)*n));
	int *bt = (int*)(malloc(sizeof(int)*n));

	for(int i=0;i<n;i++)
	{
		printf("\nEnter Arrival time and Burst Time for process : ");
		scanf("%d%d",&at[i],&bt[i]);
	}
	shortest_job_first(at,bt,n);
	return 0;
}