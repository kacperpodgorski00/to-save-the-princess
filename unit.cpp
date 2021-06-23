#include "unit.h"

Unit::Unit()
{
    this->initVariables();
}

Unit::~Unit()
{
    delete this->hitboxComponent;
    delete this->movementComponent;
    delete this->animationComponent;
}

//Component functions
void Unit::setTexture(sf::Texture& texture)
{
    this->sprite.setTexture(texture);
}

void Unit::createHitboxComponent(sf::Sprite& sprite,
                                 float offset_x, float offset_y,
                                 float width, float height)
{
    this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Unit::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Unit::createAnimationComponent(sf::Texture &texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

//Functions
void Unit::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Unit::move(const float dir_x, const float dir_y, const float& delta_time)
{
    if(this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, delta_time); //Sets velocity
    }
}

void Unit::update(const float &delta_time)
{

}

void Unit::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);

    if(this->hitboxComponent)
    {
        this->hitboxComponent->render(target);
    }
}

void Unit::initVariables()
{
    this->hitboxComponent = nullptr;
    this->movementComponent = nullptr;
    this->animationComponent = nullptr;
}
