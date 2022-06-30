#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <netdb.h>



void error(const char *msg){

    perror(msg);

    exit(1);

}



int main(int argc, char *argv[])

{

    int sockfd, portno, n;

    struct sockaddr_in serv_addr;

    struct hostent *server;



    char buffer[255];

    if(argc<3){

        fprintf(stderr, "Usage %s Hostname Port\n",argv[0]);

        exit(1);

    }



    portno = atoi(argv[2]);

    sockfd = socket(AF_INET,SOCK_STREAM,0);



    if(sockfd < 0)

        error("Error Opening Socket\n");

    else

        printf("Socket Created Successfully\n");



    server = gethostbyname(argv[1]);

    if(server==NULL){

        fprintf(stderr, "Error!! No Such Host\n");

    }



    printf("Prateek Singh 20103109\n\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);



    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 )

        error("Connection Failed\n");

    else

        printf("Connected To Server\n");



    while(1)

    {

        bzero(buffer,255);

        fgets(buffer,255,stdin);

        n=write(sockfd,buffer,strlen(buffer));

        if(n<0)

            error("Error on writing");



        bzero(buffer,255);

        n=read(sockfd,buffer,255);

        if(n<0)

            error("Error on reading");

        printf("Server: %s\n\n",buffer);

        int i=strncmp("Bye",buffer,3);

        if(i==0)

            break;

    }

    printf("Disconnected From Server\n");

    close(sockfd);

    return 0;

}