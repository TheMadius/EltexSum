/* Пример простого TCP-сервера для сервиса echo */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

void main()
{
    int sockfd, newsockfd;                /* Дескрипторы для слушающего и присоединенного сокетов */
    int clilen;                           /* Длина адреса клиента */
    int n;                                /* Количество принятых символов */
    char line[1000];                      /* Буфер для приема информации */
    struct sockaddr_in servaddr, cliaddr; /* Структуры для размещения полных адресов сервера и клиента */

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror(NULL);
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, 5) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    while (1)
    {
        pid_t p;
        clilen = sizeof(cliaddr);

        if ((newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen)) < 0)
        {
            perror(NULL);
            close(sockfd);
            exit(1);
        }

        switch (p = fork())
        {
        case -1:
        {
            perror(NULL);
            close(newsockfd);
            break;
        }
        case 0:
        {
            char line[1000]; /* Буфер для приема информации */
            int n;           /* Количество принятых символов */
            int clilen = newsockfd;

            while (true)
            {
                int size;
                if ((n = read(clilen, &size, sizeof(int))) < 0)
                {
                    perror(NULL);
                    goto clear;
                }

                if ((n = read(clilen, line, size)) < 0)
                {
                    perror(NULL);
                    goto clear;
                }

                if ((n = write(clilen, line, strlen(line) + 1)) < 0)
                {
                    perror(NULL);
                    goto clear;
                }
            }
        clear:
            close(clilen);
            exit(1);
        }
        default:
        {
            close(newsockfd);
            break;
        }
        }
    }
}
