#include <stdio.h>
#include <string.h>

int mdays[13] = {-1, 31, 28, 31, 30, 31, 
				30, 31, 31, 30, 31, 30, 25}; // 25 - Christmas
											
int main(int argc, char* argv[]) {

	int m, d, days = 0;
	if (argc == 3) {
		m = atoi(argv[1]);
		d = atoi(argv[2]);
		days = mdays[m] - d;
		m++;
		while (m <= 12) {
			days = days + mdays[m];
			m++;
		}
		printf("%d days left till Christmas\n", days);
	}
	else
		printf("Incorrect input\n");
	
	return 0;
}
		 
