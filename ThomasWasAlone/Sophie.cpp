#include "Sophie.h"
#include "TextureHolder.h"

Sophie::Sophie() {
    // Associate a texture with the sprite
    m_Sprite = Sprite(TextureHolder::GetTexture("graphics/sophie.png"));

    m_JumpDuration = .25;
}

bool Sophie::handleInput() {
    m_JustJumped = false;

    // Start a jump if not already jumping
    // but only if standing on a block (not falling)
    if (Keyboard::isKeyPressed(Keyboard::I)) {
        if (!m_IsJumping && !m_IsFalling) {
            m_IsJumping = true;
            m_TimeThisJump = 0;
            m_JustJumped = true;
        }
    }
    else {
        m_IsJumping = false;
        m_IsFalling = true;
    }

    if (Keyboard::isKeyPressed(Keyboard::J))
    {
        m_LeftPressed = true;
    }
    else
    {
        m_LeftPressed = false;
    }


    if (Keyboard::isKeyPressed(Keyboard::L))
    {
        m_RightPressed = true;
    }
    else
    {
        m_RightPressed = false;
    }

    return m_JustJumped;
}


