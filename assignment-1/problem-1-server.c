// 1.Write a udp client server program,client writing messages to server program and server
// return back the same toggled msg to client

// 1.Write a udp client server program,client writing messages to server program and server
// return back the same toggled msg to client

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#define PORT 8000
#define MAXLINE 1024

char *toggle(char str[])
{
    char *ret_str = str;
    for (int i = 0; i < strlen(str); i++)
    {
        if (ret_str[i] >= 'A' && ret_str[i] <= 'Z')
            ret_str[i] = ret_str[i] + 32;
        else if (ret_str[i] >= 'a' && ret_str[i] <= 'z')
            ret_str[i] = ret_str[i] - 32;
    }
    return ret_str;
}

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr); // len is value/resuslt

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    char *toggled = toggle(buffer);
    sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    printf("Hello message sent.\n");

    return 0;
}