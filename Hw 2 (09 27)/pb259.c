/*
	Author: Vlad Burca
	Date: 09-27-2011
	File: pb259.c
*/

#include <stdio.h>

/* First, we clear the 3 left-most bytes of
	x and we clear the right-most byte of y;
	then we add x + y so the all the bytes get
	in their desired place.
*/


int main() {
	unsigned int x, y;
	printf("x = "); 
	scanf("%x", &x); 
	printf("y = ");
	scanf("%x", &y);	 
	x = (x << 24) >>  24;
	y = (y >> 8) << 8;
	printf("\n Replace = %#x \n", x + y);
	return 0;
}
