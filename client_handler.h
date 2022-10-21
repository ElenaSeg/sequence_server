#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include "socket.h"

class ClientHandler {
private:
    Socket sock;
   
    // проверить корректность полученных данных
    bool checkParams(char *x, char *y, uint64_t &start, uint64_t &step);
    // получить следующий элемент n-й последовательности
    uint64_t getNext(int n);
    // true если n-я последовательность задана

public:
    ClientHandler(Socket sock);

    // общаться с клиентом
    void processMessage();
    // распечатать результат
    void exportSeq();

};

#endif // CLIENTHANDLER_H
