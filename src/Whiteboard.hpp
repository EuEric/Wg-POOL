#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

template <int X, int Y>
class Whiteboard
{
public:
    void startClient(std::vector<sf::Vertex> &lines, std::function<void(sf::Vertex)> emit)
    {
        sf::Texture texture;
        sf::Sprite sprite;

        sf::RenderWindow window(sf::VideoMode(X, Y), "My whiteboard");

        texture.create(X, Y);

        int mousedown = 0;
        window.setFramerateLimit(30);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if ((event.type == sf::Event::MouseMoved) && (mousedown == 1))
                {
                    lines.push_back(sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(window))));
                    emit(sf::Vector2f(sf::Mouse::getPosition(window)));
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

                    sf::Vertex foo;
                    foo.color = sf::Color::Blue;
                    emit(foo);
                }
            }

            if (lines.size() > 0 && lines[lines.size() - 1].color == sf::Color::Blue)
            {
                texture.update(window);
                lines.clear();
            }

            window.clear(sf::Color(82, 49, 120));

            window.draw(sprite);

            window.draw(&lines[0], lines.size(), sf::LinesStrip);

            sprite.setTexture(texture);

            window.display();
        }
    }
};
