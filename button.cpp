#include "button.h"

Button::Button(float x, float y, float width, float height,
               sf::Font* font, std::string text,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this->buttonState = IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setColor(sf::Color::White);
    this->text.setCharacterSize(18);
    this->text.setPosition(
        this->shape.getPosition().x + ((this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f)),
        this->shape.getPosition().y -5.0+ ((this->shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f))
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{

}

//Accessors
const bool Button::isPressed() const
{
    if(this->buttonState == ACTIVE)
    {
        return true;
    }
    return false;
}

//Functions
void Button::update(const sf::Vector2f mousePos)
{
    //Update the info is the button hover and pressed

    //Idle
    this->buttonState = IDLE;

    //Hover
    if(this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = HOVER;

        //Active
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = ACTIVE;
        }
    }

    switch (this->buttonState)
    {
    case IDLE:
        this->shape.setFillColor(this->idleColor);
        break;

    case HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;

    case ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;

    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}

void Button::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
    target->draw(this->text);
}
