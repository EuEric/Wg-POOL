#pragma once

#include <iostream>
#include "Client.hpp"
#include "Server.hpp"

class BaseMode
{
public:
    BaseMode()
    {
    }
    virtual void run() = 0;
};

class ServerMode : public BaseMode
{
public:
    ServerMode()
    {
    }
    void run()
    {
        Server test;
        test.connection();
    }
};

class ClientMode : public BaseMode
{
public:
    ClientMode()
    {
    }
    void run()
    {
        Client test;
        test.run();
    }
};