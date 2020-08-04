#include <openssl/ssl.h>
#include <openssl/err.h>


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <pthread.h>

#define IP "localhost"
#define PORT 2020
#define CERT_PATH "Server.pem"
#define KEY_PATH "Server.key"
#define CAFILE "Ca.pem"

#define MAXBUF 1024

struct my_ctx{
    SSL_CTX *ctx;
    int new_fd;
};

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


//进行加密通信的接口
void* start_routine(void *arg){
    struct my_ctx *recv_ctxfd;

    SSL_CTX *ctx;
    int new_fd;
    recv_ctxfd = (struct my_ctx *)arg;

    ctx = (*recv_ctxfd).ctx;
    new_fd = (*recv_ctxfd).new_fd;

    SSL *ssl;
    ssl = SSL_new(ctx);
    int len = 0;
    char buf[MAXBUF+1];
    char send_buf[MAXBUF+1];
    SSL_set_fd(ssl, new_fd);

    if(SSL_accept(ssl) == -1){
        printf("new_fd error\n");
    }else{
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
        int flags = fcntl(new_fd, F_GETFL, 0);
        fcntl(new_fd, F_SETFL, flags|O_NONBLOCK);
    }

    int i = 0;
    while(1){ 
        //进行读取
        bzero(buf, MAXBUF+1);
        bzero(send_buf, MAXBUF+1);
        i = GetInput(send_buf, sizeof(send_buf));
        if(i==1){
            printf("1\n");

            len = SSL_write(ssl, send_buf, strlen(send_buf));
            if(len<=0){
                printf("write failure\n");
                exit(1);
            }

        }else{
            len = SSL_read(ssl, buf, MAXBUF);
            if(len > 0){
                if(strlen(buf)!=0){
                    printf("got the message from fd: %d\n", new_fd);
                    printf("%s",buf);
                }
            }else if(len==0){
                printf("read failure\n");
                SSL_shutdown(ssl);
                SSL_free(ssl); 
                exit(1);
            }  
        } 
    } 

    SSL_shutdown(ssl);
    SSL_free(ssl); 
}




int main(int argc, char **argv){

    int sock_fd, new_fd, fd;
    socklen_t len;
    struct sockaddr_in my_addr, their_addr;
    unsigned int myport, lisnum;
    char buf[MAXBUF+1];
    char send_buf[MAXBUF+1];
    SSL_CTX *ctx;
    

    //ssl初始化
    SSL_library_init();
    //载入ssl所有算法
    OpenSSL_add_all_algorithms();
    //错误信息提示
    SSL_load_error_strings();
    //创建会话
    ctx = SSL_CTX_new(TLS_server_method());

    //添加密钥和证书
    if(ctx == NULL){
        printf("ctx NULL\n");
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

    SSL_CTX_set_client_CA_list(ctx, SSL_load_client_CA_file(CAFILE));
    
    //建立socket通信
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("sock error\n");
    }else{
        printf("sock is creat\n");
    }

   

    //对server的ip地址端口进行输入
    bzero(&my_addr, sizeof(my_addr));
    myport = PORT;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = myport;
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //进行绑定
    if(bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(my_addr))==-1){
        printf("bind error\n");
    }
    //进入监听状态
   if(listen(sock_fd, SOMAXCONN) == -1){
       printf("listen error\n");
   }

    
    pthread_t thread;

    //socket接受请求,此处accept是阻塞式，要等待客户端连接
    //开始进行线程操作
    struct my_ctx ctx_fd;
    
    while(1){
        
        len = sizeof(struct sockaddr);
        new_fd = accept(sock_fd, (struct sockaddr *) &their_addr, &len);
    
        if(new_fd == -1){
            printf("accept error\n");
        }
        else{
            //接受到连接请求，进行连接
            printf("server: got connection from %s, port %d, socket %d\n", inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port), new_fd);
            
        }

        ctx_fd.ctx = ctx;
        ctx_fd.new_fd = new_fd;
        //开始建立安全的数据传输，多线程操作
        pthread_create(&thread, NULL, start_routine, &ctx_fd);
    }
    
    /* 一对一使用
    //在会话中初始化加密连接
    len = sizeof(struct sockaddr);
    new_fd = accept(sock_fd, (struct sockaddr *) &their_addr, &len);

    if(new_fd == -1){
        printf("accept error\n");
    }
    else{
        //接受到连接请求，进行连接
        printf("server: got connection from %s, port %d, socket %d\n", inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port), new_fd);
        
    }

    SSL *ssl;
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, new_fd);

    if(SSL_accept(ssl) == -1){
        printf("new_fd error\n");
    }else{
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
        int flags = fcntl(new_fd, F_GETFL, 0);
        fcntl(new_fd, F_SETFL, flags|O_NONBLOCK);
    }

    int i = 0;
    while(1){ 
        //进行读取
        bzero(buf, MAXBUF+1);
        bzero(send_buf, MAXBUF+1);
        i = GetInput(send_buf, sizeof(send_buf));
        if(i==1){
            printf("1\n");

            len = SSL_write(ssl, send_buf, strlen(send_buf));
            if(len<=0){
                printf("write failure\n");
                exit(1);
            }

        }else{
            len = SSL_read(ssl, buf, MAXBUF);
            if(len > 0){
                if(strlen(buf)!=0){
                    printf("%s",buf);
                }
            }else if(len==0){
                printf("read failure\n");
                exit(1);
            }  
        } 
    } 

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(new_fd);
    */

    close(sock_fd);
    SSL_CTX_free(ctx);

    return 1;
}
