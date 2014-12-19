//#include<stdio.h>
//#include<netdb.h>
//#include<sys/types.h>
//#include<sys/socket.h>
//#include<arpa/inet.h>
//#include<string.h>

//#define RESPONSE_RECV_LIMIT 3000
//#define SOURCE_START_IDENTIFIER "<!DOCTYPE"
//#define SOURCE_START_IDENTIFIER2 "<html>" 		//this is the name of the identifier that the
//#define FILENAME "/"		 		// ENTER THE FILENAME HERE
//#define PORT	"80"			 		// default for web-browsers


//char *get_ip(char *host)
//{
//  struct hostent *hent;
//  int iplen = 15; //XXX.XXX.XXX.XXX
//  char *ip = (char *)malloc(iplen+1);
//  memset(ip, 0, iplen+1);
//  if((hent = gethostbyname(host)) == NULL)
//  {
//    herror("Can't get IP");
//    exit(1);
//  }
//  if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL)
//  {
//    perror("Can't resolve host");
//    exit(1);
//  }
//  return ip;
//}


//int recv_line(int sockfd, unsigned char *dest_buffer) {
//#define EOL "\r\n" // End-Of-Line byte sequence
//#define EOL_SIZE 2
//   unsigned char *nptr;
//   unsigned char *ptr;
//   int eol_matched = 0;



//   ptr = dest_buffer;

//   while(recv(sockfd, ptr, 1, 0) == 1) { // read a single byte
////      if(*ptr == EOL[eol_matched]) { // does this byte match terminator
////         eol_matched++;
////         if(eol_matched == EOL_SIZE) { // if all bytes match terminator,
////            *(ptr+1-EOL_SIZE) = '\0'; // terminate the string
////            return strlen(dest_buffer); // return bytes recevied
////         }
////      } else {
////         eol_matched = 0;
////      }
//      ptr++; // increment the pointer to the next byter;
//   }
//   ptr--;
//   *(ptr-2) = '\0';
//   return 0; // didn't find the end of line characters
//}

//int main(int argc , char *argv[])
//{
//    if(argc != 2)
//    {
//        printf("Usage %s : hostname\n",argv[0]);
//        return(0);
//    }

//    char response[RESPONSE_RECV_LIMIT+1];  // + 1 is for null
//    char *source;
//    int sockfd,newfd,err;
//    char ip[INET6_ADDRSTRLEN];
//    struct addrinfo *p,hints,*res;
//    int len,len_s;
//    int yes=1;
//    struct sockaddr_storage their_addr;
//    socklen_t addr_size;
//    void *addr;
//    char *ver;
//    char request[100];

//    printf("IP Address: %s",get_ip(argv[1]));


//    sprintf(request,"GET %s HTTP/1.1\r\nHost: %s\r\n\r\n",FILENAME,get_ip(argv[1]));

//    // print the request we are making

//   // printf("%s\n\n",request);

//    memset(&hints,0,sizeof hints);

//    hints.ai_socktype=SOCK_STREAM;

//    hints.ai_family=AF_UNSPEC;

//    if ((err = getaddrinfo(get_ip(argv[1]),PORT, &hints, &res)) != 0)
//    {
//        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
//        return 1;
//    }

//    for(p=res;p!=NULL;p=p->ai_next)
//    {
//        if( ( sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol) ) == -1)
//        {
//            printf("Socket error !!!\n");
//            return(0);
//        }

//        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
//        {
//            close(sockfd);
//            perror("client: connect");
//            continue;
//        }
//    }

//    if(send(sockfd,request,strlen(request),0) < strlen(request))
//    {
//        perror("Send Error!!\n");
//    }

//    freeaddrinfo(res);

//   unsigned char *nptr;
//   unsigned char *cptr = malloc(sizeof(unsigned char)*50000);
//   nptr = cptr;
//   recv_line(sockfd,cptr);
//   printf("%s",nptr);

//    if( recv(sockfd,response,RESPONSE_RECV_LIMIT,0) == 0 )
//    {
//        perror("Recv : ");
//        return(1);
//    }

//    close(sockfd); // we dont need it any more

////	printf("%s",response); // for debugging purposes

//    source = strstr(response,SOURCE_START_IDENTIFIER);

//    if(source == NULL)
//    {
//        source = strstr(response,SOURCE_START_IDENTIFIER2);
//    }
//    //printf("%s\n",source);
//    return(0);
//}




#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
int create_tcp_socket();
char *get_ip(char *host);
char *build_get_query(char *host, char *page);
void usage();

#define HOST "coding.debuntu.org"
#define PAGE "/"
#define PORT 80
#define USERAGENT "HTMLGET 1.0"

