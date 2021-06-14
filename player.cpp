#include "player.h"

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture)
{
    this->initVariables();
    this->initComponents();

    this->setTexture(texture);
    this->setPosition(x, y);
}

Player::~Player()
{

}

//Initializer functions
void Player::initVariables()
{

}

void Player::initComponents()
{
    this->createMovementComponent(100.f);
}