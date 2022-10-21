#ifndef SETTINGSSTORAGE_H
#define SETTINGSSTORAGE_H
#include <cinttypes>
#include <map>


class Settings {
public:
    bool is_defined[3];
    uint64_t start[3];
    uint64_t step[3];   
    uint64_t current[3];

    Settings();
    Settings(const Settings& c);
};

class SettingsStorage
{
   std::map<int, Settings> storage_map;
public:
    void setParams(int client_fd, int seq_num, uint64_t start, uint64_t step);
    void setCurrent(uint64_t current, int client_fd, int seq_num);
    
    uint64_t getStart(int client_fd, int seq_num);
    uint64_t getStep(int client_fd, int seq_num);
    uint64_t getCurrent(int client_fd, int seq_num);

    bool isDefined(int client_fd, int seq_num);
    void erase(int client_fd);
    static SettingsStorage& getInstance();

private:
    // реализуем паттерн "singleton"
    SettingsStorage();
};

#endif // SETTINGSSTORAGE_H
