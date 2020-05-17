#pragma once

#include <iostream>

#include "MyException.hpp"
#include "Client.hpp"
#include "Server.hpp"

class BaseMode
{
public:
    virtual void run() = 0;
};

class ServerMode : public BaseMode
{
public:
    void run();
};

class ClientMode : public BaseMode
{
public:
    void run();
};

class Input
{
private:
    int port;
    bool mode; // 1 - Server, 0 - Client
public:
    int getPort();

    bool operator==(int x);

    friend std::istream &operator>>(std::istream &in, Input &input);

    friend std::ostream &operator<<(std::ostream &out, const Input &input);
};
