#include "Player.h"


Player::Player(sf::RenderWindow & window)
{
	//Animation();
	twoDimensionTopBodyPlayer.setSize(sf::Vector2f(12.25f, 12.25f));
	twoDimensionTopBodyPlayer.setPosition(sf::Vector2f(200, 200));
	twoDimensionTopBodyPlayer.setOrigin(twoDimensionTopBodyPlayer.getSize() / 2.0f);
	twoDimensionTopBodyPlayer.setOrigin(twoDimensionTopBodyPlayer.getSize() / 2.0f);
	twoDimensionTopBodyPlayer.setTexture(&texture);

	isoBodyPlayer.setSize(sf::Vector2f(12.25f, 12.25f));
	isoBodyPlayer.setPosition(convert2DToIso({ twoDimensionTopBodyPlayer.getPosition().x,twoDimensionTopBodyPlayer.getPosition().y }).first, convert2DToIso({ twoDimensionTopBodyPlayer.getPosition().x,twoDimensionTopBodyPlayer.getPosition().y }).second);
	isoBodyPlayer.setOrigin(isoBodyPlayer.getSize() / 2.0f);
	isoBodyPlayer.setTexture(&texture);
}

Player::~Player()
{
}

void Player::Update(sf::Event event, bool isWalkable)
{
	movement.x = 0.0f;
	movement.y = 0.0f;

	shiftIncreaseSpeed = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))shiftIncreaseSpeed = 2;
	diagRunSpeed = speed*deltaTime*shiftIncreaseSpeed;
	normalRunSpeed = speed*deltaTime * shiftIncreaseSpeed;
	diagSpeed = speed*deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		movement.x -= diagRunSpeed;
		movement.y += diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		movement.x += diagRunSpeed;
		movement.y += diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 17;
		movement.x -= diagRunSpeed;
		movement.y -= diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		movement.x += diagRunSpeed;
		movement.y -= diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		movement.x -= diagSpeed;
		movement.y += diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		movement.x += diagSpeed;
		movement.y += diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		movement.x -= diagSpeed;
		movement.y -= diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		movement.x += diagSpeed;
		movement.y -= diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		movement.y += normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		movement.x -= normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		movement.x += normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		movement.y -= normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		movement.y += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		movement.x -= speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		movement.x += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		movement.y -= speed*deltaTime;
	}

	twoDimensionTopBodyPlayer.move(movement.x, movement.y);
	isoBodyPlayer.setPosition(convert2DToIso({ twoDimensionTopBodyPlayer.getPosition().x, twoDimensionTopBodyPlayer.getPosition().y / 2 }).first, convert2DToIso({ twoDimensionTopBodyPlayer.getPosition().x, twoDimensionTopBodyPlayer.getPosition().y / 2 }).second);

}

void Player::Draw(sf::RenderWindow & window, bool gamePause)
{
    window.draw(isoBodyPlayer);
	window.draw(twoDimensionTopBodyPlayer);
}

pair<float, float> Player::convert2DToIso(pair<float, float> pair)
{
	return{ pair.first - pair.second, (pair.first + pair.second) / 2 };
}

pair<float, float> Player::convertIsoTo2D(pair<float, float> pair)
{
	return{ (2 * pair.second + pair.first) / 2, (2 * pair.second - pair.first) / 2 };
}

