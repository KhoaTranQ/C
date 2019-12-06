#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*
PROGRAMMER: khoa Tran
b. COURSE: CSCI 3133.01
c. DATE: april 10, 2014
d. ASSIGNMENT: program 4
e. ENVIRONMENT: window 7, visual studio 2012
f. FILES INCLUDED: Visual studio 2012


h. INPUT: 
1. Create an array of 100 random numbers in the range of 1…999, write a function for each of the following processes. In building the array, if 3 or 7 evenly divide the random number, store it as a negative number.
2. Create a two dimensional array (size 10 X 10). Fill this two dimensional array with the values from the above single dimensional array. Determine the maximum value in each row.  Display the two-dimensional array and the maximum of each row.
3. Repeat number 2 above but this time instead of 10 X 10 array, prompt the user for the size of the row and column, allow user to fill in the values and display the array.(Hint: Use pointers and dynamic memory allocation ) 

i. PRECONDITIONS: None


j. OUTPUT: 
a.       Print the array ten values to a line. Make sure that the values are aligned in rows.
b.      Return a count of the number of even values
c.       Return the sum of all values in the array 


k. POSTCONDITIONS: None

*/

int test();
int change( int arr[100]);

void main()
{
	int test1;

	int i;
	int j;
	int random[100];
	int sum = 0;
	int counter = 0;
	int parttwo;
	
	for (j = 0; j < 10; j++)
	{
			for (i = 0; i < 10; i++)
			{
				random[i] = rand() % 999 + 1;


				//store as negative if divisible by 3
					if ( random[i] %3 == 0)
						{
							random[i] *= -1;
						}
				//store as negative if divisible by 7
					if ( random[i] %7 == 0)
						{
							random[i] *= -1;
						}



				printf("%5d",random[i]);
				sum += random[i];
	
				
				//count the number of even numbers
					if ( random[i] %2 == 0)
						{
							counter++;
						}

			}
	
			printf ("\n");

	}
	
	printf ("\n");

	//Print out the even counts
	printf("The count for even numbers are : %2d\n", counter);
	printf ("\n");
	

	//Print out the sum
	printf("The sum is: %4d\n",sum);
	printf ("\n");

	test1 = test();
	
	parttwo = change(random);
	

	system("pause");
	return ;

}


int test()
{ 
int n=10; 
int m=15; 
int a[10][15]; 
int *b = &a[0][0]; 

int i = 3; 
int j = 4; 
printf("%p\n%p\n", 
&a[i][j], 
&b[i*m + j]); 
} 





int change( int arr[100])
{
	int arr2[10][10];
	
	int a;
	int b;
	int c = 0;
	for (a = 0; a < 10; a++)
	{
		for (b = 0; b < 10; b++)
		{
			arr2[a][b] = arr[(c)];
			c++;
			printf("%5d", arr2[a][b]);
		
		}
			printf("\n");
		
	}

	return arr2[a][b];
	
}