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
#define MAX_PLAYER 3
#define MAX_QUES 4
//-----------------------------------------
int listenSock;
int client[FULL_CLIENT];
int player[MAX_PLAYER];
fd_set readfds;
int check=0;

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

    for(i=0;i<MAX_PLAYER;i++){
        send(player[i],&p,sizeof(protocol),0);
    }
    
}

int check_dapan(cauhoi *ch,char dap_an)
{
    if (ch->dapan_dung==dap_an) return 1;
    else return 0;
}
void check_main_p(protocol *p, cauhoi *ch)
{
    if(check_dapan(ch,p->answer)){
        if(check==0){
            p->flag=QUES;
            p->count=1;
            check=1;
        }else p->flag=MUON;

    }else p->flag=WRONG_ANSWER;

}

int start_server()
{   

    cauhoi *ch,*main_ch;
    int connSock,a=0;
    int j=0,main_socket,i,k=0;
    int max_sd,sd,nEvents;
    struct sockaddr_in address;  
    int addrlen = sizeof(address);
    for(i=0;i<=FULL_CLIENT;i++) client[i]=-1;
    protocol p[FULL_CLIENT];


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
                
                if (recv( sd , &p[i],sizeof(protocol),0) == 0) //m sua lai sau
                {
                    if(p[i].flag==ENTER_ROOM){
                        j--;
                        if(j==0) a=0;
                    }
                    if(p[i].flag==QUES) {
                        j=0;a=0;
                    }
                    printf("Client disconnected...\n"); 
                    close( sd );
                    client[i] = -1;
                } 
                else{
                    switch(p[i].flag){
                    case LOGIN: s_login(&p[i]);
                            break;
                    case SIGNUP: s_signup(&p[i]);
                            break;
                    case ENTER_ROOM:
                                    if((j==MAX_PLAYER)||(a==1)) p[i].flag=FULL;
                                    if(j<MAX_PLAYER){
                                        player[j]=sd;j++;
                                        printf("we have %d player\n",j);
                                    }
                                    break;
                                    //khi co 2 player chon enter_room thi se gui cau hoi cho 2 thang day
                    case SUB_ANSWER: check_main_p(&p[i],ch);
                                    k++;
                                    if(p[i].flag==WRONG_ANSWER){
                                        j--;
                                        if(j==0) a=0;
                                    }
                                    if(k==MAX_PLAYER){k=0;check=0;}
                                    break;
                    case ANSWER: 
                                        if(check_dapan(main_ch,p[i].answer)){
                                        if(p[i].count==MAX_QUES){
                                          p[i].flag=WIN;
                                          j=0;a=0;
                                          p[i].count=1;
                                        }else {
                                            p[i].flag=QUES;
                                            p[i].count++;
                                        }
                   
                                    }           
                                 else {p[i].flag=WRONG_ANSWER;p[i].count=1;a=0;j=0;}

                                 break;
                    

                                    
                    }
                    if(p[i].flag==QUES){
                        srand(time(NULL));
                        int vitri=rand()%9;
                        main_ch=lay_cauhoi(p[i].count,vitri);
                        ch_to_pro(&p[i],main_ch[0]);
                    }
                    if((j==MAX_PLAYER)&&(a==0)){
                            srand(time(NULL));
                            ch=lay_cauhoi(1,rand()%9);
                            play_phu(ch);
                            a=1;
                    }else{
                         if(p[i].flag!=ENTER_ROOM) send(sd,&p[i],sizeof(protocol),0);
                    }
                   
                }
                
            }
        }
    }
}
