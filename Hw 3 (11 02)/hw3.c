/*
 * Author: Vlad Burca
 * Date: 10/31/2011
 * Filename: hw3.c
 * Description: Write a rational number (fraction) as it's decimal representaiton,
 *				with repeating decimals.
 */

#include <stdio.h>

int remainders[65535];
int decimals[50];

// searches of a remainder repeated in the "history"; returns the position of repetition, else -1
int find_repeat(int r, int n_r) {
	int i;
	for (i = 0; i < n_r; i++)
		if (remainders[i] == r)
			return i;
	return -1;
}

// clears both remainders and decimals; useful when computing the decimals for next number
void clear() {
	int i;
	for (i = 0; i < 65535; i++)
		remainders[i] = -1;			// set to an impossible value for a remainder
		decimals[i] = -1;			// set to an impossible value for a decimal
}


int main() {

	int a, b;
	int integer, r, a_aux, dec;
	int n_r, n_d;
	int repeat_pos_start, repeat_pos_end, repeat_size;
	int i;	

	while (scanf("%d", &a) == 1) {
		scanf("%d", &b);
		printf("%d/%d = ", a, b);	// print fraction form
		integer = a / b;
		printf("%d.", integer);			// print the integer part
		n_r = 0;
		n_d = 0;
		clear();					// clearing decimals and remainders
		repeat_pos_start = -1;
		repeat_pos_end = -1;		// no repeating at the beginning
		a_aux = a;
		do {
			r = a_aux % b;				// get first remainder
			a_aux = r * 10;
			dec = a_aux / b;			// get first decimal, in case it is 0
			repeat_pos_start = find_repeat(r, n_r);	// find if the remainder is in the "history"
			if (repeat_pos_start != -1 && repeat_pos_end == -1)	// found start but end is not set
				repeat_pos_end = n_r;		// set the end to the last remainder
			if (n_r < 50)
				remainders[n_r] = r;			// adding the remainder to the "history"
			n_r++;
			if (n_d < 50 && repeat_pos_start == -1)	// add if we have space and \
										 if it is not the start of the repeating sequence
				decimals[n_d++] = dec;		// adding the decimal to the decimal array
			} while (((a_aux % b) != 0) && repeat_pos_start == -1);
		// printing the decimals string
		repeat_size = repeat_pos_end - repeat_pos_start;
		for (i = 0; i < n_d; i++) {
			if (repeat_pos_start == i)
				printf("(");
			printf("%d", decimals[i]);
		}
		if (repeat_pos_start != -1)
			if (n_d == 50 && repeat_size > n_d)
				printf("...), %d", repeat_size);
			else
				printf(")");
		printf("\n");	
	}
	
	return 0;
}
	
