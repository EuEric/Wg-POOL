#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My whiteboard menu");
    window.setFramerateLimit(30);

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::RectangleShape portInputBg(sf::Vector2f(600, 125));
    portInputBg.setPosition(sf::Vector2f(100, 100));
    sf::Text port("Port: 3000", font);
    port.setFillColor(sf::Color::Black);
    port.setCharacterSize(30);
    port.setPosition(sf::Vector2f(150, 150));

    sf::RectangleShape serverBtn(sf::Vector2f(600, 125));
    serverBtn.setPosition(sf::Vector2f(100, 250));
    sf::Text serverTxt("Server", font);
    serverTxt.setFillColor(sf::Color::Black);
    serverTxt.setCharacterSize(30);
    serverTxt.setPosition(sf::Vector2f(150, 300));

    sf::RectangleShape clientBtn(sf::Vector2f(600, 125));
    clientBtn.setPosition(sf::Vector2f(100, 400));
    sf::Text clientTxt("Client", font);
    clientTxt.setFillColor(sf::Color::Black);
    clientTxt.setCharacterSize(30);
    clientTxt.setPosition(sf::Vector2f(150, 450));

    bool mousedown = false;
    std::string s = "3000";
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!mousedown && serverBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    std::cout << "server" << '\n';
                    mousedown = true;
                }

                if (!mousedown && clientBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    std::cout << "client" << '\n';
                    mousedown = true;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                mousedown = false;
            }

            if (event.type == sf::Event::TextEntered)
            {
                // Eroare: pe mac backspace e pe ;
                if (event.key.code == sf::Keyboard::BackSpace && s.size() != 0)
                {
                    s.pop_back();
                    port.setString("Port: " + s);
                }
                else if (event.text.unicode < 128 && s.size() < 8)
                {
                    if ('0' <= (char)event.text.unicode && (char)event.text.unicode <= '9')
                        s.push_back((char)event.text.unicode);
                    port.setString("Port: " + s);
                }
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        window.draw(portInputBg);
        window.draw(port);
        window.draw(serverBtn);
        window.draw(serverTxt);
        window.draw(clientBtn);
        window.draw(clientTxt);

        window.display();
    }

    return 0;
}