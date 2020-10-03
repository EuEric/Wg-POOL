#include "BaseMode.hpp"

void ServerMode::run()
{
    Server::Instance()->connection();
    Server::ResetInstance();
}

void ClientMode::run()
{
    Client client;
    ++client;
}

int Input::getPort()
{
    return port;
}

bool Input::operator==(int x)
{
    if (mode == true && x > 0)
    {
        return true;
    }
    return false;
}

std::istream &operator>>(std::istream &in, Input &input)
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
                throw MyException();
            }
        }
        catch (MyException &e)
        {
            error = true;
            std::cout << e.what() << '\n';
        }
        catch (std::exception &e)
        {
            error = true;
            std::cout << e.what() << '\n';
        }
    } while (error == true);

    return in;
}

std::ostream &operator<<(std::ostream &out, const Input &input)
{
    out << input.port;
    return out;
}