#include "PlayingState.h"
#include "Engine.h"

PlayingState::PlayingState() {}

// Handle the user input while playing the game.
void PlayingState::handleInput(sf::RenderWindow& window, Engine& engine) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                engine.setPlaying(true);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                engine.toggleCharacter();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                engine.toggleSplitScreen();
            }
        }
    }

    if (engine.getThomas().handleInput()) {
        engine.getSoundManager().playJump();
    }
    if (engine.getBob().handleInput()) {
        engine.getSoundManager().playJump();
    }

}

// Update the game logic for every frame.
void PlayingState::update(float dt, Engine& engine) {
    if (engine.isNewLevelRequired()) {
        // Load a level
        engine.processLevelLoading();
    }

    if (engine.isPlaying()) {

        engine.processCollisionsAndInteractions(dt);

        // Handle character interactions (e.g., jumping on each other's heads)
        engine.handleCharacterInteractions();

        // Count down the time the player has left
        engine.reduceTimeRemaining(dt);

        // Update the HUD
        engine.getHud().update(dt);

     }

    // Check if a fire sound needs to be played
    engine.checkAndPlayFireSound();

    // Set the appropriate view around the appropriate character
    engine.updateView();

    engine.UpdateSinceLastFrame();

    // Update the particles if the particle system is running
    if (engine.getParticleSystem().running()) {
        engine.getParticleSystem().update(dt);
    }
}

// Draw the graphics on the screen.
void PlayingState::draw(sf::RenderWindow& window, Engine& engine) {
    window.clear(sf::Color::White);

    // Update the shader parameters
    engine.getRippleShader().setUniform("uTime", engine.getGameTimeTotal().asSeconds());

    if (!engine.isSplitScreen()) {
        // Single screen view

        // Draw the background
        window.setView(engine.getBacgroundView());

        window.draw(engine.getBackgroundSprite());

        window.draw(engine.getBackgroundSprite(), &engine.getRippleShader());

        window.setView(engine.getMainView());

        // Draw the level
        window.draw(engine.getLevelVertexArray(), &engine.getTextureTiles());

        // Draw Thomas and Bob
        window.draw(engine.getThomas().getSprite());

        window.draw(engine.getBob().getSprite());

        window.draw(engine.getSophie().getSprite());


        if (engine.getParticleSystem().running()) {
            window.draw(engine.getParticleSystem());
        }
    }
    else {
        // Split-screen view is active

        // Draw Thomas' side of the screen
        window.setView(engine.getBackgroundLeftView());

        window.draw(engine.getBackgroundSprite(), &engine.getRippleShader());

        window.setView(engine.getLeftView());

        window.draw(engine.getLevelVertexArray(), &engine.getTextureTiles());

        window.draw(engine.getBob().getSprite());

        window.draw(engine.getThomas().getSprite());

        if (engine.getParticleSystem().running()) {
            window.draw(engine.getParticleSystem());
        }

        // Draw Bob's side of the screen
        window.setView(engine.getBackgroundRightView());
        window.draw(engine.getBackgroundSprite(), &engine.getRippleShader());

        window.setView(engine.getRightView());

        window.draw(engine.getLevelVertexArray(), &engine.getTextureTiles());

        window.draw(engine.getThomas().getSprite());

        window.draw(engine.getBob().getSprite());

        if (engine.getParticleSystem().running()) {
            window.draw(engine.getParticleSystem());
        }
    }


    // Draw the HUD
    window.setView(engine.getHudView());
    window.draw(engine.getHud().getLevel());
    window.draw(engine.getHud().getTime());
    if (!engine.isPlaying()) {
        window.draw(engine.getHud().getMessage());
    }

    // Draw the Hazard message
    window.draw(engine.getHud().getHazardMessage());

    // Show everything we have just drawn
    window.display();
}