#pragma once

#include "hitboxcomponent.h"
#include "movementcomponent.h"
#include "animationcomponent.h"

class Unit
{

public:
    Unit();
    virtual ~Unit();

    //Component functions
    void setTexture(sf::Texture& texture);

    void createHitboxComponent(sf::Sprite& sprite,
         float offset_x, float offset_y,
         float width, float height);

    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture& texture_sheet);

    //Functions
    virtual void setPosition(const float x, const float y);
    virtual void move(const float dir_x, const float dir_y, const float& delta_time);

    virtual void update(const float& delta_time);
    virtual void render(sf::RenderTarget& target);

protected:
    sf::Sprite sprite;

    HitboxComponent* hitboxComponent;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;

private:
    void initVariables();
};


