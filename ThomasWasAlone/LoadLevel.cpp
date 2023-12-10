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
    // Deactivate all characters initially
    m_Thomas.deactivate();
    m_Bob.deactivate();
    m_Sophie.deactivate();

    // Activate and spawn characters based on the current level
    switch (level)
    {
    case 1:
        activateCharacters(m_Thomas, m_Sophie, startPosition);
        break;
    case 2:
        activateCharacters(m_Thomas, m_Bob, startPosition);
        break;
    case 3:
        activateCharacters(m_Bob, m_Sophie, startPosition);
        break;
    case 4:
        activateCharacters(m_Bob, m_Thomas, startPosition);
        break;
    case 5:
        activateCharacters(m_Bob, m_Sophie, startPosition);
        break;
    }
}

void Engine::activateCharacters(PlayableCharacter& char1, PlayableCharacter& char2, const Vector2f& startPosition)
{
    char1.spawn(startPosition, GRAVITY);
    char1.activate();
    char2.spawn(startPosition, GRAVITY);
    char2.activate();
}