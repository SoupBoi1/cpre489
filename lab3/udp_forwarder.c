/* udp_forwarder.c
 *
 * Author:
 * Description: Forwards UDP packets from a source to a destination.
 *
 * Usage:
 *   Compile the program:
 *     make
 *   Run it:
 *     ./udp-forwarder <SOURCE_IP> <SOURCE_PORT> <DESTINATION_IP> <DESTINATION_PORT> <LOSS_RATE>
 *   Loss rate is the number of packets out of 1000 that are dropped.
 *
 * Tips:
 *   Check the man pages for any functions you're unsure of. Parameters,
 *   return values, and sometimes even examples are listed!
 *
 *   Check for errors, and abstract logically separate blocks into separate
 *   functions!
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define buffersize 4096
#define SEVER_PORT 8080
#define MESSAGE "Hello, server!"
/* main
./udp_forwarder 127.0.0.1 8080 127.0.0.1 1028 0
 * The main entry point of your program */
int main(int argc, char **argv)
{
    // Good luck! Let you TA know if you have any questions.

     int sever_scoket;
     struct  sockaddr_in addr ;
    struct  sockaddr_in src_addr ;
    socklen_t src_addr_len = sizeof(src_addr);
    struct  sockaddr_in dst_addr ;

     char readbuffer[buffersize];
    char writebuffer[buffersize];
    int numberofpackets; 
    int numberofbytes;
    int numberofbytesSend; 
    int dropping = 0; 


    sever_scoket = socket(PF_INET,SOCK_DGRAM,0); // udp comminucation socket

    addr.sin_family =AF_INET;
    addr.sin_port = htons(SEVER_PORT);
    addr.sin_addr.s_addr =INADDR_ANY;


    printf("scr: %s : %s\n", argv[1],argv[2]);


    dst_addr.sin_family =AF_INET;
    dst_addr.sin_port = htons(1028); // dst the port 
    dst_addr.sin_addr.s_addr =inet_addr("127.0.0.1"); // the distitation ip

        printf("dst: %s : %s\n", argv[3],argv[4]);


    if( bind(sever_scoket,&addr,sizeof(addr)) < 0 ){
        close(sever_scoket);
        printf("bind: %d\n",-1);
    }else{
       printf("bind: %d\n",0);
    }

numberofpackets = 0;
    while(1){

        numberofbytes=0;
        numberofbytes = recvfrom(sever_scoket,readbuffer,buffersize-1,0,(struct sockaddr*)&src_addr,&src_addr_len);
        printf("got number of bytes: %d\n", numberofbytes);
        

        if(numberofbytes== -1 ){
            break;
        }else{
            //readbuffer[numberofbytes] ='\0';
            numberofpackets++;
            printf("numberofpackets: %d\n\n\n", numberofpackets);
        }
      //  dropping =(rand()%1000)+1 atoi(argv[5]);


        if(1){
            
            numberofbytesSend = sendto(sever_scoket,readbuffer, numberofbytes ,0, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
            printf("senting: %d bytes\n\n", numberofbytesSend);
            if( numberofbytesSend < 0){
                break;
            }
        }
        
    }

   
    close(sever_scoket);

    return 0;
}