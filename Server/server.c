#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main(int argc, char *argv[]){

    int sockfd;
    struct sockaddr_in host_addr;


    //Create socket
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("ERROR creating socket!\n");
        exit(1);
    }

    //Set up sockaddr structure for binding
    int port = 8888;
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = 0;

    //Printing w/e address is assigned.
    printf("%s\n",inet_ntoa(host_addr.sin_addr));

    if(bind(sockfd,(struct sockaddr *) &host_addr,sizeof(struct sockaddr)) == -1)
    {
        perror("ERROR binding socket!\n");
        exit(1);
    }

    int yes = 1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
    {
        perror("ERROR setting socket options\n");
        exit(1);
    }



}
