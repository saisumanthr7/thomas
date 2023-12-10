#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];

	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	// Prepare the sound emitters
	populateEmitters(m_FireEmitters, m_ArrayLevel);

	// How long is this new time limit
	m_TimeRemaining = m_LM.getTimeLimit();

	// Determine character spawning for the new level
	setupCharactersForLevel(m_LM.getCurrentLevel(), m_LM.getStartPosition());

	m_NewLevelRequired = false;
}

void Engine::setupCharactersForLevel(int level, const Vector2f& startPosition)
{
    // Determine which characters to spawn based on the current level
    switch (level)
    {
    case 1:
        m_Thomas.spawn(startPosition, GRAVITY);
        m_Bob.spawn(startPosition, GRAVITY);
        break;
    case 2:
        m_Thomas.spawn(startPosition, GRAVITY);
        m_Sophie.spawn(startPosition, GRAVITY);
        break;
    case 3:
        m_Bob.spawn(startPosition, GRAVITY);
        m_Sophie.spawn(startPosition, GRAVITY);
        break;
    case 4:
        m_Bob.spawn(startPosition, GRAVITY);
        m_Thomas.spawn(startPosition, GRAVITY);
        break;
    case 5:
        m_Bob.spawn(startPosition, GRAVITY);
        m_Sophie.spawn(startPosition, GRAVITY);
        break;
    }
}