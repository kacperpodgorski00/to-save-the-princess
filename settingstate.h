#pragma once

#include "state.h"
#include "gui.h"


class SettingState : public State
{
public:
    SettingState(StateData* state_data);
    virtual ~SettingState();

    //Accessors

    //Functions
    void updateInput(const float& delta_time);
    void updateGui(const float& delta_time);
    void update(const float& delta_time);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);

private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropdownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initText();

};


