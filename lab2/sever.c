#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>




int main(){

    
    int sever_scoket = socket(PF_INET,SOCK_STREAM,0);
    printf("serverscoket open: %d\n",sever_scoket);

    struct  sockaddr_in addr ;
    addr.sin_family =PF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr =INADDR_ANY;
    int bind_r = bind(sever_scoket,&addr,sizeof(addr) );
    printf("bind: %d\n",bind_r);
    int listen_r = listen(sever_scoket,7);
    printf("listen: %d\n",listen_r);


    struct  sockaddr_in client_addr ;
    int client_addr_size=0;
    int newscoket = accept(sever_scoket,&client_addr,&client_addr_size);
    printf("accept: %d\n",newscoket);
    char* buffer;
   // buffer = malloc(8); 
    int read_r= read(newscoket,&buffer,8 );
        printf("read: %d, %s\n",read_r,buffer);
  /*  buffer = malloc(8); 
    int write_r = write(newscoket,buffer,sizeof(buffer));
        printf("write_r: %d , %s\n",write_r,buffer);

    int close_r = close(sever_scoket);
        printf("close_r: %d\n",close_r);
*/




    return 0;
}

