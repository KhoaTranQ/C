
/***************************************************************
* PROGRAMMER: 		Khoa Tran 
* 
* COURSE:   		CSCI 4354.01
* 
* DATE:   		November 30, 2015
* 
* ASSIGNMENT:  		Program 4
* 
* ENVIRONMENT: 		C in Unix, code in window 7 using putty
* 
* FILES INCLUDED: 	Server.c
* 
* PURPOSE: 		Design and write the client and server 
*			programs necessary to provide a 
*			multiple client CPU scheduler that 
*			handles CPU bursts and I/O bursts. 
*
* INPUT: 		A CPU burst and I/O burst from clients
*			Arrival time from clients
*									
*
* PRECONDITIONS:  	Begin at Time zero
*			Can ask for number of clients
*			Round robin for ready state	
*  			FCFS for I/O Queue
*
*
* OUTPUT:  		Avg Turn around time
*			Avg Ready wait time
*			Average I/O Wait time
*			Content of ready queue
*															
*
* POSTCONDITIONS: 	None	
*
*
* ALGORITHM: 		
*
*			Create server structure
			create new structure
*			Set quantum
*			Prompt User to enter number of clients
*			Create commonFIFO
* 			
*			read server structure from commonFIFO
*			While counter less than clients
				Open commonFIFO to read
*				Ready Arrival time from CommonFIFO
*				for each iteration of bursts
*				For counter < total number of burst for each client
*					if counter = odd
*						increment total time in CPU
*						copy Burst from commonFIFO to new[][]
*					if counter = even
*						increment total time in IO
*						copy I/O Burst from commonFIFO to new[][]
*				end for 	
*				Calculate Ready waiting time
*				Calculate I/O waiting time
*				Calculate Turn around time		
*				Increment counter
*			end while
*			while condition is not meet
*				if finished
*					condition is meet end while
*				while row < number of clients
*					for ( collum < iteration)
*						If collumn is odd
*							if queue[row][collumn] > quantum
*								copy to rdy[][]
*								if rdy[][] != 0
*									calculate excess
*									put excess to wait
*									incremet time in cpu
*							if queue[][] <= quanum
*								copy to rdy[][]
*								if rdy[][] != 0
*									wait = 0
*									increment time in cpu
*						else collumn is even
*							put to rdy[][]
*							calculate time in IO
*					end for
*				end while
*				for (row < clients)
*					for (collumns < iterations)
*						if( wait[row][collumns] > 0)
*							add wait to CPU
*					end for
*				end for
*			end while
*			CPU utilization = (finish time  - totalidle time )/ finish time		
*			avg turn around time = finish time - arrival time / clients
*			avg wait time = total idle time / clients
*			avg I/O wait time = total I/O idle / clients	
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
***************************************************************/


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <float.h>



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
} server; 



typedef struct//data from each client in 1 row, start at column 1, 
		 //odd = cpu burst, even = io burst
{

int n[50][50]; 

}new;


int main (void)

