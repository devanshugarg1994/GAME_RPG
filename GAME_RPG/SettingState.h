#pragma once

#include "State.h"
#include "Gui.h"
#include "GraphicsSetting.h"
class SettingState : public State
{
public:

private:
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;
    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownList;
    sf::Text optionsText;
    std::vector<sf::VideoMode> modes;


    void initVariables();
    void initBackgrounds();
    void initfonts();
    void initButtons();
    void initGUI();
    void initText();
protected:
    void initKeyBinds();

public:	
    SettingState(StateData* state_data);
    virtual ~SettingState();
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

