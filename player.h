#pragma once

#include "unit.h"

class Player : public Unit
{

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Functions
    void updateThrowingBomb(const float& delta_time);
    void updateAnimation(const float& delta_time);
    virtual void update(const float& delta_time);

private:
    //Variables
    bool throwingBomb;

    //Initializer functions
    void initVariables();
    void initComponents();

};


