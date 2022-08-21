#include <iostream>
#include <future>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

using namespace std;

#define PORT 4001

int main()
{
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    string hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Конвертирует адрес ipv4 из текста в бинарь
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
        return -1;
    
    client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    send(sock, hello.c_str(), strlen(hello.c_str()), 0);
    cout << "Hello message sent\n";
    valread = recv(sock, buffer, 1024, 0);
    cout << buffer;
    close(client_fd);
    return 0;
}