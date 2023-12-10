#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"
#include "GameState.h"
#include "PlayingState.h"
#include "Sophie.h"

using namespace sf;

class GameState;

class Engine
{
private:
	// The texture holder
	TextureHolder th;

	// create a particle system
	ParticleSystem m_PS;

	// Thomas and his friend, Bob
	Thomas m_Thomas;
	Bob m_Bob;
	Sophie m_Sophie;

	// A class to manage all the levels
	LevelManager m_LM;

	// Create a SoundManager
	SoundManager m_SM;

	// The Hud
	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 300;

	// A regular RenderWindow
	RenderWindow m_Window;

	// The main Views
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	// Three views for the background
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;

	View m_HudView;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	// Declare a shader for the background
	Shader m_RippleShader;

	// Is the game currently playing?
	bool m_Playing = false;

	// Is character 1 or 2 the current focus?
	bool m_Character1 = true;

	// Start in full screen mode
	bool m_SplitScreen = false;

	// How much time is left in the current level
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;

	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	// The vertex array for the level design
	VertexArray m_VALevel;

	// The 2d array with the map for the level
	// A pointer to a pointer
	int** m_ArrayLevel = NULL;

	// Texture for the background and the level tiles
	Texture m_TextureTiles;

	// Private functions for internal use only
	//void input();
	//void update(float dtAsSeconds);
	//void draw();

	// Load a new level
	void loadLevel();

	// Run will call all the private functions
	bool detectCollisions(PlayableCharacter& character);

	// Make a vector of the best places to emit sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters,
		int** arrayLevel);

	// A vector of Vector2f for the fire emitter locations
	vector <Vector2f> m_FireEmitters;

	// Create a unique pointer to current state from Gamestate
	std::unique_ptr<GameState> currentState;

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

	// Changes the state
	void changeState(GameState* state);

	// Getters functions

	// Returns a reference to the Thomas character object.
	Thomas& getThomas();

	// Returns a reference to the Bob character object.
	Bob& getBob(); 

	// Returns a reference to the Sophie character object.
	Sophie& getSophie();

	// Returns a reference to the shader used for ripple effects.
	sf::Shader& getRippleShader();

	// Returns a reference to the texture used for the background.
	sf::Texture& getBackgroundTexture();

	// Returns a reference to the sprite used for the background.
	sf::Sprite& getBackgroundSprite();

	// Returns a reference to the main view of the game window.
	sf::View& getMainView();

	// Returns a reference to the HUD view.
	sf::View& getHudView();

	// Returns a reference to the vertex array representing the level layout.
	sf::VertexArray& getLevelVertexArray();

	// Returns a reference to the texture used for the level tiles.
	sf::Texture& getTextureTiles();

	// Returns a reference to the HUD object, which displays game info.
	Hud& getHud();

	// Returns whether the game is currently being played.
	bool isPlaying() const;

	// Returns whether the game is in split-screen mode.
	bool isSplitScreen() const;

	// Returns a reference to the main background view.
	sf::View& getBacgroundView();

	// Returns a reference to the left split-screen background view.
	sf::View& getBackgroundLeftView();

	// Returns a reference to the right split-screen background view.
	sf::View& getBackgroundRightView();

	// Returns a reference to the sound manager, handling game sounds.
	SoundManager& getSoundManager();

	// Returns the total game time elapsed.
	const sf::Time& getGameTimeTotal() const;

	// Returns a reference to the right view for split-screen mode.
	const sf::View& getRightView() const;

	// Returns a reference to the particle system used in the game.
	ParticleSystem& getParticleSystem();

	// Returns a reference to the left view for split-screen mode.
	const sf::View& getLeftView() const;

	// Setter functions

	// Toggles the focus between Thomas and Bob.
	void toggleCharacter();

	// Toggles the split-screen mode on or off.
	void toggleSplitScreen();

	// Sets the playing state of the game.
	void setPlaying(bool playing);

	// Checks if a new level is required to be loaded.
	bool isNewLevelRequired() const;

	// Processes the loading of a new level if required.
	void processLevelLoading();

	// Processes collisions and interactions for the current frame.
	void processCollisionsAndInteractions(float dt);

	// Sets whether a new level is required.
	void setNewLevelRequired(bool required);

	// Handles interactions between characters (e.g., jumping on each other).
	void handleCharacterInteractions();

	// Reduces the remaining time for the current level.
	void reduceTimeRemaining(float dt);

	// Checks for and plays fire sound effects if necessary.
	void checkAndPlayFireSound();

	// Updates the game view based on the current game state.
	void updateView();

	// Updates the HUD and other frame-based elements.
	void UpdateSinceLastFrame();

	void setupCharactersForLevel(int level, const Vector2f& startPosition);

	void activateCharacters(PlayableCharacter& char1, PlayableCharacter& char2, const Vector2f& startPosition);

};
