#pragma once
#include "Entity.h"
class Player :
    public Entity
{

private:

    void initVariables();
    void initComponenets();
    bool debug = false;
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    void debugFun();
    void updateAnimation(const float& dt);
    void update(const float& dt);

    //Functions

};

