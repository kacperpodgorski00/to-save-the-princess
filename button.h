#pragma once

#include<iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum button_states{IDLE = 0, HOVER, ACTIVE};

class Button
{

public:
    Button(float x, float y, float width, float height,
           sf::Font* font, std::string text,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();

    //Accessors
    const bool isPressed() const;

    //Functions
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

private:
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    short unsigned buttonState;

};


