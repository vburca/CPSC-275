/*
    Author: Vlad Burca
    Date: 09/11/2011
    Problem: Did You Order This Product?
*/

#include <stdio.h>

void rev_sort(int x, char *rev) {

    int digit[10] = { 0 }, i, j;
    
    if (x == 0)
        digit[x % 10]++;    

    while (x) {
        digit[x % 10]++;
        x = x / 10;
    }
    j = 0;
    for (i = 0; i <= 9; i++)
        while (digit[i]) {
            rev[j++] = '0' + i;
            digit[i]--;
        }

}    

int main() {
    
    int n1, n2;
    char rev[10] = { '\0' };

    scanf("%d %d", &n1, &n2);
    rev_sort(n1 * n2, rev);
    printf("%s \n", rev);

    return 0;

}
