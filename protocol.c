#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#define LOGIN 1
#define SIGNUP 2
#define SUCCESS 3
#define FAIL 4
#define SEND_QUE 7
#define RECV_ANSWER 8
#define ENTER_ROOM 10
typedef struct protocol{
	int flag; // 
	struct user u; // thong tin dang nhap
	int bo_cauhoi; // so hieu bo cau hoi 
	int vi_tri; //vi tri trong bo cau hoi
	char dap_an;

}protocol;

int gui_dulieu(protocol p,int sockfd)
{
	send(sockfd,&p,sizeof(protocol),0);
}
int nhan_dulieu(protocol p, int sockfd)
{
	recv(sockfd,&p,sizeof(protocol),0);
}