#include "client_handler.h"
#include "settings_storage.h"
#include <cstdint>
#include <iostream>

ClientHandler::ClientHandler(Socket sock) : sock(sock){}

// вернуть текущее значение и вычислить следующий элемент n-й последовательности
uint64_t ClientHandler::getNext(int n){
    uint64_t step = SettingsStorage::getInstance().getStep(sock.getFD(),n);
    uint64_t current = SettingsStorage::getInstance().getCurrent(sock.getFD(),n);
    uint64_t result = current;
    if (current > (current + step)) // если переполнение - начинаем со стартового значения
        current = SettingsStorage::getInstance().getStart(sock.getFD(),n);
    else 
        current += step;
    SettingsStorage::getInstance().setCurrent(current, sock.getFD(),n);
    return result;
}

//  общаться с клиентом
void ClientHandler::processMessage(){
    int buf_size = 256;
    char input_buf[buf_size];
    int count_input;
    const char error_msg[] = "invalid command\n";

    sock.send("> ");
    while (true) {
    	// читаем ввод
        while( ((count_input = sock.read(input_buf, buf_size - 1)) != -1) 
                    && (count_input < buf_size - 1) ) 
        { 
            if (strstr(input_buf,"seq") == input_buf) {
                if (isspace(input_buf[3])) {
                    sock.send(error_msg);
                    sock.send("> ");
                    continue;
                }
                // заносим полученные параметры в переменные
                int n;
                uint64_t xx,yy;
                
                char s_xx[100], s_yy[100];
                if(sscanf(input_buf + 3,"%d %s %s", &n, s_xx, s_yy) == 3) {
                    if ( (n >= 1 && n <= 3) && checkParams(s_xx, s_yy, xx, yy) )
                        SettingsStorage::getInstance().setParams(sock.getFD(), n-1, xx, yy);
                    else 
                        sock.send(error_msg);
                } 
                else 
                    sock.send(error_msg);
            } 
            else if (strstr(input_buf,"export seq") == input_buf){
                // последовательность бесконечная, выход из метода только при разрыве соединения
                exportSeq();
            }
            else 
                sock.send(error_msg);
            memset(input_buf, 0, buf_size);
            sock.send("> "); 
        }  
    }
    return;
}

bool ClientHandler::checkParams(char* x, char* y, uint64_t &start, uint64_t &step) {
    if(x[0] == '-' || y[0] == '-') 
        return false;
    try {
        start = std::stoull(x);
        step = std::stoull(y);
        if (start == 0 || step == 0)
            return false;
    }
    catch(...){
        return false;
    }
    return true;
}

void ClientHandler::exportSeq() {
    bool is_ready = false;           
    for (int i = 0; i < 3; i++) {
        if ( SettingsStorage::getInstance().isDefined(sock.getFD(),i) )
           is_ready = is_ready || true;    
    }
    if (!is_ready) 
        return;
    while(true) {
        std::string str;
        for(int i = 0; i < 3; i++){
            if (SettingsStorage::getInstance().isDefined(sock.getFD(),i)){
                str += std::to_string(getNext(i));
                str += " ";
            }
        }
        str += "\n";
        if (sock.send(str.c_str()) == -1) {
            SettingsStorage::getInstance().erase(sock.getFD());
            sock.close();
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
