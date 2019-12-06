/***************************************************************
* PROGRAMMER: 		Khoa Tran 
* 
* COURSE:   		CSCI 4354.01
* 
* DATE:   			December 1, 2015
* 
* ASSIGNMENT:  		Homework 11
* 
* ENVIRONMENT: 		C in Unix, code in window 7 using putty
* 
* FILES INCLUDED: 	signalWait.c
* 
* PURPOSE: 			Modify the program so that threadOne count up to 5
*					then threadTwo count down to 5 
*					alternate it for 3 iterations
*
* INPUT: 			none
*									
*
* PRECONDITIONS:  	count start at 0
*
*
* OUTPUT:  			for each iteration
*					output of threadOne and threadTwo
*															
*
* POSTCONDITIONS: 	None	
*
*
* ALGORITHM: 		Void ThreadOne
*						For each iteration
*							while oktogo is false
*								check condition and mutex
*							For each time counting up
*								increment count
*								printout count
*							set oktogo to false
*							unlock mutex
*						exit ThreadOne
*						
*					Void ThreadTwo
*						For each iteration
*							while oktogo is false
*								check condition and mutex
*							For each time counting down
*								decrement count
*								printout count
*							set oktogo to false
*							unlock mutex
*						exit ThreadTwo
*						
*					Main
*					Create threadOne
*					Create threadTwo
*					join threadOne
*					Join ThreadTwo
*					end
*					
*
*
*
*
***************************************************************/


#include <stdio.h>
#include <pthread.h>

int count = 0;
int oktogo = 1; //0 is false, 1 is true. For thread2 this is reversed.

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

void *start_thread_one()
{
    int i;
    int j;
    for (i=1;i<4;i++) //each iteration total of 3
	{
	 
        pthread_mutex_lock(&mutex);
	 
        while (oktogo == 0)// False, go to threadTwo
		{
            pthread_cond_wait(&condition, &mutex);
		}	
		
		
		//to identify each time its repeat	
		printf("~~~~~~~~~~~Iteration~~~~~~~~~~~~~~ %d\n", i);
		
        for (j=1;j<6;j++) // for each count
		{
		
			count++;
        	printf("thread one: %d\n", count);

		}
        oktogo = 0;
	
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condition);
		
        }
	pthread_exit(0);
   }

void *start_thread_two()
{
	int i;
	int j;
	for(i=1;i < 4;i++) 
	{
        pthread_mutex_lock(&mutex);
        while (oktogo == 1) //False go to threadOne
		{
            pthread_cond_wait(&condition, &mutex);
		}
		
	for (j=1;j<6;j++) 
		{
        count--;
        printf("thread two: %d\n", count);
		}
        oktogo = 1;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condition);

	}
	pthread_exit(0);
}

int main ()
{
	int count = 0;
	pthread_t p1,p2;

	pthread_create(&p1,NULL,(void *)start_thread_one,NULL);
	pthread_create(&p2,NULL,(void *)start_thread_two,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);

return(0);
}
