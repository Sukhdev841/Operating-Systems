#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>

using namespace std;

class monitor
{
	enum {THINKING, HUNGRY, EATING} states[5];
	sem_t mutex;
	sem_t conditions[5];
public:
	monitor()
	{
		for(int i=0;i<5;i++)
		{
			states[i] = THINKING;
			sem_init(&conditions[i],1,0);
		}
		sem_init(&mutex,1,1);
	}

	void start_eating(int i)
	{
		sem_wait(&mutex);
		states[i] = HUNGRY;
		cout<<"\n"<<(i+1)<<" is HUNGRY\n";
		test(i);
		sem_post(&mutex);
		sem_wait(&conditions[i]);
		sleep(1);
	}

	void stop_eating(int i)
	{
		sem_wait(&mutex);
		states[i] = THINKING;
		cout<<"\n"<<(i+1)<<" is THINKING\n";
		test((i+1)%5);
		test((i+4)%5);
		sem_post(&mutex);
		sleep(2);
	}

	void test(int i)
	{
		if(states[i] == HUNGRY && states[(i+1)%5] != EATING && states[(i+4)%5] != EATING)
		{
			states[i]=EATING;
			cout<<"\n"<<(i+1)<<" is eating.\n";
			sem_post(&conditions[i]);
			sleep(1);
		}
	}

};

monitor x;

void* execute(void *philosopher)
{
	int *p = (int*)(philosopher);

	while(1)
	{
		x.start_eating(*p);
		sleep(1);
		x.stop_eating(*p);
		sleep(1);
	}
}

int main()
{
	pthread_t ids[5];

	for(int i=0;i<5;i++)
	{
		int *temp = new int;
		*temp = i;
		pthread_create(&ids[i],NULL,execute,temp);
	}

	for(int i=0;i<5;i++)
	{
		pthread_join(ids[i],NULL);
	}

	return 0;
}