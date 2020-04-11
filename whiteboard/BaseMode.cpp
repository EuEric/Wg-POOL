#pragma once

#include <iostream>
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
    void run()
    {
        Server::Instance()->connection();
    }
};

class ClientMode : public BaseMode
{
public:
    void run()
    {
        Client test;
        ++test;
    }
};

class Input
{
private:
    int port;
    bool mode; // 1 - Server, 0 - Client
public:
    int getPort()
    {
        return port;
    }

    bool operator==(int x)
    {
        if (mode == true && x > 0)
        {
            return true;
        }
        return false;
    }

    friend std::istream &operator>>(std::istream &in, Input &input)
    {
        bool error = false;
        do
        {
            error = false;
            try
            {
                std::cout << "Port: ";
                std::string inputPort;
                in >> inputPort;
                input.port = std::stoi(inputPort);

                std::cout << "server / client: ";
                std::string inputMode;
                in >> inputMode;
                if (inputMode == "server")
                {
                    input.mode = 1;
                }
                else if (inputMode == "client")
                {
                    input.mode = 0;
                }
                else
                {
                    throw static_cast<std::string_view>("Invalid mode.");
                }
            }
            catch (std::string_view err)
            {
                error = true;
                std::cout << err << '\n';
            }
            catch (std::invalid_argument const &e)
            {
                error = true;
                std::cout << "Bad input: std::invalid_argument thrown" << '\n';
            }
            catch (std::out_of_range const &e)
            {
                error = true;
                std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
            }
        } while (error == true);

        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const Input &input)
    {
        out << input.port;
        return out;
    }
};