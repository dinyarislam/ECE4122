/*
Author: Dinyar Islam
Class: ECE4122

Description: Final Project

What is the purpose of this file?
Application that uses SFML to create a simple pacman game.
*/

#include <sstream>
#include <SFML/Graphics.hpp>
#include "iostream"
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

int main()
{
    // Create a video mode object
    VideoMode vm(645, 730);

    // Create and open a window for the game
    RenderWindow window(vm, "Chess");
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}