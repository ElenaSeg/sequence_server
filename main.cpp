#include <signal.h>
#include "socket.h"
#include "client_handler.h"

using namespace std;

int const PORT_NUMBER = 2222;

int main(int argc, char** argv)
{
    int port;
    if (argc >= 2) {
        sscanf(argv[1],"%d",&port);
    }
    else{
        port = PORT_NUMBER;
    }

    signal(SIGPIPE, SIG_IGN);
    int worker_fd;
    struct sockaddr_in worker_addr;
    Socket server_socket = Socket::createServerSocket(port);
    while (true) {
        Socket client_socket = server_socket.accept();
        ClientHandler* handler = new ClientHandler(client_socket);
        std::thread t(&ClientHandler::processMessage, handler);
        t.detach();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
