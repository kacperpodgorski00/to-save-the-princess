#pragma once

#include "unit.h"
#include "player.h"

class State
{

public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~State();

    const bool& getQuit() const;
    void endState();

    virtual void updateMousePositions();
    virtual void updateInput(const float& delta_time) = 0;
    virtual void update(const float& delata_time) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;


    //Resources
    std::map<std::string, sf::Texture> textures;

    //Functions
    virtual void initKeybinds() = 0;

private:

};


