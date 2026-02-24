#include "Player.h"
#include <iostream>

Player::Player()
{
	if (!m_texture.loadFromFile("gfx/dino1.png"))
		std::cerr << "No dino texture. sad";

	setTexture(&m_texture);
	setSize({ 36,36 });
	setCollisionBox({ {6,6}, { 24,25 } });
	setPosition({ 50,0 });
	m_isOnGround = false;
	setTextureRect({ { 0,0 }, { 24,24 } });
}

void Player::handleInput(float dt)
{
	m_acceleration = { 0,0 };

	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
		m_acceleration.x -= SPEED;
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
		m_acceleration.x += SPEED;
	if (m_input->isPressed(sf::Keyboard::Scancode::Space) && m_isOnGround)
		jump(JUMP_FORCE);

	if (m_input->isKeyDown(sf::Keyboard::Scancode::R))	// Reset (for debugging)
	{
		setPosition({ 50,0 });
		m_velocity = { 0,0 };

		m_isOnGround = false;
	}

	if (m_input->isPressed(sf::Keyboard::Scancode::F))
	{
		if ((getPosition() - m_flagPointer->getPosition()).lengthSquared() < 1000)//spoooky bad magic number
		{
			std::cout << "Pressed flag\n";
			m_wantsToEndGame = true;
		}

		if ((getPosition() - m_switchPointer->getPosition()).lengthSquared() < 1000)
		{
			std::cout << "Pressed switch\n";
			m_switchPointer->toggle();
		}
	}
}

void Player::update(float dt)
{
	m_oldPosition = getPosition();
	// newtonian model
	m_acceleration.y += GRAVITY;
	m_velocity += dt * m_acceleration;
	m_velocity.x *= FRICTION;
	move(m_velocity);
}

void Player::collisionResponse(GameObject& collider)
{
	sf::FloatRect playerCollider = getCollisionBox();
	sf::FloatRect wallBounds = collider.getCollisionBox();

	auto overlap = playerCollider.findIntersection(wallBounds);
	if (!overlap) return;

	if (m_oldPosition.y - getSize().y < collider.getPosition().y)
	{
		//floor collision

		m_isOnGround = true;

		if (m_velocity.y > 0)
		{
			m_velocity.y = 0;
			setPosition({ getPosition().x, collider.getPosition().y - getCollisionBox().size.y });
		}
	}
	else if (m_oldPosition.y > collider.getPosition().y + collider.getSize().y)
	{
		//ceiling collision

		m_velocity.y *= -COEFF_RESTITUTION;
	}
	else
	{
		//horizontal collision

		std::cout << "Horizontal Collision\n";

		m_velocity.x *= -COEFF_RESTITUTION;

		if (playerCollider.position.x < wallBounds.position.x)
		{
			setPosition({ getPosition().x - overlap->size.x, getPosition().y });
		}
		else
			setPosition({ getPosition().x + overlap->size.x, getPosition().y });
	}
}

void Player::jump(float jumpForce)
{
	std::cout << "jump\n";

	m_isOnGround = false;
	m_velocity.y -= jumpForce;
}