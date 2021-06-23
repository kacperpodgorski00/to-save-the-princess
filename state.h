#pragma once

#include "player.h"
#include "graphicssettings.h"


class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
    StateData() {};

    //Variables
    float gridSize;
    sf::RenderWindow* window;
    GraphicsSettings* gfxSettings;
    std::map<std::string, int>* supportedKeys;
    std::stack<State*>* states;

};

class State
{

public:
    State(StateData* state_data);
    virtual ~State();

    //Accessors
    const bool& getQuit() const;
    const bool getKeytime();

    //Functions
    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateMousePositions();
    virtual void updateKeytime(const float& delta_time);
    virtual void updateInput(const float& delta_time) = 0;
    virtual void update(const float& delata_time) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
    StateData* stateData;
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool paused;
    float keytime;
    float keytimeMax;
    float gridSize;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;


    //Resources
    std::map<std::string, sf::Texture> textures;

    //Functions
    virtual void initKeybinds() = 0;

private:

};


