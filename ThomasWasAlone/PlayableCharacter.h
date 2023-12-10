#pragma once
#include <SFML/Graphics.hpp>
#include "Observer.h"
#include <vector>
#include <memory>

using namespace sf;

class PlayableCharacter
{
protected:
	// Of course we will need a sprite
	Sprite m_Sprite;

	// How long does a jump last
	float m_JumpDuration;

	// Is character currently jumping or falling
	
	bool m_IsJumping;
	bool m_IsFalling;

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Has the player just initialted a jump
	bool m_JustJumped = false;

	// Private variables and functions come next
private:
	// What is the gravity
	float m_Gravity;

	const float NORMAL_JUMP_GRAVITY = m_Gravity; 

	// Gravity for the higher jump for rubber tile
	const float RUBBER_TILE_JUMP_GRAVITY = 300.0f;
	
	// Is the player on the rubber tile
	bool m_IsOnRubber;

	// How fast is the character
	float m_Speed = 400;

	// Where is the player
	Vector2f m_Position;

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	// Velocity for the jump
	Vector2f m_Velocity;

	// And a texture
	Texture m_Texture;

	// New member variable to track activation state
	bool m_IsActive;

	std::vector<std::shared_ptr<Observer>> observers;

	// All our public functions will come next
public:

	void spawn(Vector2f startPosition, float gravity);

	// This is a pure virtual function
	bool virtual handleInput() = 0;
	// This class is now abstract and cannot be instantiated

	// Where is the player
	FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Make the character stand firm
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	// Where is the center of the character
	Vector2f getCenter();

	// We will call this function once every frame
	void update(float elapsedTime);

	// Methods for observer pattern to attach, detach and notify the observer of any changes in subject
	void attachObserver(std::shared_ptr<Observer> observer);
	void detachObserver(std::shared_ptr<Observer> observer);
	void notifyObservers(EventType event);

	// Handle the higher jump for the rubber tile
	void jumpHigher();

	// Method to activate the character
	void activate();

	bool isActive() const;

	void deactivate();
};
