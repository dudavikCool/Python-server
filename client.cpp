


#include "client.hpp"


socket_fd initClientSocket(addrinfo* res) {
    socket_fd sockfd;
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    return sockfd;
}

addrinfo* getConnectionAddrinfo(const char* address) {
    addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM; 
    getaddrinfo(address, PORTSERVER, &hints, &res);

    return res;
}

int sendMessage(int sockfd, addrinfo* res, const char* message) {
    int numbytes;
    numbytes = sendto(sockfd, message, strlen(message), 0, res->ai_addr, res->ai_addrlen);

    return numbytes;
}

int main() {
    addrinfo* connectionAddrinfo = getConnectionAddrinfo("127.0.0.1");
    socket_fd clientfd = initClientSocket(connectionAddrinfo);
    sendMessage(clientfd, connectionAddrinfo, "Message");
    freeaddrinfo(connectionAddrinfo);
    close(clientfd);

    return 0;
}