#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(){
    char *ser_ip = "127.0.0.1";
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

    printf("client established connection server\n");

    return 0;
}