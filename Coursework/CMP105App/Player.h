#pragma once
#include "Framework/GameObject.h"
class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;
private:
    sf::Texture m_texture;
    sf::Vector2f m_acceleration;
    sf::Vector2f m_oldPosition;
    bool m_isOnGround = false;

    const float GRAVITY = 10.f;
    const float SPEED = 10.f;
    const float JUMP_FORCE = 7.0f;
    const float COEFF_RESTITUTION = 0.9f;
    const float FRICTION = 0.95f;

    void jump(float jumpForce);
};

