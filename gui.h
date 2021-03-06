#pragma once


enum button_states{IDLE = 0, HOVER, ACTIVE};

namespace gui
{
    class Button
    {

    public:
        Button(float x, float y, float width, float height,
               sf::Font* font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color = sf::Color::Transparent,
               sf::Color outline_hover_color = sf::Color::Transparent,
               sf::Color outline_active_color = sf::Color::Transparent,
               short unsigned id = 0);
        ~Button();

        //Accessors
        const bool isPressed() const;
        const std::string getText() const;
        const short unsigned& getId() const;

        //Modifiers
        void setText(const std::string text);
        void setId(const short unsigned id);

        //Functions
        void update(const sf::Vector2f& mousePos);
        void render(sf::RenderTarget& target);

    private:
        short unsigned buttonState;
        short unsigned id;

        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;
    };

    class DropDownList
    {
    public:
        DropDownList(float x, float y, float width, float height, sf::Font &font, std::string list[],
                     unsigned numberOfElements, unsigned default_index = 0);
        ~DropDownList();


        //Accessors
        const bool getKeytime();
        const unsigned short& getActiveElementId() const;

        //Functions
        void updateKeytime(const float& delta_time);
        void update(const sf::Vector2f mousePos, const float& delta_time);
        void render(sf::RenderTarget& target);

    private:
        float keytime;
        float keytimeMax;
        sf::Font& font;
        gui::Button* activeElement;
        std::vector<gui::Button*> list;
        bool showList;



    };
}


