#include <stdio.h>

void func(int arr[][5])
{
	printf("%ld %ld %ld\n", sizeof(arr), sizeof(arr[1]), sizeof(arr[1][1]));
}
int main()
{
	int arr[10][10];

	printf("%ld %ld %ld\n", sizeof(arr), sizeof(arr[1]), sizeof(arr[1][1]));
	func(arr);
}