{
int fda; // to read 
int fdb; // to write 
int client = 0; 
float q = 4;//quantum
int h;


server readf; //read from
server writet; //write to
new queue;





// Get number of clients 
printf("Server: Enter number of clients: ");
scanf("%d", &client);




int parr[50];
int pburstcount[50];
int i = 1;

while( i <= client )
{

// Create commonFIFO
if ((mkfifo("commonFIFO",0666)<0 && errno != EEXIST))
{
	perror("cant create commonFIFO");
	exit(-3);
}
 

// read from commonFIFO
	if((fda=open("commonFIFO", O_RDONLY))<0)
		printf("cant open commonFIFO to read");
 



//print out CPU and IO burst
	if(read(fda, &readf, sizeof(server))>0)
	{

		printf("%s: ",readf.privateFIFO);
		for ( h = 1; h <= readf.numburst; h++)
		{
			if ( h%2 != 0) //CPU is odd
			{
				printf("%d ", readf.burst[h]);
				queue.n[i][h] = readf.burst[h];//put cpu burst to ready queue
				 
				//[row][collumn]			
			}	

			else //IO is even
			{
				printf("(%d) ",readf.io[h]);
				queue.n[i][h] = readf.io[h];//put io burst to ready queue
								
			} //[row][collumn]

			 

		}
		printf("\n");
		
		pburstcount[i] = readf.numburst; // total number of burst for each client
		parr[i] = readf.arr; // arrival time for each client
	}


//open privateFIFO
	if((fdb=open(readf.privateFIFO, O_WRONLY))<0) 
	{
		printf("cant open privateFIFO\n");
		
	}






//calculate ready wating time, io waiting time, turnaround time.
int t = readf.arr;
int iostart = t + readf.burst[1]; //io start time
int tio = iostart; //io start time
int temp = 0;
int tincpu = 0; // time in cpu
int tinio = 0; // time in io
 
	for (h = 1; h <= readf.numburst; h++)
	{
		
		if ( h%2 != 0) //CPU is odd
			{

				t += readf.burst[h];
				tincpu += readf.burst[h]; // calculate time in cpu

			}
	
		else //IO is even
			{
											
				tio += readf.io[h];
				tinio += readf.io[h]; //calculate time in IO
			}
	
	}

//Waiting Time = arrival time ( only deal with 1 program here)
	writet.rdywait = readf.arr;
	printf("readywait time = %d\n" , writet.rdywait);
	writet.iowait = tio  - tinio;
	printf("IO wait time = %d\n" , writet.iowait);
	
//turn around time = final time - arrival time

	writet.tat = t - readf.arr;
	printf("turn around time = %d\n", writet.tat);
	printf("___________________________________\n");


//write to privateFIFO
	write(fdb, &writet, sizeof(server));// write to client


	close(fda);
	close(fda);
	i++;//increment the while loop

//end for each client
unlink("commonFIFO"); 
}



int l;
int j; 


//print out all the clients
for (j = 1; j <= client; j++)//row
{

	printf("Client %d: arrival time = [%d] ~~~ ", j, parr[j]);
	
	for (l = 1; l <= pburstcount[j]; l++)//collumn
	{
		if (l%2 != 0) //odd is cpu burst
		{
			printf("%d ", queue.n[j][l]);
			
		}
		
		else // even is IO burst
		{
			printf("(%d) ", queue.n[j][l]);
			
		}
	}
	printf("\n");

}





//doing the round robin for all clients

double cpu = parr[1];  // use to finishing time 
double io = cpu + queue.n[1][1]; // io finishing time

int extra = 1;//

double idle = 0; //each idle for cpu
double totalidle = parr[1]; // total cpu idle
double ioidle = idle + queue.n[1][1]; // total io idle
double totalioidle = ioidle; // total idle time in IO



int rdy[50][50] = {{0}};
int wait[50][50] = {{0}};
int bb = 1;
int b;
int z;
int cc = 1;//for each iteration cpu first then io


int ticpu = 0; //time in cpu
int tiio = 0; // time in io

while (extra != 0) 
{
	if (cc >= 6)
	{
		extra = 0;
	}


	j = 1;
	while( j <= client) //row
	{

		for (l = cc; l < cc + 2; l++) //collumn
		{ 

			if ( l%2 != 0) //CPU is odd
			{
				if( queue.n[j][l] > q)
				{	
				
					
					rdy[j][l] = queue.n[j][l];

					if(rdy[j][l] != 0)
					{
						wait[j][l] = rdy[j][l] - q; //put excess into wait 
						cpu += q;
						ticpu +=q;

					}
					

				} 
		
				if (queue.n[j][l] <= q)
				{
					rdy[j][l] = queue.n[j][l];

					if(rdy[j][l] != 0)
					{
						cpu += rdy[j][l];
						wait[j][l] = 0;
						
						ticpu += rdy[j][l];

					}


				}


				
			}

			else //io is even
			{
				rdy[j][l] = queue.n[j][l];
				io += rdy[j][l];	
				
				tiio += rdy[j][l];
			}

		
			

		}//end for loop


		



	j++;
		
	}//end while (j <= client)
	
	


	
	for(b = 1; b <= client; b++) // add in excess after IO is finish
	{
		for(z = cc; z < cc + 2; z++)
		{
			if(wait[b][z] > 0)
			{
				cpu += wait[b][z];
				
			}
		} 

	}//end for


	if(io > cpu )
	{
		idle = io - cpu;
		cpu += idle;
		totalidle += idle;
	}

	

	cc += 2;


} //end while 


printf("CPU finish at : %.1f\n", cpu);
printf("I/O finish at : %.1f\n", io);

double ult = (cpu - totalidle) /cpu  * 100; 
double avgt = (cpu - parr[1])/ client;
double avgr = totalidle / client;
double avgio = totalioidle / client;

printf("\nCPU utilization: %.2f percent \n", ult);
printf("Average Turnaround time %.2f\n", avgt);
printf("Average ready wait time %.2f\n", avgr);
printf("Average I/O wait time %.2f\n", avgio);






printf("\nServer: all done.\n ");
unlink("commonFIFO"); 



return 0;
}
