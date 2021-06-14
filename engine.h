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
    sf::RenderWindow *window;
    sf::Event sfEvent;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen;

    sf::Clock delta_time_Clock;
    float delta_time;

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    //Initialization
    void initVariables();
    void initWindow();
    void initKeys();
    void initStates();

};

