#pragma once
#include "Entity.h"
class Player :
    public Entity
{

private:

    void initVariables();
    void initComponenets();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();
    void update(const float& dt);

    //Functions

};

