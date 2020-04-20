#include "BaseMode.hpp"

void ServerMode::run()
{
    Server::Instance()->connection();
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

std::ostream &operator<<(std::ostream &out, const Input &input)
{
    out << input.port;
    return out;
}