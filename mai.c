    #include <stdio.h>
    int a;
    int b;
    int main(void)
    {
        scanf("%d",&a);
        scanf("%d",&b);
        if (a>b)
        {
        printf("Первое число больше\n");
        }
        else if (a<b)
        {
            printf("Второе число больше\n");
        }
        else
        {
        printf("Числа равны\n");
        }

            return 0;
    }
