#include "player.h"

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
    this->initVariables();

    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 12.f, 14.f, 97.f, 105.f);
    this->createMovementComponent(350.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 14, 7, 14, 128, 128);
    this->animationComponent->addAnimation("WALK_RIGHT", 6.f, 0, 0, 8, 0, 128, 128);
    this->animationComponent->addAnimation("WALK_DOWN", 6.f, 6, 5, 11, 5, 128, 128);
    this->animationComponent->addAnimation("WALK_UP", 6.f, 0, 5, 5, 5, 128, 128);
    this->animationComponent->addAnimation("RUN_RIGHT", 4.f, 6, 6, 11, 6, 128, 128);
    this->animationComponent->addAnimation("THROW_BOMB", 7.f, 0, 3, 5, 3, 128, 128);
}

Player::~Player()
{

}

//Functions
void Player::updateThrowingBomb(const float &delta_time)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if((this->sprite.getPosition().x + (1.5 * sprite.getGlobalBounds().width)) > sf::Mouse::getPosition().x)
        {
            this->sprite.setOrigin(124.f, 0.f);
            this->sprite.setScale(-1.f, 1.f);
        }
        else
        {
            this->sprite.setOrigin(0.f, 0.f);
            this->sprite.setScale(1.f, 1.f);
        }
        this->throwingBomb = true;
    }
}

void Player::updateAnimation(const float &delta_time)
{
    if(this->throwingBomb)
    {
        if(this->animationComponent->play("THROW_BOMB", delta_time, true))
        {
            this->throwingBomb = false;
        }
    }

    if(this->movementComponent->isIdle())
    {
        this->animationComponent->play("IDLE_RIGHT", delta_time);
    }

    else if(this->movementComponent->movingRight())
    {
        if(this->movementComponent->isMaxVelocity())
        {
            this->sprite.setOrigin(0.f, 0.f);
            this->sprite.setScale(1.f, 1.f);
            this->animationComponent->play("RUN_RIGHT", delta_time, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        }
        else
        {
            this->sprite.setOrigin(0.f, 0.f);
            this->sprite.setScale(1.f, 1.f);
            this->animationComponent->play("WALK_RIGHT", delta_time, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        }
    }

    else if(this->movementComponent->movingLeft())
    {
        if(this->movementComponent->isMaxVelocity())
        {
            this->sprite.setOrigin(124.f, 0.f);
            this->sprite.setScale(-1.f, 1.f);
            this->animationComponent->play("RUN_RIGHT", delta_time, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        }
        else
        {
            this->sprite.setOrigin(124.f, 0.f);
            this->sprite.setScale(-1.f, 1.f);
            this->animationComponent->play("WALK_RIGHT", delta_time, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        }
    }

    else if(this->movementComponent->movingUp())
    {
        this->animationComponent->play("WALK_UP", delta_time, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }

    else if(this->movementComponent->movingDown())
    {
        this->animationComponent->play("WALK_DOWN", delta_time, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
}

void Player::update(const float &delta_time)
{

    this->movementComponent->update(delta_time);

    this->updateThrowingBomb(delta_time);

    this->updateAnimation(delta_time);

    this->hitboxComponent->update();
}

//Initializer functions
void Player::initVariables()
{
    this->throwingBomb = false;
}

void Player::initComponents()
{

}
