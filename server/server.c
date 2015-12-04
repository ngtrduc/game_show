#include "start.h"

int main()
{
	int n;
	printf("1.START\n");
	printf("2.THEM CAU HOI\n");
	printf("3.SUA CAU HOI\n");
	printf("4.QUIT\n");
	scanf("%d",&n);
	while(getchar()!='\n');
	if(n==1) start_server();
}