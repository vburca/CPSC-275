/*
	Author: Vlad Burca
	Date: 09-27-2011
	File: pb277.c
*/

#include <stdio.h>

/* Since we have the "biased" formula that
	works only for negative integers, we try to
	make it work also for positives - where the
	actual formula is x >> k. Therefore, we 
	observe that we have to get rid of the extra
	terms. In this case, the most reasonable way
	to do so is to substract 1 from both 1's from
	the formula; but we need to do this only when
	x >= 0. But when x is positive, the
	most significant bit of it is 0. Therefore, we
	need to get the most significant bit of x and
	add the bitwise not of it to both 1's from the 
	formula. A similar reasoning applies when 
	x < 0. Therefore, when x >= 0, we will get
	rid of the extra terms by having
	(1 - 1) << k  = 0  and (1 - 1) = 0, getting the
	desired formula that works for positive x's.
	When x < 0, we have (1 - 0) << k  and - 1 in 
	the formula, which gives us the right formula
	for the negative x's. Thus we created a universal
	formula for all x's.
*/ 

int divide_power2(int x, int k) {
	int r = x >> (sizeof(int) - 1);
	return (x + ((1 + ~r) << k) - (1 + ~r)) >> k;
}

int main() {

	int x, k;
	
	printf(" x = ");
	scanf("%d", &x);
	printf(" k = ");
	scanf("%d", &k);

	printf("\n RESULT = %d \n", divide_power2(x, k));
	
	return 0;

}
