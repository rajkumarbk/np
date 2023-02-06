//Daytimetcpserver
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
	int listenfd,connfd;
	struct sockaddr_in servaddr, cliaddr;
	char buff[MAXLINE];
	char rbuff[MAXLINE];
	char sbuff[MAXLINE];
	time_t ticks;
	socklen_t len;
	int port;
int n;
	
	listenfd = socket(AF_INET, SOCK_STREAM,0);
	port = atoi(argv[1]);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);/* daytime_server */
	
	bind(listenfd, (SA*) &servaddr, sizeof(servaddr));
	printf("Server is waiting for connection at port 123454\n");
	listen(listenfd, LISTENQ);
	len = sizeof(cliaddr);
		connfd= accept(listenfd, (SA*) &cliaddr, &len);
		printf("Connection from %s, port %d\n",
		inet_ntop(AF_INET, &cliaddr.sin_addr,buff,sizeof(buff)),
		ntohs(cliaddr.sin_port));

	for (; ;) {
		bzero(rbuff,MAXLINE);
		n  = read(connfd, rbuff, MAXLINE);
		rbuff[n]=0;
		
		printf("Client: ");
		puts(rbuff);
		
		bzero(sbuff,MAXLINE);	
		printf("Server: ");
		fgets(sbuff,MAXLINE,stdin);
		if(strncmp(sbuff,"bye",3)==0)
			exit(0);
		write(connfd,sbuff,strlen(sbuff));

		
		
	}
}

