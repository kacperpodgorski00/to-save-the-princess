#include "settingstate.h"

SettingState::SettingState(StateData* state_data)
    : State(state_data)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initGui();
    this->initText();
}

SettingState::~SettingState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    auto it2 = this->dropdownLists.begin();
    for (it2 = this->dropdownLists.begin(); it2 != this->dropdownLists.end(); ++it2)
    {
        delete it2->second;
    }
}

//Accessors

//Functions
void SettingState::updateInput(const float &delta_time)
{

}

void SettingState::updateGui(const float &delta_time)
{
    /*Updates all the gui elements in the state and handles their functionality*/
    //BUTTONS
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    //Button functionality
    //Quit the game
    if(this->buttons["BACK"]->isPressed())
    {
        this->endState();
    }

    //Apply selected settings
    if(this->buttons["APPLY"]->isPressed())
    {
        //TEST, REMOVE LATER
        this->stateData->gfxSettings->resolution = this->modes[this->dropdownLists["RESOLUTION"]->getActiveElementId()];

        this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
    }

    //DROPDOWN LISTS
    for (auto &it : this->dropdownLists)
    {
        it.second->update(this->mousePosView, delta_time);
    }

    //Dropdown lists functionality
}

void SettingState::update(const float& delta_time)
{
    this->updateMousePositions();
    this->updateInput(delta_time);

    this->updateGui(delta_time);
}

void SettingState::renderGui(sf::RenderTarget& target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }

    for (auto &it : this->dropdownLists)
    {
        it.second->render(target);
    }
}

void SettingState::render(sf::RenderTarget* target)
{
    if(!target)
    {
        target = this->window;
    }
    target->draw(this->background);

    this->renderGui(*target);

    target->draw(this->optionsText);

//    REMOVE LATER !!!
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
}


//Initialazer functions
void SettingState::initVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingState::initBackground()
{
    this->background.setSize(
          sf::Vector2f
          (
             static_cast<float>(this->window->getSize().x),
             static_cast<float>(this->window->getSize().y)
          )
    );

    if(!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
    {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);

}

void SettingState::initFonts()
{
    if(!this->font.loadFromFile("Fonts/Insanibu.ttf"))
    {
        throw("ERROR: MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void SettingState::initKeybinds()
{
    std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void SettingState::initGui()
{
    this->buttons["BACK"] = new gui::Button(1020, 330, 300, 50,
        &this->font, "Back", 50,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["APPLY"] = new gui::Button(725, 330, 300, 50,
        &this->font, "Apply", 50,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    std::vector<std::string> modes_str;
    for(auto &i : this->modes)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    this->dropdownLists["RESOLUTION"] = new gui::DropDownList(1055, 90, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingState::initText()
{
    this->optionsText.setFont(this->font);

    this->optionsText.setPosition(sf::Vector2f(750.f, 90.f));

    this->optionsText.setCharacterSize(43);
    this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

    this->optionsText.setString(
        "Resolution \nFullscreen \nVsync \nAntialiasing \n"
    );
}
