#include <arpa/inet.h> 

enum {SUCCESS,FAIL};

int create_connection(int PORT,char IP[10])
{
	int sockfd;
	struct sockaddr_in serverAddr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		printf("khong the tao duoc socket\n");
		return FAIL;
	}
	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(IP);
	if(connect(sockfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){
	printf("ket noi den server that bai\n");
	return FAIL;
	}
	printf("server duoc ket noi thanh cong ...\n");
	return sockfd;
}
int main()
{
	int sockfd=create_connection(5500,"127.0.0.1");
	int n;
	printf("1.LOGIN\n");
	printf("2.SIGNUP\n");
	
	printf("4.QUIT\n");
	scanf("%d",&n);
	while(getchar()!='\n');
	if(n==1) login(sockfd);
	
}
