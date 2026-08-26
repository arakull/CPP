#include <stdio.h>

int minus_of_int(int x);


int main(void)
    {
        int x=0, d = 0;
        scanf("%d",&x);
        d= minus_of_int(x);
        printf("%d", d);
    }

int minus_of_int(int x)
    {
        int d = 0;
        d= -x;
        return d;
    }
