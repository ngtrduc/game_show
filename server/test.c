#include <stdio.h>
#include "lib/cauhoi.h"
int check=0;

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

check_dapan(cauhoi *ch,char dap_an)
{
    if (ch->dapan_dung==dap_an) return 1;
    else return 0;
}
void check_main_p(protocol *p, cauhoi *ch)
{
    if(check_dapan(ch,p->answer)){
        if(check==0){
            p->flag=QUES;
            check=1;
        }else p->flag=MUON;

    }else p->flag=WRONG_ANSWER;

}
int main()
{
    protocol p;
    char dap_an;
    cauhoi *ch;
    ch=lay_cauhoi(1,0);
    p.answer='c';
    check_main_p(&p,ch);
    printf("%d",p.flag);
        check_main_p(&p,ch);
    printf("%d",p.flag);
}