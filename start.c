#include <stdio.h>
#include <string.h>   
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   
#include <arpa/inet.h>    
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> 
#include "cauhoi.h"

#define PORT 5500
#define MAX_CLIENT 4
enum {SUCCESS,FAIL};
int play_phu(int client[3])
{
    int client;
    int min_time=15;
    int recvbytes,i,vi_tri=rand()%10;
    char buff[15];
    struct cauhoi *ch;
    struct dapan *da;
    ch=lay_cauhoi("cauhoi_phu",vi_tri);
    for(i=0;i<4;i++){
        send(client[i],ch,sizeof(struct cauhoi),0);
    }
    in_cauhoi(ch[0]);
    for(i=0;i<4;i++){
        recvbytes=recv(client[i],da,sizeof(struct dapan),0);
        buff[recvbytes]='\0';
        if(strcmp(da.dapan,"dung")) {
            if(da.time<min_time)
            {min_time=da.time;
            client=client[i];}
            }
    }
    return client;
}
void start()
{
    int client;
	int listenSock,addrlen, connSock, client[9]={-1};
	int nEvents,sd;
	int max_sd;
	int i,j=0;
	struct sockaddr_in address;
	int recvbytes,sentbytes;
	fd_set readfds;

	if( (listenSock = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("Listen Socket are created...\n");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
 	if (bind(listenSock, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Bind successed ...\n");
    if (listen(listenSock, 10) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    addrlen =sizeof(address);
    printf("Waiting for connection");

    while(1)
    {
    	FD_ZERO(&readfds);
  
        //them listen socket vao fdset
        FD_SET(listenSock, &readfds);
        max_sd = listenSock;
        for ( i = 0 ; i < max_clients ; i++) 
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
            perror("select");
            continue;
        }
        while (FD_ISSET(listenSock, &readfds)) 
        {
  			
            if ((connSock = accept(listenSock, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
          
           	
            printf("New connection , socket fd is %d \n" , connSock);
        	
           	// them socket vao socket list
            for (i = 0; i < 10; i++) 
            {
                //neu vi tri chua co' socket toi

                if( client[i] == -1 )
                {
                    client[i] = connSock;
                    printf("Adding socket to socket list on %d\n" , i);
                     
                    break;
                }
            }
            j++;
            if(j==4) break;
        }
        printf("Bat dau choi\n");
        client=play_phu();
        for(i=0;i<4;i++){
            if(client[i]!=client) close(client[i]);
        }
        play();
        
    }

}
