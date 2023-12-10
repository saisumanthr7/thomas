#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Engine.h"

class Engine;  // Forward declaration

class GameState {
public:
    // Handle the user input.
    virtual void handleInput(sf::RenderWindow& window, Engine& engine) = 0;

    // Update the game logic.
    virtual void update(float dt, Engine& engine) = 0;

    // Draw the graphics onto the screen
    virtual void draw(sf::RenderWindow& window, Engine& engine) = 0;

    // A default destructor
    virtual ~GameState() = default;
};