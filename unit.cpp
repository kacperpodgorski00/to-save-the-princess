#include "unit.h"

Unit::Unit()
{
    this->initVariables();
}

Unit::~Unit()
{

}

//Component functions
void Unit::setTexture(sf::Texture& texture)
{
    this->texture = &texture;
    this->sprite.setTexture(texture);
}

void Unit::createMovementComponent(const float maxVelocity)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity);
}

//Functions
void Unit::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Unit::move(const float& delta_time, const float dir_x, const float dir_y)
{
    if(this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, delta_time); //Sets velocity
    }
}

void Unit::update(const float &delta_time)
{

}

void Unit::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}

void Unit::initVariables()
{
    this->texture = nullptr;

    this->movementComponent = nullptr;
}
