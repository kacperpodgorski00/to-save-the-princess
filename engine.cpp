#include "engine.h"

//Static functions


//Constructors/Destructors
Engine::Engine()
{
    this->initWindow();
    this->initKeys();
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
    this->fullscreen = false;
    this->delta_time = 0.f;
}

void Engine::initWindow()
{
    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;


    if(ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;;
    }
    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    if(this->fullscreen)
    {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    }
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);

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

void Engine::initStates()
 {
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
 }

