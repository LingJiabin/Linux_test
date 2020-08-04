#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

int GetInput(char *send_buf, int len){

    fd_set rfds;
    struct  timeval tv;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    if(select(1, &rfds, NULL, NULL, &tv) > 0){
        fgets(send_buf, len, stdin);
        return 1;
    }
    
    return 0;
}

int main(){
    printf("begin input \n");
    char send_buf[1024];
 
    int i = 0;
    while(1){
        i = GetInput(send_buf, sizeof(send_buf));

        if(i == 1){
            printf("**%s\n", send_buf);
        }else{
            continue;
            //printf("null\n");
        }
        bzero(send_buf, sizeof(send_buf));
    }

    return 0;
}