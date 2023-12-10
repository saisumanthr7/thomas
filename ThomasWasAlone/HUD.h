#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	Font m_Font;
	Text m_StartText;
	Text m_TimeText;
	Text m_LevelText;
	Text m_SetHazardText;
	sf::Clock hazardMessageTimer;

public:
	Hud();
	Text getMessage();
	Text getLevel();
	Text getTime();
	Text getHazardMessage();

	void setLevel(String text);
	void setTime(String text);
	void update(float dt);
	
	// New methods for updating HUD elements
	void updateFireCollision();
	void updateWaterCollision();
	//void updatePlayerDeath();
	//void updateLevelCompletion();
};