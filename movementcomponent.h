#pragma once

#include <iostream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class MovementComponent
{

public:
    MovementComponent(sf::Sprite& sprite, float maxVelocity);
    virtual ~MovementComponent();

    //Accessors
    const sf::Vector2f& getVelocity() const;

    //Functions
    void move(const float dir_x, const float dir_y, const float& delta_time);
    void update(const float& delta_time);

private:
    sf::Sprite& sprite;

    float maxVelocity;

    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f deceleration;

    //Initializer functions



};

