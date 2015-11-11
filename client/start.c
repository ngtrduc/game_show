#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#define FAIL -1
#define BUFF_SIZE 256
#define SUCCESS 1
int nhan_bocauhoi(int sockfd,int i)
{
	int recvbytes;
	FILE *fp;
	char ten_bocauhoi[15]="bo_cauhoi";
	char b[3];
	char buff[BUFF_SIZE];
    sprintf(b, "%d", i);
    strcat(ten_bocauhoi,b);
    strcat(ten_bocauhoi,".dat");
    fp=fopen(ten_bocauhoi,"w");
    while(1){
    	memset(buff,'\0',sizeof(buff));
		recvbytes=recv(sockfd,buff,BUFF_SIZE,0);
		if(recvbytes==0) break;
		printf("nhan du lieu tu %s...\n",ten_bocauhoi);
		fputs(buff,fp);
	}
	fclose(fp)
	return SUCCESS;
}
void get_bocauhoi()
{	printf("Loading the data, please wait....\n");
	for(i=0;i<=BO_CAUHOI;i++){
		nhan_bocauhoi(i);
	}
	printf("Load success !!\n");
	printf("------------------------------------------");
}
int get_data(char buff[15],int sockfd)
{
	recvbytes=recv(sockfd,buff,15,0);
}
int start(user u,int sockfd)
{

	int temp;
	printf("Hello,%s",u.account);
	printf("1.Enter room and Watting for other user to play\n");
	printf("2.Xem lich su\n");
	printf("3.Quit");
	scanf("%d",&temp);
	while(getchar()!='\n');
	if(temp == 1) start_game(sockfd);
}
int start_game(int sockfd)
{
	struct cauhoi *ch;
	char buff[15];
	printf("Watting for other user....");
	make_code(buff,); // them code sau
	send(sockfd,buff,100,0);
	recv(sockfd,buff,100,0);
	ch=(struct cauhoi*)malloc(sizeof(struct cauhoi));
	ch=lay_cauhoi(buff[1],buff[2])
}