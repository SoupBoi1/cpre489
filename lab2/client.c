#include <stdio.h>
#include <sys/socket.h>

struct sockaddr_in
{
    int sin_family;
    int sin_port;
    long s_arrd; // todo
};
struct in_addr
{
    unsigned long s_addr; 
};



int main(){

    
    int ok = socket(PF_INET,SOCK_STREAM,0);

        // clinet
   // struct sockaddr_in addr = {PF_INET,55,(long)77}; 
    //htons(int port);
// Set to dummy IP address
 //Set to INADDR_ANY


    printf("%d",&ok);
    return 0;
}

