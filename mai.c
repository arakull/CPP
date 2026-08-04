#include <stdio.h>
#include <math.h>



int main(void)
{
    int a;
    int b;
    int c;

    printf("Enter the coefficient a before x^2\n");
    scanf("%f", &a);

    printf("Enter the coefficient b before x\n");
    scanf("%f", &b);

    printf("Enter the coefficient c\n");
    scanf("%f", &c);

    printf("%fx^2 + %fx + %f = 0\n", a, b, c);

    float D = b * b - 4 * a * c;


    if (D < 0)
    {
        printf("There are no solutions\n");
    }

    else
    {
        float Dsq = sqrt(D);
        if (D == 0)
        {
            float x1 = (-b) / (2 * a);

            printf("The equation has a unique solution\n");
            printf("x = %.3f\n", x1);
        }
        else
        {
            float x1 = (-b + Dsq) / (2 * a);
            float x2 = (-b - Dsq) / (2 * a);

            printf("x1 = %.3f\n", x1);
            printf("x2 = %.3f\n", x2);
        }
    }
    return 0;
}
