#include "ccitt16.h"
#include "introduceerror.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

/* The primary client/sender function
 * sockfd - the bound TCP socket (already set up) to communicate
 * 					with the secondary
 * ber 	  - bit error rate which must be passed to IntroduceError */
void primary(int sockfd, double ber) {



    int read_size=3;
    int window =3; // Go-Back-N ARQ protocol with a send window of size N = 3

    int buffer_window=0; // our send window 
    int send_meg_size =26; // size of the message in  number of char
    char send_msg[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // our message 
    int number_of_packets = send_meg_size /2; // number of packet needed to spend the send_msg
    packet_t packetArray[number_of_packets]; // send_msg to packects
    char srv_reply[150]; // recive size 

    int tem_number_of_reply=0;  // when reciving this size of the arrqy of the number of packets recived at that movement
    int tem_send_window=0;  //used to hold the buffer_window value before being updtae in reciving ack and nack

    packet_t tem_packet_with_errors;// get the packects that's going ot be send and will put errors in it


    char temPacketdata[2]; // place holder to create ther data for ecah packet 
    for (int i =0; i < number_of_packets;i++){
        temPacketdata[0] = send_msg[0+i*2];// making the data
        temPacketdata[1] = send_msg[1+i*2]; // by taking the two elelment 
       // printf("%i %c%c \n",i,send_msg[0+i*2],send_msg[1+i*2]); 

        build_packet(&packetArray[i],PKT_TYPE_DATA,temPacketdata,i); // creating packet 
        //print_packet(&packetArray[i]); 

    }
    
    printf("---------Beginning subroutine---------\n");

    while (buffer_window < number_of_packets ){ // does 

        printf("\n\nSEND WINDOW := %d \nPROGRESS: %d/%d\n",buffer_window,number_of_packets-buffer_window ,number_of_packets); // start of sending windsize packects

        for(int i =0; i< window;i++){// send the packets in the window 
            if (buffer_window+i< number_of_packets){ // checks if the buffer window isn't over the limt of the array
                tem_packet_with_errors = packetArray[i+buffer_window]; // get the packects that's going ot be send and will put errors in it
                introduce_bit_error((char* ) &(tem_packet_with_errors),sizeof(packetArray[i]),ber); //introduce_bit_error in to the each packet
                if (send(sockfd, &tem_packet_with_errors, sizeof(tem_packet_with_errors), 0) < 0) //sendstyhe packet
                    perror("Send failed");

                printf("Sent packet: ");
                print_packet(&packetArray[buffer_window +i]); // prints the packet send

            }
        }

        tem_send_window =buffer_window; //used to hold the buffer_window value before being updtae in reciving ack and nack
        for(int i =0; i< window;i++){  // recives all the packect sent
            if (tem_send_window+i< number_of_packets){  // // checks if the buffer window isn't over the limt of the array
                if ((read_size = recv(sockfd, srv_reply, PKT_SIZE, 0)) < 0) { // reciveinng the packect look for the three packects 
                    perror("recv failed");
                } else {
                    printf("%d.Received packet: ",i+1); // prints the start of the recive packects
                    print_packet((packet_t *)&srv_reply); //prints the packet recived
                    tem_number_of_reply = sizeof((packet_t *)&srv_reply)/sizeof((packet_t *)&srv_reply)[0]; // size of the arrqy of the number of packets recived at that movement
                    
                    for (int y =0; y< tem_number_of_reply;y++){ // goes through all the packect recived

                        if( ((packet_t *)srv_reply)[y].type == PKT_TYPE_ACK ){ // checks if it's a ack type apck
                            printf("\tGOT ACK: looking for %d\n",buffer_window+1); // print to indicate it's an ACK
                            if (buffer_window == (((packet_t *)srv_reply)[y].sequence_number)-1 ){ // if its the correct sequence number 
                                buffer_window+=1; // adjectig the window size
                                printf("\tgot %d, update window size to %d \n",(((packet_t *)srv_reply)[y].sequence_number),buffer_window); // print ditails

                            }else{
                                printf("\tgot %d IGNORE\n",(((packet_t *)srv_reply)[y].sequence_number)); // prints if duplicate and some other reaso for not working 

                            }

                        }

                        if( ((packet_t *)srv_reply)[y].type == PKT_TYPE_NAK ){ // checks if it's a Nack 
                            printf("\tGOT NACK: current sendwindow %d go to %d \n",buffer_window,((packet_t *)srv_reply)[y].sequence_number -window); // print to indicate it's an ACK
                            buffer_window = ((packet_t *)srv_reply)[y].sequence_number ; // set the window size to apropiact index to send the NACK
                        }
                    }

                    
                }
            }
        }



    }

}
