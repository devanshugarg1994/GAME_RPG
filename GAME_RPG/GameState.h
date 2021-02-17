#pragma once
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "TileMap.h"
class GameState : 
    public State
{
private:
    Player *player;
    sf::Font font;
    PauseMenu *pMenu;
    TileMap* tileMap;


    void initKeyBinds();
    void initfonts();
    void initPauseMenu();
    void initTextures();
    void initPlayers();
    void initTileMap();

public:
    GameState(StateData * state_data);
    virtual ~GameState();

    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);

};

