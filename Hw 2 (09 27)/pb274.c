/*
	Author: Vlad Burca
	Date: 09-27-2011
	File: pb274.c
*/

#include <stdio.h>

/* We need to check for positive and negative overflow.
	In order for a negative overflow to occur, we need
	these conditions: x < 0 and y > 0; also, when a
	negative overflow occurs, then x - y > 0. On the
	second part, for a positive overflow to occur, we
	need these conditions: x > 0 and y < 0; also, when
	a positive overflow occurs, then x - y < 0. So we
	have to check for either one of these two events.
*/ 

int tsub_ok(int x, int y) {

	return !((x < 0 && y > 0 && ((x - y) > 0)) 
		|| ((x > 0) && (y < 0) && (x - y) < 0)); 

}

int main() {

	int x, y;
	printf(" x = ");
	scanf("%d", &x);
	printf(" y = ");
	scanf("%d", &y);
	
//	printf("\n Difference = %d", x - y);	
	printf("\n RESULT = %d \n", tsub_ok(x, y));

	return 0;

}

