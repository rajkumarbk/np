#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

#define MAX_CLIENTS 10

struct client {
    int id;
    char name[32];
    char registration_no[32];
    int msg_sent_count;
};

struct client clients[MAX_CLIENTS];

int client_count = 0;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void init_clients() {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].id = -1;
    }
}

void add_client(int id, char *name, char *registration_no) {
    if (client_count >= MAX_CLIENTS) {
        printf("Cannot add more clients, client limit reached\n");
        return;
    }


    clients[client_count].id = id;
    strcpy(clients[client_count].name, name);
    strcpy(clients[client_count].registration_no, registration_no);
    clients[client_count].msg_sent_count = 0;

    client_count++;
}

struct client *get_client(int id) {
    for (int i = 0; i < client_count; i++) {
        if (clients[i].id == id) {
            return &clients[i];
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    init_clients();
    add_client(1, "John Doe", "123456");
    add_client(2, "Jane Smith", "234567");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
}