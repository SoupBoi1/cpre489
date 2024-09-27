#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


#define buffersize 4096
#define SEVER_PORT 8080


int main(){
    FILE *fp;
    char filebuffer[128];
    char writebuffer[buffersize]; 
    char readbuffer[buffersize];

    int sever_scoket;
    int newscoket;

    struct  sockaddr_in addr ;
    struct  sockaddr_in client_addr ;
    int client_addr_size=sizeof(client_addr);
    char* buffer;
    
    int bind_r;

    sever_scoket = socket(PF_INET,SOCK_STREAM,0);
    printf("serverscoket open: %d\n",sever_scoket);

    addr.sin_family =PF_INET;
    addr.sin_port = htons(SEVER_PORT);
    addr.sin_addr.s_addr =INADDR_ANY;

    if( bind(sever_scoket,&addr,sizeof(addr)) < 0 ){
        closeSever(sever_scoket);
        printf("bind: %d\n",-1);
    }else{
        printf("bind: %d\n",0);
    }


    if(listen(sever_scoket,7)<0){
        closeSever(sever_scoket);
        printf("listen: %d\n",-1);
    }else{
        printf("listen: %d\n",0);
    }

    newscoket = accept(sever_scoket,&client_addr,&client_addr_size);
    if(newscoket<0){
        closeSever(sever_scoket);
        printf("accept: %d\n",-1);
    }else{
        printf("accept: %d\n",0);
    }

    if(read(newscoket,&buffer,buffersize )<0){
        closeSever(sever_scoket);
        printf("read: %d\n",-1);
    }else{
        printf("read: %d\n",0);
    }
    printf("readed: %s\n",&buffer);

// ----- uptime string -----
    fp = popen("uptime","r" );
    if(fp ==NULL){
        perror("uptime commad failed to read");
        exit(1);
    }
    fgets(writebuffer,buffersize, fp);
   
    writebuffer[strlen(writebuffer)-1]='\0';
    pclose(fp);


    if(write(newscoket,writebuffer,buffersize)<0){
        closeSever(sever_scoket);
        printf("write_r: %d\n",-1);
    }else{
        printf("write_r: %d\n",0);
    }
    printf("write_r: %d sending: %s\n",buffersize,writebuffer);



    closeSever(sever_scoket);
    return 0;
}

int closeSever(int sever_scoket){
    int close_r = close(sever_scoket);
    printf("close_r: %d\n",close_r);
}
