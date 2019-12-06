
//PROGRAMMER: khoa Tran
//b. COURSE: CSCI 3133.01
//c. DATE: january 29, 2014
//d. ASSIGNMENT: program 1
//e. ENVIRONMENT: visual studio 2012
//f. FILES INCLUDED: Visual studio 2012
//(1)   Practice writing Pseudocode and Flowchart
//(2)   Practice UHCL Documentation
//(3)   Practice using Expressions and operators in C

//h. INPUT: Radius of a circle 
//i. PRECONDITIONS: use constant pi = 3.14159 

//j. OUTPUT: Diameter, circumference, arena and the radius
//k. POSTCONDITIONS: use constant pie = 3.14159


#include <stdio.h>
#include <math.h>
#include <stdlib.h>



int main(int r)
{
	float p = 3.14159;
	float dia,cir,area;

	printf("enter radius: ");
	scanf_s("%d",&r);
	
	printf("the radius of the circle is %2d\n",r);

	dia = 2*r;
	printf("The diameter of the circle is %2f\n",dia);

	cir = 2*p*r;
	printf("The circumference of the circle is %2f\n",cir);

	area = p*r*r;
	printf("The area of the circle is %2f\n\n",area);



	system ("pause");
	return 0;
}