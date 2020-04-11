#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <thread>
#include <string>
#include <cstring>
#include <map>
#include <SFML/Graphics.hpp>
#include <arpa/inet.h>

#include "ATC.cpp"

class Server
{
private:
    sockaddr_in address;
    int server_fd;
    bool dataToBeSend;
    std::string s;
    std::vector<int> poolClients;
    sf::Texture currentTexture;
    static Server *pInstance;
    Server();
    void server_speaks(sf::Vertex, int);
    static void connection_thread(int);

public:
    void connection();
    static Server *Instance();
};