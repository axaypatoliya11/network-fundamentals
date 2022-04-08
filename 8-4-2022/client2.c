#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(){
    char buf[200];
    char *ser_ip = "127.0.0.1";
    int n;
    int sockfd_in, ret_val;

    struct sockaddr_in servaddr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000); //TCP port---HTTP
    inet_pton(AF_INET, ser_ip, &servaddr.sin_addr);

    ret_val = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    if(ret_val < 0){
        perror("bind: ");
        exit(2);
    }

    printf("enter the data that you want to send to the server\n");
    gets(buf);
    write(sockfd, buf, strlen(buf));
    n = read(sockfd, buf, 200);
    buf[n] = '\0';
    printf("rec'd %s from server\n", buf);
    close(sockfd);

    return 0;
}