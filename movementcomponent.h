#pragma once


class MovementComponent
{

public:
    MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    //Accessors
    const float& getMaxVelocity() const;
    const sf::Vector2f& getVelocity() const;


    //Functions
    const bool isIdle() const;
    const bool moving() const;
    const bool movingLeft() const;
    const bool movingRight() const;
    const bool movingUp() const;
    const bool movingDown() const;
    const bool isMaxVelocity() const;


    void move(const float dir_x, const float dir_y, const float& delta_time);
    void update(const float& delta_time);

private:
    sf::Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    //Initializer functions



};

