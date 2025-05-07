#include <stdio.h>

struct st {
	int a;
	int b;
	struct st* p;
};

struct st node1;
struct st node2;
struct st node3;

void fun() {
	printf("aaa");
}

int main()
{
	node1.p = &node2;
	node2.p = &node3;
	fun();
}
