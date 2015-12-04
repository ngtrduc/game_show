#include "protocol.h"
#include <unistd.h>
#include <poll.h>


#define TIME_OUT 15000
// chuyen noi dung cau hoi vao giao thuc de chuyen di
void ch_to_pro(protocol *p,cauhoi ch)
{
    strcpy(p->ch.cauhoi,ch.cauhoi);
    strcpy(p->ch.dapan1,ch.dapan1);
    strcpy(p->ch.dapan2,ch.dapan2);
    strcpy(p->ch.dapan3,ch.dapan3);
    strcpy(p->ch.dapan4,ch.dapan4);
    p->ch.dapan_dung=ch.dapan_dung;
}
// tao them 1 bo cau hoi moi
struct cauhoi nhap_cauhoi(i)
{
	struct cauhoi ch;
	printf("nhap cau hoi %d: \n",i);
	gets(ch.cauhoi);
	printf("nhap dap an 1:\n");
	gets(ch.dapan1);
	printf("nhap dap an 2:\n");
	gets(ch.dapan2);
	printf("nhap dap an 3:\n");
	gets(ch.dapan3);
	printf("nhap dap an 4:\n");
	gets(ch.dapan4);
	printf("nhap dan an dung:\n");
	ch.dapan_dung=getchar();
	while(getchar()!='\n');
	return ch;
}

void them_cauhoi(){
	int i=1;
	struct cauhoi ch;
	char temp[5];
	FILE *fp;
	char bo_cauhoi[15];
	printf("bo cau hoi ban muon them:\n");
	gets(bo_cauhoi);
	strcat(bo_cauhoi,".dat");
	fp=fopen(bo_cauhoi,"wb");
	do{
		ch=nhap_cauhoi(i);
		fwrite(&ch,sizeof(cauhoi),1,fp);
		printf("tiep tuc khong (y/n)\n");
		gets(temp);
		i++;
	}while(!strcmp(temp,"y"));
	fclose(fp);
}
// lay cau hoi tu file ra
struct cauhoi *lay_cauhoi(int set,int vi_tri)
{
	char bo_cauhoi[32]="bo_cauhoi/bo_cauhoi";
	char b[15];
    sprintf(b, "%d",set );
    strcat(bo_cauhoi,b);
	struct cauhoi *ch;
	FILE *fp;
	strcat(bo_cauhoi,".dat");
	ch=(struct cauhoi*)malloc(sizeof(struct cauhoi));
	fp= fopen(bo_cauhoi,"r+b");
	if(fp==NULL){
		printf("khong ton tai bo cau hoi tren.\n");
		return NULL;
	}
	if(fseek(fp,vi_tri*sizeof(struct cauhoi),SEEK_SET)!=0){
		printf("Fseek failed!!\n");
		return NULL;
	}
	fread(ch,sizeof(cauhoi),1,fp);
	fclose(fp);
	return ch;
}
//in cau hoi
void in_cauhoi(cauhoi ch)
{
	printf("%s\n",ch.cauhoi );
	printf("1.%s\n",ch.dapan1);
	printf("2.%s\n",ch.dapan2);
	printf("3.%s\n",ch.dapan3);
	printf("4.%s\n",ch.dapan4);
}