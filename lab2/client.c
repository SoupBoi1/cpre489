#include <stdio.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#define buffersize 4096
#define SEVER_PORT 8080

int main(int argc, char **argv){

    FILE *fp;
    FILE *fip;
    char filebuffer[128];
    char writebuffer[buffersize]; 
    char readbuffer[buffersize];


    int clintSocket = socket(PF_INET,SOCK_STREAM,0);
        printf("serverscoket open: %d\n",clintSocket);


    struct  sockaddr_in addr ;
    addr.sin_family =PF_INET;
    addr.sin_port = htons(SEVER_PORT);
    addr.sin_addr.s_addr =inet_addr(argv[1]);
    
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
   // fgets(writebuffer_IP_tem,buffersize, fip);   
    //writebuffer_IP = strtok(writebuffer_IP_tem, " ");
    fscanf(fip,"%s",writebuffer_IP);
    writebuffer_IP[strlen(writebuffer_IP)]='\0';
    pclose(fip);
    sprintf(writebuffer,"%s: %s", writebuffer_IP ,writebuffer_tem);
    ///------------uptime and ip wirte buffer genterated end;---- ///

    int connect_r = connect(clintSocket,(struct sockaddr*)&addr,sizeof(addr));
    printf("connect_r: %d\n",connect_r);

    int write_r = write(clintSocket,writebuffer,buffersize);

    printf("write_r: %d \nsending: %s\n",write_r,writebuffer);

    
    int read_r= read(clintSocket,&readbuffer,buffersize );

    printf("read_r: %d\ngot from sever: %s\n",read_r,readbuffer);
    int close_r = close(clintSocket);
    printf("close_r: %d\n",close_r);



 //   printf("%d \n%d \n%d \n%d \n%d \n",clintSocket,connect_r,write_r,read_r,close_r);
    return 0;
}

