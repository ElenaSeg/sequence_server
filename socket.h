#ifndef SOCKET_H
#define SOCKET_H

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <stdexcept>
#include <chrono>
#include <errno.h>

class Socket
{
private:
    int fd;
public:
    Socket(int fd);

    static Socket createServerSocket(int port_no);
    Socket accept();
    int read(char *buf, int len);
    int send(const char *buf);
    int getFD();
    void close();
};

#endif // SOCKET_H
