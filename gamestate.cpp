#include "gamestate.h"

//Constructors / Destructors
GameState::GameState(StateData* state_data)
    : State(state_data)
{
    this->initKeybinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initPlayers();
    this->initTileMap();
}

GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
    delete this->tileMap;
}


void GameState::updateInput(const float &delta_time)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
    {
        if(!this->paused)
        {
            this->pauseState();
        }
        else
        {
            this->unpauseState();
        }
    }
}

void GameState::updatePlayerInput(const float &delta_time)
{
    //Update player input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    {
        this->player->move(-1.f, 0.f, delta_time);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        this->player->move(1.f, 0.f, delta_time);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    {
        this->player->move(0.f, -1.f, delta_time);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    {
        this->player->move(0.f, 1.f, delta_time);
    }
}

void GameState::updatePauseMenuButtons()
{
    if(this->pmenu->isButtonPressed("QUIT"))
            this->endState();
}

void GameState::update(const float& delta_time)
{
    this->updateMousePositions();
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);

    if(!this->paused) //Unpaused update
    {
        this->updatePlayerInput(delta_time);

        this->player->update(delta_time);
    }
    else //Paused update
    {
        this->pmenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget* target)
{
    if(!target)
    {
        target = this->window;
    }

    //this->map.render(*target);

    this->player->render(*target);

    if(this->paused) //Pause menu render
    {
        this->pmenu->render(*target);
    }
}

//Initializer functions
void GameState::initKeybinds()
{
    std::ifstream ifs("Config/gamestate_keybinds.ini");

    if(ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while(ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void GameState::initFonts()
{
    if(!this->font.loadFromFile("Fonts/Insanibu.ttf"))
    {
        throw("ERROR: MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void GameState::initTextures()
{
    if(!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/hero_right.png"))
    {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
    }
}

void GameState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 800.f, "Quit");
}

void GameState::initPlayers()
{
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}
