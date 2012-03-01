#include <stdio.h>
#include <stdlib.h>

int diagonal(int **m, int n) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (m[i][j] != 0 || m[j][i] != 0)
				return 0;
	return 1;
}

int identity(int **m, int n) {
	int i;
	for (i = 0; i < n; i++)
		if (m[i][i] != 1)
			return 0;
	return 1;
}

int lower(int **m, int n) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (m[i][j] != 0)
				return 0;
	return 1;
}

int upper(int **m, int n) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (m[j][i] != 0)
				return 0;
	return 1;
}


int check_matrix(int **m, int n) {
	if (diagonal(m, n) && identity(m, n))
		return 2;
	else if (diagonal(m, n)) 
			return 1;
	else if (lower(m, n))
			return 3;
	else if (upper(m, n))
			return 4;
		else
			return -1;
}

int main() {

	int n, i, j;
	scanf("%d", &n);
	
	int **m = (int **) malloc(n * sizeof(int));
	
	for (i = 0; i < n; i++)
		m[i] = (int *) malloc(n * sizeof(int));

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &m[i][j]);

	switch(check_matrix(m, n)) {
		case 1: printf("Diagonal matrix\n"); break;
		case 2: printf("Identity matrix\n"); break;
		case 3: printf("Lower triangular matrix\n"); break;
		case 4: printf("Upper triangular matrix\n"); break;
		case -1: printf("No special case detected\n"); break;
	}

	return 0;
}
	
