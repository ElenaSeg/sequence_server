#include "settings_storage.h"
#include <iostream>

Settings::Settings(){
    for(int i = 0; i < 3; i++) {
        is_defined[i] = false;
        start[i] = 0;
        step[i] = 0;
        current[i] = 0;
    }
}

SettingsStorage::SettingsStorage(){}

void SettingsStorage::setParams(int client_fd, int seq_num, std::uint64_t start, std::uint64_t step){
    if (storage_map.find(client_fd) == storage_map.end())
        storage_map[client_fd] = Settings();
    storage_map[client_fd].is_defined[seq_num] = true;
    storage_map[client_fd].start[seq_num] = start;
    storage_map[client_fd].current[seq_num] = start;
    storage_map[client_fd].step[seq_num] = step;

}

void SettingsStorage::setCurrent(uint64_t current, int client_fd, int seq_num){
    storage_map[client_fd].current[seq_num] = current;
}

uint64_t SettingsStorage::getStart(int client_fd, int seq_num){
    return storage_map[client_fd].start[seq_num];
}

uint64_t SettingsStorage::getStep(int client_fd, int seq_num){
    return storage_map[client_fd].step[seq_num];
}

uint64_t SettingsStorage::getCurrent(int client_fd, int seq_num){
    return storage_map[client_fd].current[seq_num];
}

bool SettingsStorage::isDefined(int client_fd, int seq_num){
    return storage_map[client_fd].is_defined[seq_num];
}

void SettingsStorage::erase(int client_fd){
    storage_map.erase(client_fd);
}

SettingsStorage& SettingsStorage::getInstance(){
    static SettingsStorage _instance;
    return _instance;
}
