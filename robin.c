#include <stdio.h>
#include <stdlib.h>

void round_robin(int *at,int *bt,int time_quantum,int n)
{
	int time = 0,j;
	int remain = n;
	int *wt = (int*)(malloc(sizeof(int)*n));
	for(j=0;j<n;j++)
		wt[j]=0;

	while(remain>0)
	{
		int i=0;
		for(i =0;i<n;i++)
		{
			if(time >= at[i] && bt[i]>0)
			{
				if(bt[i] >= time_quantum)
				{
					bt[i] -= time_quantum;
					wt[i] += time - at[i];
					at[i] = time + time_quantum;
					time += time_quantum;
				}
				else if(bt[i] < time_quantum)
				{
					wt[i] += time - at[i];
					time = time + bt[i];
					at[i] = time;
					bt[i] = 0;
				}
				if(bt[i]<=0)
				{
					remain--;
				}
			}
			else if(time < at[i])
			{
				time++;
				break;
			}
		}
	}

	int i,sum = 0;
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

	int time_quantum;
	printf("\nEnter time quantum for round robin : ");
	scanf("%d",&time_quantum);
	round_robin(at,bt,time_quantum,n);
	return 0;
}