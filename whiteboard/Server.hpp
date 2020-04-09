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

class Server
{
private:
    static const int Port = 1438;
    sockaddr_in address;
    int server_fd;
    static bool dataToBeSend;
    static std::string s;
    static std::vector<int> poolClients;
    static sf::Texture currentTexture;

public:
    Server();

    static void server_speaks(sf::Vertex, int);

    static void connection_thread(int);

    void connection();
};