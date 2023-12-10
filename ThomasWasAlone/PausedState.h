/*// PausedState class
#pragma once
#include "GameState.h"
#include "Engine.h"

class GameState;
class Engine;

class PausedState : public GameState {
public:
    void handleInput(sf::RenderWindow& window, Engine& engine) override;
    void update(float dt, Engine& engine) override;
    void draw(sf::RenderWindow& window, Engine& engine) override;
};
*/