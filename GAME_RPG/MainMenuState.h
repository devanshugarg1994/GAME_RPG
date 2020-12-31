#pragma once
#include "State.h"
#include "Button.h"
class MainMenuState :
    public State
{
private:
    sf::RectangleShape background;
    sf::Font font;
    std::map<std::string, Button*> buttons;
    void initfonts();
    void initButtons();
protected:
    void initKeyBinds();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    virtual ~MainMenuState();
    void endState();
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);
};

