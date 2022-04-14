// IS_SET will check that particulat FD is set or not

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>
#include<fcntl.h>

int main(){
    int fd1, fd2;
    fd_set read_set, write_set, except_set;
    char buf[10];

    struct timeval timeout;

    int n;
    timeout.tv_sec = 90;

    fd1 = open("./write", O_RDWR);
    fd2 = open("./read", O_RDWR);

    FD_ZERO(&read_set);
    // FD_ZERO(&write_set);
    // FD_ZERO(&except_set);

    FD_SET(fd1, &read_set);
    FD_SET(fd2, &read_set);

    n = select(FD_SETSIZE, &read_set, NULL, NULL, &timeout);
    if(n<0){
        perror("select");
        exit(1);
    }
    printf("no of descriptor ready = %d\n", n);

    // test wether fd1 is ready or not
    if(FD_ISSET(fd1, &read_set)){
        printf("reading from fd1(write)\n");
        n = read(fd1, buf, 10);
        printf("read %d from write\n", n);
    }
    // test wether fd2 is ready or not
    if(FD_ISSET(fd2, &read_set)){
        printf("reading from fd2(read)\n");
        n = read(fd2, buf, 10);
        printf("read %d from read\n", n);
    }

    return 0;
}