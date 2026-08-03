    #include <stdio.h>
    #include <math.h>
    int a;
    int b;
    int c;
    int main(void)
    {
        printf("Enter the coefficient a before x^2\n");
        scanf("%d",&a);

        printf("Enter the coefficient b before x\n");
        scanf("%d",&b);

        printf("Enter the coefficient c\n");
        scanf("%d",&c);
#include <stdio.h>
#include <math.h>

int a;
int b;
int c;

int main(void)
{
    printf("Enter the coefficient a before x^2\n");
    scanf("%d", &a);

    printf("Enter the coefficient b before x\n");
    scanf("%d", &b);

    printf("Enter the coefficient c\n");
    scanf("%d", &c);

    printf("%dx^2 + %dx + %d = 0\n", a, b, c);

    float D = b * b - 4 * a * c;
    float Dsq = sqrt(D);

    if (D < 0)
    {
        printf("There are no solutions\n");
    }
    else if (D == 0)
    {
        int x1 = (-b) / (2 * a);

        printf("The equation has a unique solution\n");
        printf("x = %d\n", x1);
    }
    else if (Dsq == (int)Dsq)
    {
        int x1 = (-b + Dsq) / (2 * a);
        int x2 = (-b - Dsq) / (2 * a);

        printf("x1 = %d\n", x1);
        printf("x2 = %d\n", x2);
    }
    else
    {
        float x1 = (-b + Dsq) / (2 * a);
        float x2 = (-b - Dsq) / (2 * a);

        printf("x1 = %.3f\n", x1);
        printf("x2 = %.3f\n", x2);
    }

    return 0;
}
        printf("%dx^2 + %dx + %d=0\n",a,b,c);

        float D = (b*b-4*a*c);
        float Dsq = sqrt(D);
        if (D<0)
            {
                printf("There are no solutions\n");
            }
        else if (D==0)
            {
                int x1=(-b)/(2*a);
                printf("The equation has a unique solution \n");
                printf("x=%d\n",x1);
            }
        else if (Dsq==(int)Dsq)
            {
                int x1=(-b+Dsq)/(2*a);
                int x2=(-b-Dsq)/(2*a);
                printf("x1=%d\n",x1);
                printf("x2=%d\n",x2);
            }
        else
            {
                float x1=(-b+Dsq)/(2*a);
                float x2=(-b-Dsq)/(2*a);
                printf("x1=%.3f\n",x1);
                printf("x2=%.3f\n",x2);
            }
        return 0;
    }
