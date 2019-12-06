
/*************************************************************** 
* PROGRAMMER: 		Khoa Tran 
* 
* COURSE:   		CSCI 4354.01
* 
* DATE:   		November 19, 2015
* 
* ASSIGNMENT:  		Program 4
* 
* ENVIRONMENT: 		C in Unix, code in window 7 with putty
* 
* FILES INCLUDED: 	client.c
* 
* PURPOSE: 		Design and write the client and server 
*			programs necessary to provide a 
*			multiple client CPU scheduler that 
*			handles CPU bursts and I/O bursts. 
*
*   
* INPUT:  		CPU burst
*			I/O Burst
*			Arrival time
*			total number of bursts
* 					
*					
*
* PRECONDITIONS:  	multiple CPU bursts and I/O bursts
*
*					
*   
* OUTPUT: 		Ready waiting time
*			I/O waiting time
*			turnaround time
*
* 
* POSTCONDITIONS: 	None
*
*
*   
* ALGORITHM: 		
* 					
* 			Create client structure
*			create getpid
*			create privateFIFO
*			open commonFIFO to write		
*			prompt user to input arrival times
*			prompt user to input total number of bursts
*			while user still input 
*				if odd 
* 				Prompt user to input CPU bursts	
*				if even		
*				prompt user to input I/O bursts
*			end while
*			Write structure to CommonFIFO				
*			Open privateFIFO to read				
*			Read from privateFIFO
*			print ready waiting time
*			print I/O waiting time
*			print Turn around time			
*			Unlink private FIFO			
* 			Terminate
* 
*
*
*			Estimated Time
*				Design - 15 minutes
*				Implementation - 1 hour
*				testing - 30 minutes
*
*			Actual time
*				Design - 45 minutes
*				Implementation - 2 days
*				testing - 1 hour
*
***************************************************************/


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


typedef struct
{
char privateFIFO[50];
int numburst; 
int burst[50]; 
int io[50];
int arr;
int rdywait;
int iowait;
int tat;
} client; 



int main (void)
{
	int fda;// to write 
	int fdb;// to read 
	client writet; // write to
	client readf;// read from 
	int input;
	int clientID;


//privateFIFO	

	clientID = getpid();
  	sprintf(writet.privateFIFO, "FIFO%d", clientID);
	if ((mkfifo(writet.privateFIFO,0666)<0 && errno != EEXIST))
	{
		perror("cant create privateFIFO");
		exit(-1);
	}
	printf("Client: Succesfully created %s \n", writet.privateFIFO);
 
  
// open commonFIFO 
	if((fda=open("commonFIFO", O_WRONLY))<0)
     		printf("can't open commonFIFO to write\n");
 
// enter burst and io burst


	
	int h;
//arrival time

	printf("what is the arrival time: ");
	scanf("%d", &writet.arr);

//total number of input for both CPU and IO burst
	printf("how many CPU burst and I/O burst are you inputting: "); 
	scanf("%d", &writet.numburst);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//get user to enter each cpu burst and IO burst
	for (h = 1; h <= writet.numburst; h++)
	{	
		if ( h%2 != 0) //CPU is alway odd number
		{
			printf("Client: Please enter the CPU burst: ");
			scanf("%d", &writet.burst[h]);
		}	
		else //IO is alway even
		{
			printf("Client: Please enter the IO burst: ");
			scanf("%d", &writet.io[h]);
			
		}
	} 
	  



// Send data to server
	write(fda, &writet, sizeof(client)); 
	printf("Client: Data sent to server\n");



	printf("\nprivateFIFO: %s \n",writet.privateFIFO);

//open privateFIFO to read
	if((fdb=open(writet.privateFIFO, O_RDONLY))<0)
	{
		printf("\ncant open privateFIFO");
	}


	printf("\nClient: Waiting for server\n");

	
//read from privateFIFO	
	read(fdb, &readf, sizeof(client));


//Waiting Time for burst and IO
	printf("readywait time = %d\n" , readf.rdywait);
	printf("IO wait time = %d\n" , readf.iowait);
	
//turn around time

	printf("turn around time = %d\n", readf.tat);




// Close
close(fda);
close(fdb);

unlink(writet.privateFIFO);

  

printf ("\n\nall done!\n\n");
printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
return 0;
}
  





