#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "4030"
#define ADDRLEN 16
using namespace std;

void initServerSocket();
void recvMessage(int);
void* getAddr(sockaddr*);

int main() {
    initServerSocket();
}

void* getAddr(sockaddr* addr) {
    
    return &(((sockaddr_in*)addr)->sin_addr.s_addr);
    
}

void initServerSocket() {
    int sockfd;
    addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PORT, &hints, &res);
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    bind(sockfd, res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res);
    recvMessage(sockfd);
}

void recvMessage(int sockfd) {
    sockaddr_storage their_addr;
    socklen_t addr_len;
    char buffer[1024];

    addr_len = sizeof(their_addr);
    int numbytes = recvfrom(sockfd, buffer, 1024, 0, (sockaddr*)&their_addr, &addr_len);

    char s[ADDRLEN];
    cout << "Got packet from \n" << inet_ntop(AF_INET, getAddr((sockaddr*)&their_addr), s, ADDRLEN) << endl;
    cout << ntohs(((sockaddr_in*)((sockaddr *)&their_addr))->sin_port) << endl;
    buffer[numbytes] = '\0';
    cout << buffer;
}

