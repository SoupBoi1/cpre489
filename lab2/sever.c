#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>




int main(){

    
    int socket_Result = socket(PF_INET,SOCK_STREAM,0);
    //port 17
   // int port = htops(17);
    //int ip = inet_addr("8.8.8.8");
   // struct  sockaddr sockAddr ={PF_INET,htops(17),inet_addr("8.8.8.8")};
    //int bind_v = bind(socket_Result,&sockAddr,sizeof(sockAddr) );
int bind_v =0;
    // sever
 //   struct sockaddr_in addr = {PF_INET,55,(long)77}; 
//    htons(int port);
//    inet_addr();
 //   inet_addr(char *) 

    printf("%d\n%d\n",&socket_Result,&bind_v);
    return 0;
}

