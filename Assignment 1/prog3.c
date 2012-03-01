/*
    Author: Vlad Burca
    Date: 09/11/2011
    Problem: Sort of Like Sorting
*/

#include <stdio.h>

void sort(int *nr) {

    int i, aux, g;

    while (g != 0) {
        g = 0;
        for (i = 0; i < 9; i++)
            if (nr[i] > nr[i + 1]) {
                aux = nr[i];
                nr[i] = nr[i + 1];
                nr[i + 1] = aux;
                g = 1;
            }
    }

}


int main() {

    int nr[10], sorted[10], i, start, end;

    for (i = 0; i < 10; i++)
        scanf("%d", &nr[i]);
    sort(nr);
    start = 0;
    end = 9;
    for (i = 0; i < 10; i++)
        if (i % 2 == 0)
            sorted[start++] = nr[i];
        else
            sorted[end--] = nr[i];
    for (i = 0; i < 10; i++)
        printf("%d ", sorted[i]);
    printf("\n");

    return 0;

}
        
