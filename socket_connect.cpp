#include <iostream>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;


int main() {
    addrinfo hints, *res;
    int sockfd;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo("www.example.net", "http", &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if ((connect(sockfd, res->ai_addr, res->ai_addrlen)) == -1) {
        perror("connect");
        exit(1);
    }
    
}