#include <SFML/Graphics.hpp>
#include "socket.cpp"

std::vector<int> Server::poolClients = std::vector<int>();
bool Server::dataToBeSend = false;
std::string Server::s = std::string();
sf::Sprite Server::text = sf::Sprite();

int main()
{

    Server test;
    test.connection();

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    std::vector<sf::Vertex> lines;
    sf::Texture texture;
    sf::Sprite sprite;
    texture.create(800, 600);

    int mousedown = 0;
    // run the program as long as the window is open
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if ((event.type == sf::Event::MouseMoved) && (mousedown == 1))
            {
                std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << '\n';
                lines.push_back(sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(window))));
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                mousedown = 1;
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                mousedown = 0;
                texture.update(window);
                lines.clear();
            }
        }

        window.clear(sf::Color::Red);

        window.draw(sprite);

        window.draw(&lines[0], lines.size(), sf::LinesStrip);
        std::cout << sizeof(texture);

        sprite.setTexture(texture);
        window.display();
    }

    return 0;
}