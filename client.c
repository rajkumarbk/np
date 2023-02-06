//Daytimetcpclient
#include<time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#define MAXLINE 1024
#define LISTENQ 10
typedef struct sockaddr SA;

int main(int argc, char **argv)
{
	int sockfd,n;
	char text[200];
	char rbuff[MAXLINE];
	char sbuff[MAXLINE];
	char recvline[MAXLINE +1];
	struct sockaddr_in servaddr;
	int port;

	if (argc !=3)
		printf("usuage:a.out <IPaddress> <port>");
	if( ( sockfd = socket(AF_INET, SOCK_STREAM,0)) <0)
		printf("socket error");
	port= atoi(argv[2]);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port =htons(port); /*daytime server*/
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <=0)
		printf("inet_pton error for %s", argv[1]);
	if(connect(sockfd, (SA*) &servaddr, sizeof(servaddr)) <0)
		printf("connect error");
	while(1){
	
		bzero(sbuff,MAXLINE);
		printf("Client: ");
		fgets(sbuff,MAXLINE,stdin); 
		if(strncmp(sbuff,"bye",3)==0)
			exit(0);
		write(sockfd,sbuff,strlen(sbuff));		
		
		bzero(rbuff,MAXLINE);
		n=read(sockfd, rbuff, MAXLINE);
		rbuff[n]=0;	
		//read(sockfd,rbuff,strlen(rbuff));
		printf("Server: ");		
		puts(rbuff);
			
	}
}
