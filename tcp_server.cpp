#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in socketaddr;
    socketaddr.sin_family = AF_INET;
    socketaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socketaddr.sin_port = htons(10086);

    if (-1 == bind(sockfd, (sockaddr*)& socketaddr, sizeof(socketaddr))){
        perror("bind failed! \n");

        return -1;
    }
    listen(sockfd, 10);

    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    int clientfd = accept(sockfd, (struct sockaddr*)& clientaddr, &len);
    printf("sccept! clientfd : %d\n", clientfd);

    char buf[1024] = {0};
    int count = recv(clientfd, buf, 1024, 0);
    send(clientfd, buf, count, 0);
    printf("socket : %d,  clientfd : %d, count : %d , message : %s  \n", sockfd, clientfd, count, buf);

    return 0;
}