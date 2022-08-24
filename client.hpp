#ifndef CLIENT_HPP
#define CLIENT_HPP
    #include <iostream>
    #include <unistd.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>

    #define PORTSERVER "4030"
    #define ADDRLEN 16
    typedef int socket_fd;

    using namespace std;

    addrinfo* getConnectionAddrinfo(const char*);
    socket_fd initClientSocket(addrinfo* res);
    int sendMessage(int sockfd, const char*);
    void recvMessage(int sockfd);
#endif