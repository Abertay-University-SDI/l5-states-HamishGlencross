#pragma once
#include "Framework/GameObject.h"
#include "Switch.h"

class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;

    void setSwitch(Switch* switchObject) { m_switchPointer = switchObject; }
    void setFlag(GameObject* flagObject) { m_flagPointer = flagObject; }

    void setWantsEndGame(bool endGame) { m_wantsToEndGame = endGame; }
    bool getWantsEndGame() { return m_wantsToEndGame; }

private:
    sf::Texture m_texture;
    sf::Vector2f m_acceleration;
    sf::Vector2f m_oldPosition;

    Switch* m_switchPointer;
    GameObject* m_flagPointer;

    bool m_isOnGround = false;

    bool m_wantsToEndGame = false;

    const float GRAVITY = 10.f;
    const float SPEED = 10.f;
    const float JUMP_FORCE = 5.0f;
    const float COEFF_RESTITUTION = 0.9f;
    const float FRICTION = 0.95f;

    void jump(float jumpForce);
};

