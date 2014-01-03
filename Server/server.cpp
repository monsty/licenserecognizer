#include "server.h"
#include <QDebug>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>


Server::Server()
{
}

Server::~Server()
{
}

int Server::listening()
{
    int sockfd;
    int newfd;
    socklen_t size;
    struct sockaddr_in server;
    struct sockaddr_in remote;

    server.sin_family = AF_INET;
    server.sin_port = htons(4243);
    server.sin_addr.s_addr = INADDR_ANY;
    memset(&(server.sin_zero), 0, 8);

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    if(bind(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    if(listen(sockfd, 5) == -1)
    {
        perror("listen");
        exit(1);
    }
    size = sizeof(struct sockaddr_in);

    while(1)
    {
        if((newfd = accept(sockfd, (struct sockaddr *)&remote, &size)) == -1)
        {
            perror("accept");
            exit(1);
        }

        qDebug() << "CLIENT CONNECTION";

        if (!fork())
        {
            //send(newfd, msg, sizeof(msg), 0);
            //close(0);
            close(newfd);
        }
    }

    qDebug() << "TEST OK";
    return 1;
}
