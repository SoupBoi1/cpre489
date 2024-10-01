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
    int numberofbytes;  // number of bytes revived 
    int numberofbytesSend;  // number of bytes this will send 

    int dropping; 
    int dropcount;
    int dropinput=atoi(argv[5]); // the loss rate value is stored here



    sever_scoket = socket(PF_INET,SOCK_DGRAM,0); // udp comminucation socket

    addr.sin_family =AF_INET;
    addr.sin_port = htons(SEVER_PORT);
    addr.sin_addr.s_addr =INADDR_ANY;


    printf("scr: %s : %s\n", argv[1],argv[2]); // prints out vlc scourse ip address info


    dst_addr.sin_family =AF_INET;
    dst_addr.sin_port = htons(atoi(argv[4])); // dst the port 
    dst_addr.sin_addr.s_addr =inet_addr(argv[3]); // the distitation ip

    printf("dst: %s : %s\n", argv[3],argv[4]); // prints out destination scourse ip address info



    if( bind(sever_scoket,&addr,sizeof(addr)) < 0 ){ //  bind this sever/udpfowarder 
        close(sever_scoket);
        printf("bind: %d\n",-1);
    }else{
       printf("bind: %d\n",0);
    }

numberofpackets = 0; // the number of packets 
dropcount=0; // amount of packets droped
int tem_checker =0; // used for if statements weather to drop or send
if(dropinput >0){ // if lassrate =0 it will chose to drop -1 it no droping else it will pick the number

    dropping = (rand()%(1000/dropinput)) ; // it sotres a random number from 0 to 1000/lossrate. for exaple lost rate if 10 then it will store a random number bewtten 0 to 100 this will be used to determind which packet to drop
}else{
    dropping=-1;
}

/**
 * *********IMPORTED NOTES***************
 * I will reffer 0 to 1000/lossrate  as "range of loss"
 */
    while(1){

        numberofbytes=0;
        numberofbytes = recvfrom(sever_scoket,readbuffer,buffersize-1,0,(struct sockaddr*)&src_addr,&src_addr_len);// recives the packet 

        printf("got number of bytes: %d\n", numberofbytes);
        

        if(numberofbytes== -1 ){ // breaks while loop if reciving is not working well 
            break;
        }else{
            printf("numberofpackets: %d\n", (numberofpackets)); // prints the total number of packts recived 
                        numberofpackets++; // count the number of packet recivied 

        }
        if(dropinput >0){ //  if the loss rate is 0 then temcheck thethat detersmines weather to drop is set to a value that make the just sents 
            printf("dropdays----\n");
           tem_checker = (numberofpackets%(1000/dropinput));
            // (1000/dropinput) is the maxium of the "range of loss "and moding numberofpackets with it  he maxium of the "range of loss" limts the range of numberofpackets to 0 to (1000/dropinput) 
            if((numberofpackets%(1000/dropinput))==0){ // therefore this is basicly saying if numberofpackets%(1000/dropinput) go through all of the value from 0 to (1000/dropinput) and goes back to 0 agian the dropping restes  
                dropping = (rand()%(1000/dropinput)) ; // rests the value pick to drop 
            }
        }else{
            printf("lossess----\n");

            tem_checker = 0;// 0!=-1 hech it will sents 
            dropping = -1;
        }


        printf("dropping: %d \ntotaldorop: %d\n\n", dropping ,dropcount); // next drop packt number and count of drops 


        if(dropping!=tem_checker ){ // if dropping the packect number pick to drop is not equal to   numberofpackets in the rage of "rage of loss" then it will send the packet to destination address
            
            numberofbytesSend = sendto(sever_scoket,readbuffer, numberofbytes ,0, (struct sockaddr*)&dst_addr, sizeof(dst_addr)); // sends to destination adrress 

            printf("senting: %d bytes\n\n", numberofbytesSend); // prin tto comform it sneded 

            if( numberofbytesSend < 0){
                break;
            }
        }else{ // it the dropps matches then it doesn't send 
            
            dropcount++; // cout of sroup goes up by one 
        }
        
    }

   
    close(sever_scoket);

    return 0;
}