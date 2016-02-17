#include <stdio.h>

int fact(int n)
{
	return n>1 ? n*fact(n-1) : 1;
}

int main()
{
	int n;
	printf("Hello, world, enter fact number!");
	scanf("%d",&n);
	printf("%d", fact(n));
}