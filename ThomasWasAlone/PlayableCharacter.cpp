#include "PlayableCharacter.h"

void PlayableCharacter::spawn(Vector2f startPosition, float gravity)
{
	// Place the player at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Initialize the gravity
	m_Gravity = gravity;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

	m_IsActive = false;
}

void PlayableCharacter::update(float elapsedTime)
{

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}


	// Handle Rubber tile jumping
	if (m_IsOnRubber)
	{
		m_TimeThisJump += elapsedTime;

		if (m_TimeThisJump < m_JumpDuration)
		{
			// Move up higher
			m_Position.y -= m_Gravity * 4 * elapsedTime;

		}
		else
		{
			m_IsOnRubber = false;
			m_IsFalling = true;
		}
	}

	// Handle Jumping
	if (m_IsJumping)
	{
		// Update how long the jump has been going
		m_TimeThisJump += elapsedTime;

		// Is the jump going upwards
		if (m_TimeThisJump < m_JumpDuration)
		{
			// Move up at twice gravity
			m_Position.y -= m_Gravity * 2 * elapsedTime;
		}
		else
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}

	}

	// Apply gravity
	if (m_IsFalling)
	{
		m_Position.y += m_Gravity * elapsedTime;
	}

	// Update the rect for all body parts
	FloatRect r = getPosition();


	// Feet
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width - 2;
	m_Right.top = r.top + r.height * .35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .5;
	m_Left.width = 1;
	m_Left.height = r.height * .3;

	// Move the sprite into position
	m_Sprite.setPosition(m_Position);

}

FloatRect PlayableCharacter::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

FloatRect PlayableCharacter::getFeet()
{
	return m_Feet;
}

FloatRect PlayableCharacter::getHead()
{
	return m_Head;
}

FloatRect PlayableCharacter::getLeft()
{
	return m_Left;
}

FloatRect PlayableCharacter::getRight()
{
	return m_Right;
}

Sprite PlayableCharacter::getSprite()
{
	return m_Sprite;
}



void PlayableCharacter::stopFalling(float position)
{
	m_Position.y = position - getPosition().height;
	m_Sprite.setPosition(m_Position);
	m_IsFalling = false;
}

void PlayableCharacter::stopRight(float position)
{

	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopLeft(float position)
{
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopJump()
{
	// Stop a jump early 
	m_IsJumping = false;
	m_IsFalling = true;
}

// Attach an observer
void PlayableCharacter::attachObserver(std::shared_ptr<Observer> observer) {
	observers.push_back(observer);
}

// Detach an observer
void PlayableCharacter::detachObserver(std::shared_ptr<Observer> observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

// Notify all observers of an event
void PlayableCharacter::notifyObservers(EventType event) {
	for (auto& observer : observers) {
		observer->onNotify(event);
	}
}

// Handle the higher jump for the rubber tile
void PlayableCharacter::jumpHigher()
{
	// Check if not already jumping
	if (!m_IsJumping)
	{
		m_IsJumping = true;
		m_IsOnRubber = true;
		m_TimeThisJump = 0;
		m_Gravity = RUBBER_TILE_JUMP_GRAVITY; 
	}
}

void PlayableCharacter::activate() {
	m_IsActive = true;
}

bool PlayableCharacter::isActive() const {
	return m_IsActive;
}

void PlayableCharacter::deactivate() {
	m_IsActive = false;
}

