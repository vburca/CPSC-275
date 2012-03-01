#include <stdio.h>

int main() {
    
    int test[100] = {1, 2, 3, 4, 5};
    int len = sizeof(test) / sizeof(int);
    printf("%d", len);
    return 0;

}
