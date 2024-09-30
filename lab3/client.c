#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


#define buffersize 4096
#define SEVER_PORT 8080


int main(int argc, char **argv){


    int sever_scoket;

    struct  sockaddr_in addr ;

    

    sever_scoket = socket(PF_INET,SOCK_DGRAM,0);
    sendto();
}