#pragma once

#include "mainmenustate.h"

class Engine
{

public:
    //Constructors/Destructors
    Engine();
    virtual ~Engine();

    //Functions

    //Regular
    void endApplication();

    //Update
    void updateDeltatime();
    void updateSFMLEvents();
    void update();

    //Render
    void render();

    //Core
    void run();

private:
    //Variables
    GraphicsSettings gfxSettings;
    StateData stateData;
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock delta_time_Clock;
    float delta_time;

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    float gridSize;

    //Initialization
    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initKeys();
    void initStateData();
    void initStates();

};

