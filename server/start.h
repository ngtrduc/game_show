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
#include "lib/cauhoi.h"
#include "lib/login_signup.h"


#define FULL_CLIENT 10
#define PORT 5500
#define MAX_PLAYER 2

typedef struct answer{
    char answ;
    int player;
}answer;
//-----------------------------------------
int listenSock;
int client[FULL_CLIENT];
int player[MAX_PLAYER];
fd_set readfds;

//-----------------------------------------------



int create_listenSock(int port)
{
    //int master_socket;
    struct sockaddr_in address;
    if( (listenSock = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
    {
        perror("socket failed");
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    //bind socket
    if (bind(listenSock, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        perror("bind failed");
        return -1;
    }
    printf("Listener on port %d \n", PORT);
    if (listen(listenSock, 3) < 0)
    {
        perror("listen");
        return -1;
    }
    puts("Waiting for connections ...");
    return 0;
}
void ch_to_pro(protocol *p,cauhoi ch)
{
    strcpy(p->ch.cauhoi,ch.cauhoi);
    strcpy(p->ch.dapan1,ch.dapan1);
    strcpy(p->ch.dapan2,ch.dapan2);
    strcpy(p->ch.dapan3,ch.dapan3);
    strcpy(p->ch.dapan4,ch.dapan4);
    p->ch.dapan_dung=ch.dapan_dung;
}
void play_phu(cauhoi *ch)
{
    protocol p;
    int i;
    //int vitri=rand()%10;
    p.flag=SUB_QUES;
    ch_to_pro(&p,ch[0]);

    for(i=0;i<=MAX_PLAYER;i++){
        send(player[i],&p,sizeof(protocol),0);
    }
    
}

check_dapan(cauhoi ch,char dap_an)
{
    if (ch.dapan_dung==dap_an) return 1;
    else return 0;
}

int start_server()
{   

    int check=0;
    cauhoi *ch;
    int connSock;
    int j=0,main_socket,i,k=0;
    int max_sd,sd,nEvents;
    struct sockaddr_in address;  
    int addrlen = sizeof(address);
    for(i=0;i<=FULL_CLIENT;i++) client[i]=-1;
    protocol p;
    answer a[MAX_PLAYER];

    create_listenSock(PORT);

    while(1)
    {
        FD_ZERO(&readfds);
        FD_SET(listenSock, &readfds);
        max_sd = listenSock;
            for ( i = 0 ; i < FULL_CLIENT ; i++) 
        {
            
            sd = client[i];
            if(sd > 0)
                FD_SET( sd , &readfds);
            if(sd > max_sd)
                max_sd = sd;
        }
        nEvents = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
            if (nEvents < 0) printf("select error...\n");
        if (FD_ISSET(listenSock, &readfds)) 
        {
            if ((connSock = accept(listenSock, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
          
            
            printf("New connection , socket fd is %d \n" , connSock);
            // them socket vao socket list
            for (i = 0; i < FULL_CLIENT; i++) 
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

        for (i = 0; i < FULL_CLIENT; i++) 
        {
            sd = client[i];
              
            if (FD_ISSET( sd , &readfds)) 
            {
                
                if (recv( sd , &p,sizeof(protocol),0) == 0)
                {
                   
                    printf("Client disconnected...\n"); 
                    close( sd );
                    client[i] = -1;
                }
                else{
                    switch(p.flag){
                    case LOGIN: s_login(&p);
                            break;
                    case SIGNUP: s_signup(&p);
                            break;
                    case ENTER_ROOM:if(j==MAX_PLAYER) p.flag=FULL;
                                    if(j<MAX_PLAYER){
                                        player[j]=sd;j++;
                                        printf("we have %d player\n",j);
                                    }
                                    break;
                    case SUB_ANSWER: a[k].answ=p.answer;
                                     a[k].player=sd;
                                     k++; break;
                                 
                }
                if(p.flag!=ENTER_ROOM) send(sd,&p,sizeof(protocol),0);
                }
                
            }
        }
        if(j==MAX_PLAYER){
                ch=lay_cauhoi(1,0);
                if(check==0) play_phu(ch);
                check=1;
            }
        if(k==MAX_PLAYER){
           for(k=0;k<=MAX_PLAYER;k++) {
                if(check_dapan(ch[0],a[k].answ)) main_socket=a[k].player;
            }
            printf("nguoi chien thang la nguoi choi %d",main_socket);
            check =0;
            j=0;
            k=0;
        }
    }

}
