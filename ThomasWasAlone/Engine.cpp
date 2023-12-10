#include "Engine.h"
#include "FireCollisionObserver.h"
#include "WaterCollisionObserver.h"
#include <memory>
#include <sstream>


Engine::Engine()
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Thomas was late",
		Style::Fullscreen);

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_HudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));

	// Inititialize the split-screen Views
	m_LeftView.setViewport(
		FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	m_RightView.setViewport(
		FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	m_BGLeftView.setViewport(
		FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	m_BGRightView.setViewport(
		FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}
	else
	{
		// Load two shaders (1 vertex, 1 fragment)
		m_RippleShader.loadFromFile("shaders/vertShader.vert",
			"shaders/rippleShader.frag");
	}

	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/background.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);


	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tiles_sheet.png");

	// Initialize the particle system
	m_PS.init(1000);

	// Create and attach observers to the character using smart pointers
	std::shared_ptr<Observer> fireObserver = std::make_shared<FireCollisionObserver>(m_Hud);
	m_Thomas.attachObserver(fireObserver);
	m_Bob.attachObserver(fireObserver);

	// Create and attach observers to the character using smart pointers
	std::shared_ptr<Observer> iceObserver = std::make_shared<WaterCollisionObserver>(m_Hud);
	m_Thomas.attachObserver(iceObserver);
	m_Bob.attachObserver(iceObserver);

	// Initialize the currentState with PlayingState
	currentState = std::make_unique<PlayingState>();
}// End Engine constructor

void Engine::run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		// Update the total game time
		m_GameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		
		currentState->handleInput(m_Window, *this);
		currentState->update(dtAsSeconds, *this);
		// Draw in any state
		currentState->draw(m_Window, *this);
	}
}

// Changes the state
void Engine::changeState(GameState* state) {
	currentState.reset(state);
}

// Returns a reference to the Thomas character object.
Thomas& Engine::getThomas() {
	return m_Thomas;
}

// Returns a reference to the Bob character object.
Bob& Engine::getBob() {
	return m_Bob;
}

// Returns a reference to the Sophie character object.
Sophie& Engine::getSophie() {
	return m_Sophie;
}


// Returns a reference to the shader used for ripple effects.
sf::Shader& Engine::getRippleShader() {
	return m_RippleShader;
}

// Returns a reference to the texture used for the background.
sf::Texture& Engine::getBackgroundTexture() {
	return m_BackgroundTexture;
}

// Returns a reference to the sprite used for the background.
sf::Sprite& Engine::getBackgroundSprite() {
	return m_BackgroundSprite;
}

// Returns a reference to the main view of the game window.
sf::View& Engine::getMainView() {
	return m_MainView;
}

// Returns a reference to the main background view.
sf::View& Engine::getBacgroundView() {
	return m_BGMainView;
}

// Returns a reference to the left split-screen background view.
sf::View& Engine::getBackgroundLeftView() {
	return m_BGLeftView;
}

// Returns a reference to the right split-screen background view.
sf::View& Engine::getBackgroundRightView() {
	return m_BGRightView;
}

// Returns a reference to the HUD view.
sf::View& Engine::getHudView() {
	return m_HudView;
}

// Returns a reference to the vertex array representing the level layout.
sf::VertexArray& Engine::getLevelVertexArray() {
	return m_VALevel;
}

// Returns a reference to the texture used for the level tiles.
sf::Texture& Engine::getTextureTiles() {
	return m_TextureTiles;
}

// Returns a reference to the HUD object, which displays game info.
Hud& Engine::getHud() {
	return m_Hud;
}

// Returns whether the game is currently being played.
bool Engine::isPlaying() const {
	return m_Playing;
}

// Returns whether the game is in split-screen mode.
bool Engine::isSplitScreen() const {
	return m_SplitScreen;
}

// Toggles the focus between Thomas and Bob.
void Engine::toggleCharacter() {
	m_Character1 = !m_Character1;
}

// Toggles the split-screen mode on or off.
void Engine::toggleSplitScreen() {
	m_SplitScreen = !m_SplitScreen;
}

// Returns a reference to the sound manager, handling game sounds.
SoundManager& Engine::getSoundManager() {
	return m_SM;
}

// Returns the total game time elapsed.
const sf::Time& Engine::getGameTimeTotal() const {
	return m_GameTimeTotal;
}

// Returns a reference to the right view for split-screen mode.
const sf::View& Engine::getRightView() const {
	return m_RightView;
}

// Returns a reference to the left view for split-screen mode.
const sf::View& Engine::getLeftView() const {
	return m_LeftView;
}

// Returns a reference to the particle system used in the game.
ParticleSystem& Engine::getParticleSystem() {
	return m_PS;
}

// Sets the playing state of the game.
void Engine::setPlaying(bool playing) {
	m_Playing = playing;
}

// Checks if a new level is required to be loaded.
bool Engine::isNewLevelRequired() const {
	return m_NewLevelRequired;
}

// Processes the loading of a new level if required.
void Engine::processLevelLoading() {
	if (isNewLevelRequired()) {
		loadLevel();
	}
}

// Processes collisions and interactions for the current frame.
void Engine::processCollisionsAndInteractions(float dt) {
		getThomas().update(dt);
		getBob().update(dt);

		if (detectCollisions(getThomas()) && detectCollisions(getBob())) {
			setNewLevelRequired(true);
			getSoundManager().playReachGoal();
		}
		else {
			detectCollisions(getBob());
		}
}

// Sets whether a new level is required.
void Engine::setNewLevelRequired(bool required) {
	m_NewLevelRequired = required;
}

// Handles interactions between characters (e.g., jumping on each other).
void Engine::handleCharacterInteractions() {
	if (m_Bob.getFeet().intersects(m_Thomas.getHead()))
	{
		m_Bob.stopFalling(m_Thomas.getHead().top);
	}
	else if (m_Thomas.getFeet().intersects(m_Bob.getHead()))
	{
		m_Thomas.stopFalling(m_Bob.getHead().top);
	}
}

// Reduces the remaining time for the current level.
void Engine::reduceTimeRemaining(float dt) {
	m_TimeRemaining -= dt;
	if (m_TimeRemaining <= 0) {
		m_NewLevelRequired = true;
		m_TimeRemaining = 0; // Reset time to avoid negative values
	}
}

// Checks for and plays fire sound effects if necessary.
void Engine::checkAndPlayFireSound() {

	vector<Vector2f>::iterator it;
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Where is this emitter?
		// Store the location in pos
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emiter near the player?
		// Make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Is the player inside localRect?
		if (m_Thomas.getPosition().intersects(localRect))
		{
			// Play the sound and pass in the location as well
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}
}

// Updates the game view based on the current game state.
void Engine::updateView() {
	// Implement logic to update the game view based on the game state
	if (m_SplitScreen) {
		// Update split-screen views
		m_LeftView.setCenter(m_Thomas.getCenter());
		m_RightView.setCenter(m_Bob.getCenter());
	}
	else {
		// Update single-screen view
		if (m_Character1) {
			m_MainView.setCenter(m_Thomas.getCenter());
		}
		else {
			m_MainView.setCenter(m_Bob.getCenter());
		}
	}
}

// Updates the HUD and other frame-based elements.
void Engine::UpdateSinceLastFrame() {

	// Increment the number of frames since the last HUD calculation
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		// Update game HUD text
		stringstream ssTime;
		stringstream ssLevel;

		// Update the time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		// Update the level text
		ssLevel << "Level:" << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		m_FramesSinceLastHUDUpdate = 0;
	}
}
