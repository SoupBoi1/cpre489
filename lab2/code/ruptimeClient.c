#include <stdio.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#define buffersize 4096 // size of the buffer sent and read formt eh sever
#define SEVER_PORT 8080 // sever's port 

int main(int argc, char **argv){

    FILE *fp;// to store uptime  file 
    FILE *fip;// tosotre ip addrss file 
    char writebuffer[buffersize]; // the buffer that sends to sever 
    char readbuffer[buffersize]; // the buffer that reads fromt eh sever 


    int clintSocket = socket(PF_INET,SOCK_STREAM,0); // the sckot of the client 
       // printf("serverscoket open: %d\n",clintSocket);


    struct  sockaddr_in addr ; // the addrs of the client 
    addr.sin_family =PF_INET;
    addr.sin_port = htons(SEVER_PORT); // the port 
    addr.sin_addr.s_addr =inet_addr(argv[1]);
    
    ///------------uptime and ip wirte buffer genterated---- //
    // ------ uptime ------------//
    fp = popen("uptime","r" ); // run the comad and 
    if(fp ==NULL){
        perror("uptime commad failed to read");
        exit(1);
    }
    char writebuffer_tem[buffersize]; 
    fgets(writebuffer_tem,buffersize, fp);   // puts tiem uptime output to this value
    writebuffer_tem[strlen(writebuffer_tem)-1]='\0'; // places a null in the end incase there isn't
    pclose(fp);
    // ------ ip ------------//
    fip = popen("hostname -I","r" );// run the commad to get ipaddres of the this sever
    if(fip ==NULL){
        perror("uptime commad failed to read");
        exit(1);
    }
    char writebuffer_IP[buffersize]; // the ip address of the computer here 
    fscanf(fip,"%s",writebuffer_IP);// gets first word of the ip addrss commad hostname -I"'s output
    writebuffer_IP[strlen(writebuffer_IP)]='\0';// put null in the end of the string 
    pclose(fip);
    sprintf(writebuffer,"%s: %s", writebuffer_IP ,writebuffer_tem); // places the ip  adn the uptime i write buffer 
    ///------------uptime and ip wirte buffer genterated end;---- ///

    int connect_r = connect(clintSocket,(struct sockaddr*)&addr,sizeof(addr));// connects to sever
   // printf("connect_r: %d\n",connect_r);

    int write_r = write(clintSocket,writebuffer,buffersize); // sneds the writebuffer to the sever 

   // printf("write_r: %d \nsending: %s\n",write_r,writebuffer);

    
    int read_r= read(clintSocket,&readbuffer,buffersize ); //sends the stuff it got back from the sever
    printf("%s\n",&readbuffer); // prints the uptime of the sever sented
    int close_r = close(clintSocket); // closes the client 
   // printf("close_r: %d\n",close_r);



 //  // printf("%d \n%d \n%d \n%d \n%d \n",clintSocket,connect_r,write_r,read_r,close_r);
    return 0;
}

