#pragma once

#include "gamestate.h"
#include "editorstate.h"
#include "settingstate.h"
#include "gui.h"

class MainMenuState : public State
{
public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions
    void updateInput(const float& delta_time);
    void updateButtons();
    void update(const float& delta_time);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);

private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

};


