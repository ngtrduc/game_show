#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#define BO_CAUHOI 15
#define TRUE   1
#define FALSE  0
#define MAX_CLIENT 10
#define PLAYER_NUM 4
#define BUFF_SIZE 256
enum {SUCCESS,FAIL};
// tao listenSock vs PORT la so hieu cong
int create_listenSock(int PORT)
{
	int master_socket;
	struct sockaddr_in address;
	if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
    {
        perror("socket failed");
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    //bind socket
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        perror("bind failed");
        return -1;
    }
    printf("Listener on port %d \n", PORT);
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        return -1;
    }
    puts("Waiting for connections ...");


    return master_socket;

}
void acept_connection(int listenSock,int *client,fd_set readfds)
{
	char buff[1025];
	int connSock,i;
	int max_sd,sd,nEvents,j=0;
	struct sockaddr_in address;
      
	int addrlen = sizeof(address);
	while(TRUE){
       	FD_ZERO(&readfds);
  
        //them listen socket vao fdset
        FD_SET(listenSock, &readfds);
        max_sd = listenSock;
         
        //them soc ket vao fdset
        for ( i = 0 ; i < MAX_CLIENT ; i++) 
        {
            
            sd = client[i];
            if(sd > 0)
                FD_SET( sd , &readfds);
            if(sd > max_sd)
                max_sd = sd;
        }
        
        nEvents = select( max_sd + 1 , &readfds , NULL , NULL , NULL);   
        if (nEvents < 0) 
        {
            printf("select error...\n");
        }
        if (FD_ISSET(listenSock, &readfds)) 
        {
            if ((connSock = accept(listenSock, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
          
           	
            printf("New connection , socket fd is %d \n" , connSock);
        	j++;
           	// them socket vao socket list
            for (i = 0; i < MAX_CLIENT; i++) 
            {
                //neu vi tri chua co' socket toi

                if( client[i] == -1 )
                {
                    client[i] = connSock;
                    printf("Adding socket to socket list on %d\n" , i);
                    
                    break;
                }
            }
        }
          
        
        for (i = 0; i < MAX_CLIENT; i++) 
        {
            sd = client[i];
              
            if (FD_ISSET( sd , &readfds)) 
            {
                
                if (recv( sd , buff, 1024,0) == 0)
                {
                   
                    printf("Host disconnected...\n"); 
                    close( sd );
                    client[i] = -1;
                    j--;
                }
            }
        }
    	if(j==PLAYER_NUM){
    		printf("We have %d player to play!!!\n",j);
    		break;
    	}
    }
}
int send_bocauhoi(int sockfd,int i)
{
    FILE *fp;
    char buff[BUFF_SIZE];
    char ten_bocauhoi[15]="bo_cauhoi";
    char b[3];
    char temp[15];
    sprintf(b, "%d", i);
    strcat(ten_bocauhoi,b);
    strcat(ten_bocauhoi,".dat");
    fp=fopen(ten_bocauhoi,"r");
    while(1){
        //lam rong bo nho dem
        memset(buff,'\0',sizeof(buff));

        int nread = fread(buff,1,BUFF_SIZE,fp);

        printf("so byte doc duoc : %d\n",nread);
        if(nread>0){
            printf("bat dau gui du lieu...\n");
        }
        send(sockfd,buff,nread,0);
        if(nread<BUFF_SIZE){
        if(feof(fp)) printf("Ket thuc file...\n");
        if(ferror(fp)) printf("loi doc file...\n");
        break;
        }
    }
    fclose(fp);
    return SUCCESS;

}
int send_all(int *client,fd_Set readfds, int flag )
{
	int recvbytes;
	char buff[100];
	int i,s,j,vi_tri;
	for (i = 0; MAX_CLIENT; i++) 
        {
            switch(flag){
                case 0: for(j=0,j<=BO_CAUHOI,j++) send_bocauhoi(client[i],j);
                        break;
                case 1: vi_tri=rand()%10;
                        makecode(buff,1,0,vi_tri);
                        send(client[i],buff,4,0);
            }
            
        }
    return SUCCESS;
}








