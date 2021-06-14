#pragma once

#include "unit.h"

class Player : public Unit
{

public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    //Functions

private:
    //Variables

    //Initializer functions
    void initVariables();
    void initComponents();

};


