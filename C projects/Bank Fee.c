/*
PROGRAMMER: khoa Tran
b. COURSE: CSCI 3133.01
c. DATE: feb 6, 2014
d. ASSIGNMENT: program 2
e. ENVIRONMENT: window 7, visual studio 2012
f. FILES INCLUDED: Visual studio 2012


h. INPUT: Allow your application to select the type of account and enter the number of checks written. The application should compute and display the bank’s service fees for the month

i. PRECONDITIONS: Input validation: Do not accept a negative value for the number of checks written


j. OUTPUT: All checks for the month are assigned the same charge, based on the total number of checks written during the month.
k. POSTCONDITIONS: Input validation: Do not accept a negative value for the number of checks written
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>



int main()

{

	int menuchoice;

	printf( "Menu choices\n");
	printf( "<1> Checking\n");
	printf( "<2> Money-Market\n\n");
	printf("Please enter 1 for Checking or 2 for Money-Market:\n");
	scanf_s("%d", &menuchoice);


	if (menuchoice == 1)
		
	{
		printf("\nChecking Account\n");
		printf("Your Total Charge is $15.00\n\n");
		printf("--------------------------------------------------------------------------------");
		return main();
	}


	if (menuchoice == 2)
	{
		float mm = 10;
		int check;
		printf("\nMoney-Market\n");
		printf("Please Enter number of checks: ");
		scanf_s("%d", &check);

		if (check > 0 && check < 20)
			{
			float a = 0.1;
			float total = mm + check*a;
			printf("\nYour Total Charge = $%.2f\n\n",total);
					printf("--------------------------------------------------------------------------------");
			}


		if (check >= 20 && check < 39)
			{
			float b = 0.08;
			float total = mm + check*b;
			printf("\nYour Total Charge = $%.2f\n\n",total);
					printf("--------------------------------------------------------------------------------");
			}


		if (check >= 40 && check < 59)
			{
			float c = 0.06;
			float total = mm + check*c;
			printf("\nYour Total Charge = $%.2f\n\n",total);
					printf("--------------------------------------------------------------------------------");
			}


		if (check >= 60)
			{
			float d = 0.04;
			float total = mm + check*d;
			printf("\nYour Total Charge = $%.2f\n\n",total);
					printf("--------------------------------------------------------------------------------");
			}

		else if (check < 0)
		{
			
			printf("\nINVALID number of check please check your input\n\n");
					printf("--------------------------------------------------------------------------------");
		}// validation for input number of checks

		return main();
	}

	

	if (menuchoice != 2 && menuchoice != 1)
	{
		printf("\nINVALID Choice please pick a valid option\n\n");
		return main();

	}//validation for input choices


	



	system("pause");
	
	return 0;
	
}