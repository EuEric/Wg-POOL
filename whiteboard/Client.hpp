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

#include "ATC.hpp"
#include "Whiteboard.hpp"

class Client
{
private:
    sockaddr_in serv_addr;
    static int sock;
    static std::vector<sf::Vertex> lines;

public:
    Client();

    static void recive_smth();

    static void emit(sf::Vertex);

    void operator++();

    void run();
};