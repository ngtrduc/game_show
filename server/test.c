#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include <termios.h>
static struct termios old, new;
void initTermios(int echo) {
    tcgetattr(0, &old);                       
    new = old;                                
    new.c_lflag &= ~ICANON;                   
    new.c_lflag &= echo ? ECHO : ~ECHO;       
    tcsetattr(0, TCSANOW, &new);              
}

void resetTermios(void) {
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo) {
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

char getch(void) {
    return getch_(0);
}

int get_pass(char pass[]){
    int i=0;

    while(1){
        pass[i]=getch();
        if(pass[i]== '\n') break;
        i++;
    }
    pass[i]='\0';
    return 1;
}
int main()
{
    char temp[30];
        printf("nhap pass\n");
        get_pass(temp);
        printf("%s",temp);

}