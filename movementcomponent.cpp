#include "movementcomponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity,
                                     float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

//Accessors
const float & MovementComponent::getMaxVelocity() const
{
    return this->maxVelocity;
}

const sf::Vector2f & MovementComponent::getVelocity() const
{
    return this->velocity;
}

//Functions
const bool MovementComponent::isIdle() const
{
    if(this->velocity.x == 0.f && this->velocity.y == 0.f)
    {
        return true;
    }
    return false;
}

const bool MovementComponent::moving() const
{
    if(this->velocity.x != 0.f || this->velocity.y != 0.f)
    {
        return true;
    }
    return false;
}

const bool MovementComponent::movingLeft() const
{
    if(this->velocity.x < 0.f)
    {
        return true;
    }
    return false;
}

const bool MovementComponent::movingRight() const
{
    if(this->velocity.x > 0.f)
    {
        return true;
    }
    return false;
}

const bool MovementComponent::movingUp() const
{
    if(this->velocity.y < 0.f)
    {
        return true;
    }
    return false;
}

const bool MovementComponent::movingDown() const
{
    if(this->velocity.y > 0.f)
    {
        return true;
    }
    return false;
}



const bool MovementComponent::isMaxVelocity() const
{
    if(this->velocity.x > 290.f || this->velocity.y > 290.f || this->velocity.x < -290.f || this->velocity.y < -290.f)
    {
        return true;
    }
    return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& delta_time)
{
    /* Accelerating a sprite until reaching the max velocity. */

    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& delta_time)
{
    /* Decelerating the sprite, control the velocity and move the sprite */
    if(this->velocity.x > 0.f) //Positive x
    {
        //Max velocity check
        if(this->velocity.x > this->maxVelocity)
        {
            this->velocity.x = this->maxVelocity;
        }

        //Deceleration
        this->velocity.x -= deceleration;
        if(this->velocity.x < 0.f)
        {
            this->velocity.x = 0.f;
        }
    }
    else if(this->velocity.x < 0.f) //Negative x
    {
        //Max velocity check
        if(this->velocity.x < -this->maxVelocity)
        {
            this->velocity.x = -this->maxVelocity;
        }

        //Deceleration
        this->velocity.x += deceleration;
        if(this->velocity.x > 0.f)
        {
            this->velocity.x = 0.f;
        }
    }

    if(this->velocity.y > 0.f) //Positive y
    {
        //Max velocity check
        if(this->velocity.y > this->maxVelocity)
        {
            this->velocity.y = this->maxVelocity;
        }

        //Deceleration
        this->velocity.y -= deceleration;
        if(this->velocity.y < 0.f)
        {
            this->velocity.y = 0.f;
        }
    }
    else if(this->velocity.y < 0.f) //Negative y
    {
        //Max velocity check
        if(this->velocity.y < -this->maxVelocity)
        {
            this->velocity.y = -this->maxVelocity;
        }

        //Deceleration
        this->velocity.y += deceleration;
        if(this->velocity.y > 0.f)
        {
            this->velocity.y = 0.f;
        }
    }

    //Final move
    this->sprite.move(this->velocity * delta_time); //Uses velocity
}
