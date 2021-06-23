#include "gui.h"

gui::Button::Button(float x, float y, float width, float height,
               sf::Font* font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
               short unsigned id)
{
    this->buttonState = IDLE;
    this->id = id;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idle_color);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(outline_idle_color);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
        this->shape.getPosition().x + ((this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f)),
        this->shape.getPosition().y -5.0+ ((this->shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f))
    );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

    this->outlineIdleColor = outline_idle_color;
    this->outlineHoverColor = outline_hover_color;
    this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
{

}

//Accessors
const bool gui::Button::isPressed() const
{
    if(this->buttonState == ACTIVE)
    {
        return true;
    }
    return false;
}

const std::string gui::Button::getText() const
{
    return this->text.getString();
}

const short unsigned & gui::Button::getId() const
{
    return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
    this->text.setString(text);
}

void gui::Button::setId(const unsigned short id)
{
    this->id = id;
}

//Functions
void gui::Button::update(const sf::Vector2f& mousePos)
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
        this->text.setFillColor(this->textIdleColor);
        this->shape.setOutlineColor(this->outlineIdleColor);
        break;

    case HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        this->shape.setOutlineColor(this->outlineHoverColor);
        break;

    case ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        this->shape.setOutlineColor(this->outlineActiveColor);
        break;

    default:
        this->shape.setFillColor(sf::Color::Red);
        this->text.setFillColor(sf::Color::Blue);
        this->shape.setOutlineColor(sf::Color::Green);
        break;
    }
}

void gui::Button::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
    target.draw(this->text);
}


// ################### DROP DOWN LIST ####################

//Constructor/Destructor
gui::DropDownList::DropDownList(float x, float y, float width, float height,
    sf::Font &font, std::string list[],
    unsigned numberOfElements, unsigned default_index)
    : font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
    //unsigned numberOfElements = sizeof (list) / sizeof (std::string);

    this->activeElement = new gui::Button(
                x, y, width, height,
                &this->font, list[default_index], 20,
                sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
                );

    for(size_t i=0; i < numberOfElements; i++)
    {
        this->list.push_back(
            new gui::Button(
                x, y + ((i+1) * height), width, height,
                &this->font, list[i], 20,
                sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
                i
            )
        );
    }
}

gui::DropDownList::~DropDownList()
{
    delete this->activeElement;
    for(size_t i=0; i < this->list.size(); i++)
    {
        delete this->list[i];
    }
}


//Accessors
const bool gui::DropDownList::getKeytime()
{
    if(this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}
const unsigned short & gui::DropDownList::getActiveElementId() const
{
    return this->activeElement->getId();
}

//Functions
void gui::DropDownList::updateKeytime(const float& delta_time)
{
    if(this->keytime < this->keytimeMax)
    {
        this->keytime += 10.f * delta_time;
    }
}

void gui::DropDownList::update(const sf::Vector2f mousePos, const float& delta_time)
{
    this->updateKeytime(delta_time);

    this->activeElement->update(mousePos);

    //show and hide the list
    if(this->activeElement->isPressed() && this->getKeytime())
    {
        if(this->showList)
        {
            this->showList = false;
        }
        else
        {
            this->showList = true;
        }
    }

    if(this->showList)
    {
        for (auto &i : this->list)
        {
            i->update(mousePos);

            if(i->isPressed() && this->getKeytime())
            {
                this->showList = false;
                this->activeElement->setText(i->getText());
                this->activeElement->setId(i->getId());
            }
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget &target)
{
    this->activeElement->render(target);

    if(this->showList)
    {
        for (auto &i : this->list)
        {
            i->render(target);
        }
    }
}
