#pragma once

#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Framework/Collision.h"
#include "Switch.h"

class Level1 : BaseLevel {
public:
	Level1(sf::RenderWindow& window, Input& input, GameState& gameState);
	~Level1() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

	void setWantsToPause(bool paused) { m_isPaused = paused; }
	bool getWantsToPause() { return m_isPaused; }

private:
	// Default functions for rendering to the screen.

	// Default variables for level class.
	TileMap m_tileMap;

	Player m_player;

	bool m_isPaused;

	sf::Font m_font;
	sf::Text m_pauseMenu;

	sf::Texture m_tileTexture;
	GameObject m_flag;
	Switch m_switch;
};