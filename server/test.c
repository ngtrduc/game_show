#include <stdio.h>
#include "lib/cauhoi.h"
	int client[10]={-1};

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
    //int vitri=rand()%10;
    ch_to_pro(&p,ch[0]);
    in_cauhoi(p.ch);
    free(ch);
}
check_dapan(cauhoi ch,char dap_an)
{
    if (ch.dapan_dung==dap_an) return 1;
    else return 0;
}
int main()
{
	int i;
	// char a;
	// cauhoi *ch;
	// ch=lay_cauhoi(1,0);
	// play_phu(ch);
	// scanf("%c",&a);
	// if(check_dapan(ch[0],a)) printf("dung\n");
	// else printf("sai\n");
	for(i=0;i<10;i++) printf("%d\n",client[i] );
}