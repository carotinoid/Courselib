#include<stdio.h>

int main(){
	int no=100;
	int val;
    __asm(
          "movl %1, %%ebx\n\t"
          "add $5, %%ebx\n\t"
          "movl %%ebx, %1\n\t"
          : "=r" (val)
          : "r" (no)
          : "ebx" 
            );
	printf("%d \n", val);
	return 0;
}


