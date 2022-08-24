#include <iostream>
#include <future>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

using namespace std;

#define SERVER_PORT 4001
#define CLIENT_PORT 4030

int main()
{
    int sockfd, valread;
    struct sockaddr_in serv_addr, cli_addr;
    string hello = "Hello";
    char buffer[1024] = {0};

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        return -1;

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));

    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(CLIENT_PORT);
    cli_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (sockaddr*)&cli_addr, sizeof(cli_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    unsigned int n, len;
    // MSG_CONFIRM отправляет ответ на датаграмму без ARP
    sendto(sockfd, hello.c_str(), strlen(hello.c_str()), 0, 
        (sockaddr*)&serv_addr, sizeof(serv_addr));
    cout << "Sent";
    len = sizeof(serv_addr);
    n = recvfrom(sockfd, buffer, 1024, 0, (sockaddr*)&serv_addr, (socklen_t*)&len);

    cout << buffer;
    close(sockfd);
}