#pragma once

#include "State.h"
#include "Gui.h"
class SettingState : public State
{
public:

private:
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;
    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownList;


    void initVariables();
    void initBackgrounds();
    void initfonts();
    void initButtons();
    void initGUI();
protected:
    void initKeyBinds();

public:	
    SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingState();
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

