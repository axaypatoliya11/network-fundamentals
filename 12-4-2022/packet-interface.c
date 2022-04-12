// shows how to use packet interface to capture all the packets at the data link level
// apply sudo because we are working at physical link layer that is below the internet protocol layer. are working in an advance option mode beause we are implementing the protocol modules at a very low level so we have to be a root user for that

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>

int main(){ 
    int pack_socket, n;
    struct sockaddr_ll sa;
    socklen_t sl;
    char buf[2000];
    sl = sizeof(struct sockaddr_ll);

    // sock_row keeps physical layer header, sock_dgram removes it
    pack_socket = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
    if(pack_socket < 0){
        printf("failed to open packet socket\n");
        exit(0);
    }

    printf("packet socket successfully opened\n");
    while(1){
        n = recvfrom(pack_socket, buf, 2000, 0, (struct sockaddr *)&sa, &sl);
        printf("recieved packet of length %d\n", n);
    }
    close(pack_socket);
    return 0;
}