/*#include "GameState.h"
#include "PausedState.h"

void PausedState::handleInput(sf::RenderWindow& window, Engine& engine) {
    // Handle paused state input
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {  // Assuming 'P' is the pause key
            engine.togglePause();
        }
        // Additional input handling for paused state
    }
}

void PausedState::update(float dt, Engine& engine) {
    // Update paused state logic
}

void PausedState::draw(sf::RenderWindow& window, Engine& engine) {
    window.clear();
    // Drawing code for paused state
    window.display();
}
*/