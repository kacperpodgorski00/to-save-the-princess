#include "engine.h"

//Static functions


//Constructors/Destructors
Engine::Engine()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Engine::~Engine()
{
    delete this->window;

    while(!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}


//Functions
void Engine::endApplication()
{
    std::cout << "Ending Application!" << std::endl;
}

void Engine::updateDeltatime()
{
    this->delta_time = this->delta_time_Clock.restart().asSeconds();
}

void Engine::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Engine::update()
{
    this->updateSFMLEvents();

    if(!this->states.empty())
    {
        this->states.top()->update(this->delta_time);

        if(this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    //Closing game
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Engine::render()
{
    this->window->clear();

    //Render items

    if(!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

void Engine::run()
{
    while (this->window->isOpen())
    {
        this->updateDeltatime();
        this->update();
        this->render();
    }
}

//Initializer fuctions
void Engine::initVariables()
{
    this->window = nullptr;

    this->delta_time = 0.f;

    this->gridSize = 100.f;
}

void Engine::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Engine::initWindow()
{
    if(this->gfxSettings.fullscreen)
    {
        this->window = new sf::RenderWindow(
                 this->gfxSettings.resolution,
                 this->gfxSettings.title,
                 sf::Style::Fullscreen,
                 this->gfxSettings.contextSettings);
        }
    else
        this->window = new sf::RenderWindow(
                 this->gfxSettings.resolution,
                 this->gfxSettings.title,
                 sf::Style::Titlebar | sf::Style::Close,
                 this->gfxSettings.contextSettings);

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);

}

void Engine::initKeys()
{
    std::ifstream ifs("Config/supported_keys.ini");

    if(ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while(ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }
    ifs.close();

    //Debug REMOVE LATER!!!
    for(auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

void Engine::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Engine::initStates()
 {
    this->states.push(new MainMenuState(&this->stateData));
 }

