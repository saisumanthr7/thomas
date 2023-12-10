#include "Hud.h"
#include <iostream>

Hud::Hud()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/Roboto-Light.ttf");

	// Paused
	m_StartText.setFont(m_Font);
	m_StartText.setCharacterSize(100);
	m_StartText.setFillColor(Color::White);
	m_StartText.setString("Press Enter when ready!");

	// Hazard Text
	m_SetHazardText.setFont(m_Font);
	m_SetHazardText.setCharacterSize(75);
	m_SetHazardText.setFillColor(Color::White);

	// Position the text
	FloatRect textRect = m_StartText.getLocalBounds();

	m_StartText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	m_StartText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

	m_SetHazardText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

	// Time
	m_TimeText.setFont(m_Font);
	m_TimeText.setCharacterSize(75);
	m_TimeText.setFillColor(Color::White);
	m_TimeText.setPosition(resolution.x - 150, 0);
	m_TimeText.setString("------");

	// Level
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(75);
	m_LevelText.setFillColor(Color::White);
	m_LevelText.setPosition(25, 0);
	m_LevelText.setString("1");
}

// Display the collision text with fire
void Hud::updateFireCollision() 
{
	m_SetHazardText.setString("Ouch! Hit by fire!");
	hazardMessageTimer.restart();
}

// Display the collision text with water
void Hud::updateWaterCollision() 
{
	m_SetHazardText.setString("Brrr! Slipped into water!");
	hazardMessageTimer.restart();
}

/*void Hud::updatePlayerDeath()
{
	m_SetHazardText.setString("Oh no! You died!");
}

void Hud::updateLevelCompletion() 
{
	m_SetHazardText.setString("Level Complete! Well done!");
}*/

Text Hud::getMessage()
{
	return m_StartText;
}

Text Hud::getHazardMessage() 
{
	return m_SetHazardText;
}

Text Hud::getLevel()
{
	return m_LevelText;
}

Text Hud::getTime()
{
	return m_TimeText;
}

void Hud::setLevel(String text)
{
	m_LevelText.setString(text);
}

void Hud::setTime(String text)
{
	m_TimeText.setString(text);
}

// Handle the timer for hazard text
void Hud::update(float dt) {
	if (hazardMessageTimer.getElapsedTime().asSeconds() > 2) { 
		m_SetHazardText.setString(""); // Clear the message after 2 seconds
	}
}