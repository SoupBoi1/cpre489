#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


#define buffersize 4096
#define SEVER_PORT 8080


int main(int argc, char **argv){
    //FILE *fp;
    //FILE *fip;
    //char filebuffer[128];
    //char writebuffer[buffersize]; 
    //char readbuffer[buffersize];

    int sever_scoket;
   // int newscoket;

    struct  sockaddr_in addr ;
   // struct  sockaddr_in client_addr ;
    //int client_addr_size=sizeof(client_addr);
  //  char* buffer;
    

    sever_scoket = socket(PF_INET,SOCK_DGRAM,0); // udp comminucation socket
   // printf("serverscoket open: %d\n",sever_scoket);

    addr.sin_family =PF_INET;
    addr.sin_port = htons(SEVER_PORT);
    addr.sin_addr.s_addr =INADDR_ANY;

    if( bind(sever_scoket,&addr,sizeof(addr)) < 0 ){
        closeSever(sever_scoket);
       // printf("bind: %d\n",-1);
    }else{
       // printf("bind: %d\n",0);
    }


   

    newscoket = accept(sever_scoket,&client_addr,&client_addr_size);
    if(newscoket<0){
        closeSever(sever_scoket);
       // printf("accept: %d\n",-1);
    }else{
       // printf("accept: %d\n",0);
    }

    if(read(newscoket,&readbuffer,buffersize )<0){
        closeSever(sever_scoket);
       // printf("read: %d\n",-1);
    }else{
       // printf("read: %d\n",0);
    }
    printf("%s\n",&readbuffer);

    ///------------uptime and ip wirte buffer genterated---- //
    // ------ uptime ------------//
    fp = popen("uptime","r" );
    if(fp ==NULL){
        perror("uptime commad failed to read");
        exit(1);
    }
    char writebuffer_tem[buffersize]; 
    fgets(writebuffer_tem,buffersize, fp);   
    writebuffer_tem[strlen(writebuffer_tem)-1]='\0';
    pclose(fp);
    // ------ ip ------------//
    fip = popen("hostname -I","r" );
    if(fip ==NULL){
        perror("uptime commad failed to read");
        exit(1);
    }
    char writebuffer_IP[buffersize]; 
    fscanf(fip,"%s",writebuffer_IP);
    writebuffer_IP[strlen(writebuffer_IP)]='\0';
    pclose(fip);
    sprintf(writebuffer,"%s: %s", writebuffer_IP ,writebuffer_tem);
    ///------------uptime and ip wirte buffer genterated end;---- ///

    if(write(newscoket,writebuffer,buffersize)<0){
        closeSever(sever_scoket);
       // printf("write_r: %d\n",-1);
    }else{
       // printf("write_r: %d\n",0);
    }
   // printf("write_r: %d sending: %s\n",buffersize,writebuffer);



    closeSever(sever_scoket);
    return 0;
}

int closeSever(int sever_scoket){
    int close_r = close(sever_scoket);
   // printf("close_r: %d\n",close_r);
}
