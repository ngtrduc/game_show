#include "lib/cauhoi.h"



int sockfd;

int start()
{
	int temp;
	// printf("Hello,%s",p->u.account);
	printf("1.Enter room and Watting for other user to play\n");
	printf("2.Xem lich su\n");
	printf("3.Quit\n");
	scanf("%d",&temp);
	while(getchar()!='\n');
	if(temp == 1) {
		printf("Watting for other user....\n");
		start_game();
	}
}
int start_game()
{
	int count=-1;
	protocol p;
	p.flag=ENTER_ROOM;
	
	while(1){
		send(sockfd,&p,sizeof(protocol),0);
		recv(sockfd,&p,sizeof(protocol),0);
		switch(p.flag){
			case SUB_QUES: 	printf("sub ques\n");
							p.flag = SUB_ANSWER;
							in_cauhoi(p.ch);
							p.answer=get_answer();
							break;
			// case QUES: 	
						/*p.flag = ANSWER;
						in_cauhoi(p.ch);
						p.answer=get_answer();
						count++;break;*/
			case WRONG_ANSWER: printf("Wrong answer !!\n");
								break;
			case MUON: printf("you had answered too late\n");

		}
		if(p.flag==QUES){
			printf("win nhe\n");
			break;
		}
		if(p.flag==FULL){
			printf("full phong roi\n");
			break;
		}
		if((p.flag == WRONG_ANSWER)||(p.flag==MUON)){
			printf("End Game :( :( :(\n");
			break;
			}
		// if(p.flag == WIN){
		// 	printf("CONGRATULATION, YOU ARE THE MILLIONAIRE!!!");
		// }
	}
	//print_score(count);
}