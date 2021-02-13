#pragma once
#include "State.h"
#include "Gui.h"
#include"GameState.h"
#include "EditorState.h"
#include "SettingState.h"
#include "GraphicsSetting.h"

class MainMenuState :
    public State
{
private:
    GraphicsSetting& gSetting;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;
    std::map<std::string, gui::Button*> buttons;
    void initVariables();
    void initBackgrounds();
    void initfonts();
    void initButtons();
protected:
    void initKeyBinds();

public:
    MainMenuState(sf::RenderWindow* window, GraphicsSetting& gSettings,
            std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

