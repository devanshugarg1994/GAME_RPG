#pragma once
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
class GameState : 
    public State
{
private:
    Player *player;
    sf::Font font;
    PauseMenu *pMenu;


protected:
    void initKeyBinds();
    void initfonts();
    void initPauseMenu();
    void initTextures();
    void initPlayers();

public:
    GameState(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);

};

