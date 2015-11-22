#include "lib/cauhoi.h"
#include "test.h"


int sockfd;
void delay()
{
	printf(" The game will start in: \n");
	get_answer(2000);
	printf("3...\n");
	get_answer(2000);
	printf("2...\n");
	get_answer(2000);
	printf("1....\n");
	get_answer(1000);
}
int score(int count)
{
	switch(count){
		case 1: return 10;
		case 2: return 20;
		case 3: return 40;
		case 4: return 80;
		case 5: return 100;
		case 6: return 200;
		case 7: return 500;
		case 8: return 800;
		case 9: return 1000;
		case 10: return 2000;
		case 11: return 4000;
		case 12: return 6000;
		case 13: return 8000;
		case 14: return 10000;
		case 15: return 15000;
		default: return 0;


	}
}
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
	int count=0;
	protocol p;
	p.flag=ENTER_ROOM;
	int check=1;
	while(1){
		send(sockfd,&p,sizeof(protocol),0);
		recv(sockfd,&p,sizeof(protocol),0);
		switch(p.flag){
			case SUB_QUES: 	printf("Phan choi cau hoi phu\n");
							p.flag = SUB_ANSWER;
							in_cauhoi(p.ch);
							p.answer=get_answer(TIME_OUT);
							
							break;
			case QUES: 	printf("		Correct!!\n");
						if(check==1){
							delay();
							check=0;
						}
						printf("-Ques %d\n",p.count);
						p.flag = ANSWER;
						in_cauhoi(p.ch);
						p.answer=get_answer(TIME_OUT);
						count=p.count;
						break;
			case WRONG_ANSWER: printf("Wrong answer !!\n");
								break;
			case MUON: printf("you had answered too late\n");

		}
		if(p.flag==WIN){
			printf("CONGRATULATION,YOU ARE THE MILLIONAIRE\n");
			congra();
			break;
		}
		if(p.flag==FULL){
			printf("Full room, please try again later\n\n");
			break;
		}
		if((p.flag == WRONG_ANSWER)||(p.flag==MUON)){
			printf("End Game :( :( :(\n\n");
			break;
			}
		// if(p.flag == WIN){
		// 	printf("CONGRATULATION, YOU ARE THE MILLIONAIRE!!!");
		// }
	}
	printf("\n\nYour score: %d\n\n\n",score(count));
}