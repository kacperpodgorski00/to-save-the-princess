#pragma once

#include "state.h"

class GameState : public State
{

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Functions
    void updateInput(const float& delta_time);
    void update(const float& delta_time);
    void render(sf::RenderTarget* target = nullptr);

private:
    Unit *player;

    //Functions
    void initKeybinds();
    void initTextures();
    void initPlayers();

};
