// by Sudipta Halder
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define buffersize 4096 // the size of the buffer sented and read
#define SEVER_PORT 8080 //  the port 


int main(int argc, char **argv){
    FILE *fp; // the file fp use to caputre Uptime
    FILE *fip; // the file fip to capture this computer's IP address
    char writebuffer[buffersize]; // the buffer sented to client
    char readbuffer[buffersize]; // the buffer to read from client

    int sever_scoket; // this sever's socket
    int newscoket; // the output of accpet() function 

    struct  sockaddr_in addr ; // this sever address 
    struct  sockaddr_in client_addr ; // client's address
    int client_addr_size=sizeof(client_addr); // the size of clients address 
    
    int bind_r;// the out put of bind function 

    sever_scoket = socket(PF_INET,SOCK_STREAM,0);
   // printf("serverscoket open: %d\n",sever_scoket);

    addr.sin_family =PF_INET;
    addr.sin_port = htons(SEVER_PORT);
    addr.sin_addr.s_addr =INADDR_ANY;

    if( bind(sever_scoket,&addr,sizeof(addr)) < 0 ){ // checks if bind is succesful  or else closes 
        closeSever(sever_scoket); // this function closes the sever 
       // printf("bind: %d\n",-1);
    }else{
       // printf("bind: %d\n",0);
    }

 
    if(listen(sever_scoket,7)<0){ // if listen is susseful or the sever closes   
        closeSever(sever_scoket);
       // printf("listen: %d\n",-1);
    }else{
       // printf("listen: %d\n",0);
    }

    newscoket = accept(sever_scoket,&client_addr,&client_addr_size); // checks if appect is succesfull or the sever closes 
    if(newscoket<0){
        closeSever(sever_scoket);
       // printf("accept: %d\n",-1);
    }else{
       // printf("accept: %d\n",0);
    }

    if(read(newscoket,&readbuffer,buffersize )<0){ //  checks it got anything some client else the sever closes 
        closeSever(sever_scoket);
       // printf("read: %d\n",-1);
    }else{
       // printf("read: %d\n",0);
    }
    printf("%s\n",&readbuffer);  // prints the the uptime from client

    ///------------uptime and ip wirte buffer genterated---- //
    // ------ uptime ------------//
    fp = popen("uptime","r" ); // run the commad
    if(fp ==NULL){
        perror("uptime commad failed to read");
        exit(1);
    }
    char writebuffer_tem[buffersize]; 
    fgets(writebuffer_tem,buffersize, fp);   // puts tiem uptime output to this value 
    writebuffer_tem[strlen(writebuffer_tem)-1]='\0'; // places a null in the end incase there isn't
    pclose(fp);
    // ------ ip ------------//
    fip = popen("hostname -I","r" ); // run the commad to get ipaddres of the this sever 
    if(fip ==NULL){ 
        perror("uptime commad failed to read");
        exit(1);
    }
    char writebuffer_IP[buffersize]; // the ip address of the computer here 
    fscanf(fip,"%s",writebuffer_IP); // gets first word of the ip addrss commad hostname -I"'s output
    writebuffer_IP[strlen(writebuffer_IP)]='\0'; // put null in the end of the string 
    pclose(fip);
    sprintf(writebuffer,"%s: %s", writebuffer_IP ,writebuffer_tem); // places the ip  adn the uptime i write buffer 
    ///------------uptime and ip wirte buffer genterated end;---- ///

    if(write(newscoket,writebuffer,buffersize)<0){ // sents writebuffer amd if unsufesfull the sever closes 
        closeSever(sever_scoket);
       // printf("write_r: %d\n",-1);
    }else{
       // printf("write_r: %d\n",0);
    }
   // printf("write_r: %d sending: %s\n",buffersize,writebuffer);



    closeSever(sever_scoket); //  the sever closes 
    return 0;
}

/*
 * @prameter int  sever_scoket the socket of the sever
 this close the sokect of paramenter sever_scoket
 */
int closeSever(int sever_scoket){
    int close_r = close(sever_scoket); // closes the sver 
   // printf("close_r: %d\n",close_r);
}
