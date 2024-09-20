#include <stdio.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>





int main(){

    
    int clintSocket = socket(PF_INET,SOCK_STREAM,0);
        printf("serverscoket open: %d\n",clintSocket);


    struct  sockaddr_in addr ;
    addr.sin_family =PF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr =inet_addr("127.0.0.1");
    
    int connect_r = connect(clintSocket,(struct sockaddr*)&addr,sizeof(addr));
            printf("connect_r: %d\n",connect_r);

    char* buffer = "su"; 
    int write_r = write(clintSocket,buffer,8);
    printf("write_r: %d sending: %s\n",write_r,buffer);
   // buffer = malloc(8); 
    int read_r= read(clintSocket,&buffer,8 );
    printf("read_r: %d, got %s\n",read_r,buffer);
    int close_r = close(clintSocket);
    printf("close_r: %d\n",close_r);

 //   printf("%d \n%d \n%d \n%d \n%d \n",clintSocket,connect_r,write_r,read_r,close_r);
    return 0;
}

