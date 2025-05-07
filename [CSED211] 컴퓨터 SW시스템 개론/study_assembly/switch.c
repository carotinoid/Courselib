#include <stdio.h>

int divide_by_five(int x) {
	x = x / 5;
	return x;
}

int main() 
{
	int x;
	scanf("%d", &x);
	x = divide_by_five(x);
	switch(x) {
		case 1:
		printf("1");
		break;
		case2:
		printf("2");
		break;
		case3:
		printf("3");
		break;
		default:
		printf("asdf");
	}
}
