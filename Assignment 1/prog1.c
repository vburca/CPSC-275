/*
    Author: Vlad Burca
    Date: 09/11/2011
    Problem: Case of the Missing Numbers
*/

#include <stdio.h>

int main() {
    
    int nr[100] = { 0 }, x, i, n;

    scanf("%d", &x);
    while (x != 0) {
        if (nr[x - 1] == 0)
            nr[x - 1] = 1;
        scanf("%d", &x);
    }
    n = 0;
    for (i = 0; i < 100; i++) {
        if (nr[i] == 0) {
            printf("%d ", i + 1);
            n++;
        }
        if (n == 10) {
            n = 0;
            printf("\n");
        }
    }
    printf("\n");

    return 0;

}
