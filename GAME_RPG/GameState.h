#pragma once
#include "State.h"
class GameState : 
    public State
{
private:
    Entity player;

protected:
    void initKeyBinds();

public:
    GameState(sf::RenderWindow * window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();
    void endState();
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);

};

