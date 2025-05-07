#include <stdio.h>

int main()
{
    float f1, f2 = 0.2, f3 = 1.5;
    scanf("%f", &f1);
    float f4 = f2 + f3;
	float f5 = f4 / f1;
	printf("%f", f5);

	float f6;
	scanf("%lf", &f6);
	float f7 = f5 * f6;
	printf("%lf", f7);
}   
