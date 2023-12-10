#pragma once
#include "GameState.h"
#include "Engine.h"

class GameState;
class Engine;

class PlayingState : public GameState {
public:
    PlayingState();

    // Handle the user input while playing the game and override the default handleInput
    void handleInput(sf::RenderWindow& window, Engine& engine) override;

    // Update the game logic for every frame and override the default update.
    void update(float dt, Engine& engine) override;

    // Draw the graphics on the screen and override the default draw.
    void draw(sf::RenderWindow& window, Engine& engine) override;
};
