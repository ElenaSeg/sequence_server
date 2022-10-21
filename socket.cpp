#include "socket.h"

Socket::Socket(int fd): fd(fd) { }

Socket Socket::createServerSocket(int port_no) {
    int listener_fd;
    struct sockaddr_in listener_addr;
    listener_fd = socket(AF_INET, SOCK_STREAM, 0);
    listener_addr.sin_family = AF_INET;
    listener_addr.sin_port = htons(port_no);
    listener_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (  bind(listener_fd, (struct sockaddr*)(&listener_addr), sizeof(listener_addr)) == 0 ){
        ::listen(listener_fd,100);
        return Socket(listener_fd);
    } 
    else {
        fprintf(stderr, "%s\n", strerror(errno));
        throw std::runtime_error("could not bind to socket");
    }
}

Socket Socket::accept(){
    // int client_fd = ::accept(fd,nullptr, nullptr); 
    struct sockaddr_in handler_addr;
    socklen_t len = sizeof(handler_addr);
    int client_fd=::accept(fd,(struct sockaddr*)(&handler_addr), &len);

    if (client_fd != -1) {
        return Socket(client_fd);
    } 
    else {
        fprintf(stderr, "%s\n", strerror(errno));
        throw std::runtime_error("could not create connection to client");
    }
}

int Socket::read(char *buf, int len){
    return ::read(fd, buf, len);
}

int Socket::send(const char *buf){
    return ::send(fd,buf, strlen(buf),0);
}

int Socket::getFD() {
    return fd;
}

void Socket::close(){
    ::close(fd);
}
