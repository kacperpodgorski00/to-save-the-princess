#pragma once

#include "state.h"
#include "pausemenu.h"
#include "tilemap.h"

class GameState : public State
{

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void updateInput(const float& delta_time);
    void updatePlayerInput(const float& delta_time);
    void updatePauseMenuButtons();
    void updateButtons();
    void update(const float& delta_time);
    void render(sf::RenderTarget* target = nullptr);

private:
    sf::Font font;
    PauseMenu* pmenu;

    Unit *player;

    TileMap* tileMap;

    //Functions
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initTileMap();

};
