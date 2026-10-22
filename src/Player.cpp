#include "pacman/Player.hpp"


Player::Player()
    : shape(12.f),
      currentDirection(1, 0),
      speed(20.f)

{
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(12.f, 12.f);
}


void Player::handleEvents(const sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {

        if (event.key.code == sf::Keyboard::Up) {
            currentDirection = sf::Vector2i(0, -1);
        } else if (event.key.code == sf::Keyboard::Right) {
            currentDirection = sf::Vector2i(1, 0);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            currentDirection = sf::Vector2i(0, 1);
        }
        else if (event.key.code == sf::Keyboard::Left) {
            currentDirection = sf::Vector2i(-1, 0);
        }
 
    }

}


void Player::render(sf::RenderWindow& window) {

    window.draw(shape);

}


void Player::update(float deltaTime) {

    screenPosition.x += currentDirection.x * speed * deltaTime;
    screenPosition.y += currentDirection.y * speed * deltaTime;

    shape.setPosition(screenPosition);

}


void Player::setStartPosition(sf::Vector2i start, sf::Vector2f startScreenPosition) {

    tilePosition = start;
    screenPosition = startScreenPosition;
    shape.setPosition(screenPosition);

}


sf::Vector2f Player::getScreenPosition() const {
    return screenPosition;
}


void Player::setTilePosition(sf::Vector2i newTilePosition) {
    tilePosition = newTilePosition;
}


sf::Vector2i Player::getTilePosition() const {
    return tilePosition;
}


bool Player::isAtTileCenter(sf::Vector2f tileCenter) const {

    float tolerance = 2.f;

    float positionX = std::abs(screenPosition.x - tileCenter.x);
    float positionY = std::abs(screenPosition.y - tileCenter.y);

    return positionX < tolerance && positionY < tolerance;

}


void Player::checkAvalibleDirections(const std::vector<sf::Vector2i> avalibleDirections) {

    int numOfAvalibleDirections = avalibleDirections.size();
    int counter = 0;

    for (const sf::Vector2i& direction : avalibleDirections) {

        if (currentDirection != direction) {
            counter += 1;
        }

    }

    if (counter == numOfAvalibleDirections) {
        currentDirection = sf::Vector2i(0, 0);
    }

}