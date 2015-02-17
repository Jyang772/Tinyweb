#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
int cmd_line(int a, int b);
void lookup();

struct commands{
    char *command;
    int (*cmd_handler)(int a, int b);
};

struct commands cmds[] = {
{"USER", cmd_line},
{"PINGU", lookup}

};

int cmd_line(int a, int b){
    printf("%d and %d",a,b);
}

void lookup()
{
    struct hostent *host_info;
    struct in_addr *address;

    host_info = gethostbyname("www.micropenguin.net");
    address = (struct in_addr *)(host_info->h_name);
    printf("%s: ",inet_ntoa(*address));
}

void initialize_server(int *sockfd, int port)
{
    struct sockaddr_in host_addr;

    //Create socket
    if((*sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("ERROR creating socket!\n");
        exit(1);
    }

    //Set up struct
    host_addr.sin_addr.s_addr = INADDR_ANY;
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = port;

    //bind socket
    if(bind(*sockfd,(struct sockaddr*) &host_addr,sizeof(struct sockaddr)) == -1)
    {
        perror("Failed to bind socket!\n");
        exit(1);
    }

    //set socket options
    int optVal = 1;
    if(setsockopt(*sockfd,SOL_SOCKET, SO_REUSEADDR,&optVal,sizeof(int)) == -1)
    {
        perror("Failed to set socket options!\n");
        exit(1);
    }

    //listen on socket
    if(listen(*sockfd,5) == -1)
    {
        perror("Failed to listen on socket!\n");
        exit(1);
    }

}

int main(int argc, char *argv[]){

    int sockfd = malloc(sizeof(int));
    int port = 8888;
    initialize_server(&sockfd,port);



    cmds[1].cmd_handler(1,2);

}
