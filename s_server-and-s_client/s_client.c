
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/ioctl.h>
#include <string.h>
 
#define MAXBUF 1024
#define IP "192.168.220.128"
#define PORT 443
#define KEY_PATH "Client.key"
#define CERT_PATH "Client.pem"
#define CAFILE "Ca.pem"

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


int main(int argc, char **argv){
    int sock_fd, fd;
    struct sockaddr_in dest;
    char buf[MAXBUF+1];
    char send_buf[MAXBUF+1];
    int len;
    SSL_CTX *ctx;
    SSL *ssl;

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    ctx = SSL_CTX_new(TLSv1_2_client_method());  

    //进行加密会话设置
    if (ctx == NULL){
        printf("cts null ]\n");
    }

    if(SSL_CTX_use_certificate_file(ctx, CERT_PATH, SSL_FILETYPE_PEM)<=0){
        printf("use cert failure\n");
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, KEY_PATH, SSL_FILETYPE_PEM) <= 0){
        printf("use key failure\n");
    }

    if(!SSL_CTX_check_private_key(ctx)){
      printf("key is not cert\n");
    }
    
    if(SSL_CTX_load_verify_locations(ctx, CAFILE, NULL)){
        printf("verify done\n");
    }
    
    //创建socket
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("sock_fd error");
    }else{
        printf("socket created\n");
    }
    
    //设定目的地址信息
    dest.sin_family = AF_INET;
    dest.sin_port = htons(PORT);
    dest.sin_addr.s_addr = inet_addr("127.0.0.1");

    //进行连接
    if(connect(sock_fd, (struct sockaddr *) &dest, sizeof(dest))!=0){
        printf("connect failure\n");
        perror("Connect ");
        exit(errno);
    }else{
        printf("connect ok\n");
    }


    //创建ssl加密通信
    ssl = SSL_new(ctx);
    //绑定sock_fd
    if(SSL_set_fd(ssl, sock_fd)==0){
        printf("set_fd failure\n");
    }

    if (SSL_connect(ssl) == -1){
        printf("ssl_connct failure\n");
    }else{
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
        //ShowCerts(ssl);
        int flags = fcntl(sock_fd, F_GETFL, 0);
        fcntl(sock_fd, F_SETFL, flags|O_NONBLOCK);
    }

int i = 0;
while(1){ 

    bzero(send_buf, MAXBUF+1);
    bzero(buf, MAXBUF+1);   
    len = 0;
    
    //判断是否有有键盘输入
    i = GetInput(send_buf, sizeof(send_buf)); 

    if(i==1){
            //printf("1\n");
            //写入
            len = SSL_write(ssl, send_buf, strlen(send_buf));
            if(len<=0){
                printf("write failure\n");
                break;
            }
            
        }else{
            //读出
            len = SSL_read(ssl, buf, MAXBUF);
            if(len > 0){
                if(strlen(buf)!=0){
                    printf("%s",buf);
                }
            }else if(len==0){
                printf("read failure\n");
                break;
            }
        } 
}
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sock_fd);
    SSL_CTX_free(ctx);
    return 1;
}
