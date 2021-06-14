#pragma once

#include "movementcomponent.h"

class Unit
{

public:
    Unit();
    virtual ~Unit();

    //Component functions
    void setTexture(sf::Texture& texture);
    void createMovementComponent(const float maxVelocity);

    //Functions
    virtual void setPosition(const float x, const float y);
    virtual void move(const float& delta_time, const float x, const float y);

    virtual void update(const float& delta_time);
    virtual void render(sf::RenderTarget* target);

protected:
    sf::Texture* texture;
    sf::Sprite sprite;

    MovementComponent* movementComponent;

private:
    void initVariables();
};


