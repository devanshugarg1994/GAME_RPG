#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
    private:
        sf::Font font;
        PauseMenu* pMenu;
        std::map<std::string, gui::Button*> buttons;
        TileMap* tileMap;
        sf::RectangleShape selectorRect;
        // Functions
        void initVariables();
        void initfonts();
        void initButtons();
        void initPauseMenu();
        void initKeyBinds();
        void initGui();
        void initTileMap();

    public:
        EditorState(StateData* state_data);
        virtual ~EditorState();
        void updateInput(const float& dt);
        void updateButtons();
        void updateGUI();
        void updatePauseButtons();
        void update(const float& dt);
        void renderButtons(sf::RenderTarget& target);
        void renderGui(sf::RenderTarget& target);
        void render(sf::RenderTarget* target = nullptr);
    };



