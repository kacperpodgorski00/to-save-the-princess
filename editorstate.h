#pragma once

#include "state.h"
#include "gui.h"
#include "pausemenu.h"
#include "tilemap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState : public State
{
public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& delta_time);
    void updateEditorInput(const float& delta_time);
    void updateButtons();
    void updateGui();
    void updatePauseMenuButtons();
    void update(const float& delta_time);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);

private:
    //Variables
    sf::Font font;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    sf::RectangleShape selectorRect;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();
};


