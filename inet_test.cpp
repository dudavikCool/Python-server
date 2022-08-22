#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>


using namespace std;

#define SERVER_PORT 4001
#define CLIENT_PORT 4030
#define ADDRLEN 16

int main()
{
    sockaddr_in addr;
    char ipv4[ADDRLEN];
    inet_pton(AF_INET, "192.168.0.2", &addr.sin_addr);
    cout << addr.sin_addr.s_addr << endl;
    inet_ntop(AF_INET, &addr.sin_addr, ipv4, ADDRLEN);
    cout << ipv4;
}