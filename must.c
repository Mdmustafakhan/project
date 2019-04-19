#include<semaphore.h>
#include<stdio.h>
#include<malloc.h>
#include<pthread.h>
#include<stdlib.h>

//creating semaphore
// n -> total number of process, later given by user
// resources -> total number of resources we have
// resource_count -> store count of resources needed by each process

sem_t s;

int n,resources;
int *resource_count;

void decrease_count(int count)
{

	resources -= count;
}
void increase_count(int count)
{
	
	resources += count;
	
}
void* execute_process(void *res_count)
{
	int count = *(int *)res_count;
	
	if(resources<resource_count[count])
	{
		printf("\nRace condition for P%d \t Status [Waiting...] [Resources Avail : %d]",count+1,resources);
		
	}
	
		sem_wait(&s);
		//critical section to acquire resources
		
		decrease_count(resource_count[count]);
		
		
		printf("\n\nP%d Resoruce Aquired... [Resource Avail : %d]\n",count+1,resources);
		
		sleep(3);
		
		
		//releasing the aquired resources
		
		increase_count(resource_count[count]);
		
		printf("\nP%d Completed... [Resource Avail : %d]",count+1,resources);
		sem_post(&s);		
}

int main()
{
  
  printf("\nEnter number of process : ");
  scanf("%d",&n);
  
  
  printf("\n\nEnter total number of resources : ");
  scanf("%d",&resources);
  
  printf("\nEnter resources needed to each process :");
  //creating resource_count variable to store count of resources need by each process
  resource_count = (int*)malloc(sizeof(int)*n);
  
  int i=0;
  for(i=0;i<n;i++)
  {
  	printf("\nP%d : ",i+1);
  	scanf("%d",&resource_count[i]);
  	
  	if(resource_count[i]>resources)
  		{
		  printf("\nCannot be greater that total resources...\nERROR...EXITING...");
  		  return 0;
  		}
  }
  
  
  //Initialize semaphore
  	sem_init(&s,0,1);
  	
  //creating n threads (acting as process)
  pthread_t p[n];
  
  for(i=0;i<n;i++)
  	{
  		int *temp = (int*)malloc(sizeof(int)*1);
  		temp[0] = i;
  		pthread_create(&p[i],NULL,execute_process,(void*)(temp));
	  }
  	
  //running each thread
  for(i=0;i<n;i++)
  {
  	pthread_join(p[i],NULL);
  }
  	
  
}