int main(int argc, char **argv)
{
  struct sockaddr_in *remote;
  int sock;
  int tmpres;
  char *ip;
  char *get;
  char buf[BUFSIZ+1];
  char *host;
  char *page;

  if(argc == 1){
    usage();
    exit(2);
  }
  host = argv[1];
  if(argc > 2){
    page = argv[2];
  }else{
    page = PAGE;
  }
  sock = create_tcp_socket();
  ip = get_ip(host);
  fprintf(stderr, "IP is %s\n", ip);
  remote = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in *));
  remote->sin_family = AF_INET;
  tmpres = inet_pton(AF_INET, ip, (void *)(&(remote->sin_addr.s_addr)));
  if( tmpres < 0)
  {
    perror("Can't set remote->sin_addr.s_addr");
    exit(1);
  }else if(tmpres == 0)
  {
    fprintf(stderr, "%s is not a valid IP address\n", ip);
    exit(1);
  }
  remote->sin_port = htons(PORT);

  if(connect(sock, (struct sockaddr *)remote, sizeof(struct sockaddr)) < 0){
    perror("Could not connect");
    exit(1);
  }
  get = build_get_query(host, page);
  fprintf(stderr, "Query is:\n<<START>>\n%s<<END>>\n", get);

  //Send the query to the server
  int sent = 0;
  while(sent < strlen(get))
  {
    tmpres = send(sock, get+sent, strlen(get)-sent, 0);
    if(tmpres == -1){
      perror("Can't send query");
      exit(1);
    }
    sent += tmpres;
  }
  //now it is time to receive the page
  memset(buf, 0, sizeof(buf));
  int htmlstart = 0;
  char * htmlcontent = malloc(sizeof(char)*500000);
  char * nptr = htmlcontent;
  int i=0;
  while(recv(sock,htmlcontent,1,0) > 0){
      htmlcontent++;
  }
  //Skip header.
  //Skip CRLFs
  nptr = strstr(nptr,"\r\n\r\n");
  printf("%s",nptr+4);
//  while((tmpres = recv(sock, buf, BUFSIZ, 0)) > 0){
//    if(htmlstart == 0)
//    {
//      /* Under certain conditions this will not work.
//      * If the \r\n\r\n part is splitted into two messages
//      * it will fail to detect the beginning of HTML content
//      */
//        printf("CALLED!!!\n");
//      htmlcontent = strstr(buf, "\r\n\r\n");
//      if(htmlcontent != NULL){
//        htmlstart = 1;
//        htmlcontent += 4;
//      }
//    }else{
//      htmlcontent = buf;
//    }
//    if(htmlstart){
//      fprintf(stdout, htmlcontent);
//    }

//    memset(buf, 0, tmpres);
//  }
  if(tmpres < 0)
  {
    perror("Error receiving data");
  }

  printf("\nSearching for \"Micropenguin\"\n");

  //Testing.
  //Outputs starting index position of substring.
  unsigned int j;
  int match = 0;
  char *begin = nptr+4;
  char *name = "MicroPenguin";
  for(j=0; j<strlen(begin);j++){
      if(begin[j] == name[match]){
          match++;
      }
      else{
          if(begin[j] == name[0])
              match = 1;
          else
              match = 0;
      }
      if(match == strlen(name)){
          printf("Found at: %d\n",j-strlen(name)+1);
          printf("J: %d\n",j);
          printf("j-strlen: %d\n",strlen(name));
          int i;
          for(i=j-strlen(name)+1;i<=j;i++)
              printf("%c",begin[i]);
          printf("\n");
      }

  }


  char *s;
  s = strcasestr(nptr+4,"MicroPenguin");
  if(s != NULL){
  int pos = s - (nptr+4);
  printf("Position: %d\n",pos);
  }


  free(get);
  free(remote);
  //free(ip);
  close(sock);
  return 0;
}

void usage()
{
  fprintf(stderr, "USAGE: htmlget host [page]\n\
\thost: the website hostname. ex: coding.debuntu.org\n\
\tpage: the page to retrieve. ex: index.html, default: /\n");
}


int create_tcp_socket()
{
  int sock;
  if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
    perror("Can't create TCP socket");
    exit(1);
  }
  return sock;
}


char *get_ip(char *host)
{
//  struct hostent *hent;
//  int iplen = 15; //XXX.XXX.XXX.XXX
//  char *ip = (char *)malloc(iplen+1);
//  memset(ip, 0, iplen+1);
//  if((hent = gethostbyname(host)) == NULL)
//  {
//    herror("Can't get IP");
//    exit(1);
//  }
//  if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL)
//  {
//    perror("Can't resolve host");
//    exit(1);
//  }
//  return ip;

    struct hostent *host_info;
    struct in_addr *address;
    int iplen = 15;
    char *ip;// = (char *)malloc(iplen+1);
    host_info = gethostbyname(host);
    if(host_info == NULL){
        printf("Could not lookup %s\n",host);
    } else{
        address = (struct in_addr*) host_info->h_addr;
        //inet_ntop(AF_INET,(void*)host_info->h_addr_list[0],ip,iplen);
    }
    //memset(ip, 0, iplen+1);
    ip = inet_ntoa(*address);
    //printf("Length: %d\n",strlen(ip));
    //printf("ip: %s\n",inet_ntoa(*address));
    getchar();
    return ip;
}

char *build_get_query(char *host, char *page)
{
  char *query;
  char *getpage = page;
  char *tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";
  if(getpage[0] == '/'){
    getpage = getpage + 1;
    fprintf(stderr,"Removing leading \"/\", converting %s to %s\n", page, getpage);
  }
  if(strlen(getpage) > 1)
  getpage = strcat(getpage,"/");
  // -5 is to consider the %s %s %s in tpl and the ending \0
  query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(USERAGENT)+strlen(tpl)-5);
  sprintf(query, tpl, getpage, host, USERAGENT);
  return query;
}
