#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;
int main() {
    int status;
    addrinfo hints;
    addrinfo* servinfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    getaddrinfo(NULL, "3490", &hints, &servinfo);

    int s;
    s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    
    bind(s, servinfo->ai_addr, servinfo->ai_addrlen);
    int yes = 1;
    if((setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1) {
        perror("setsockopt");
        exit(1);
    }
    
    


}
