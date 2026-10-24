#include "pacman/Ghost.hpp"

Ghost::Ghost(sf::Color color)
    : shape(12.f),
      currentDirection(1, 0),
      tilePosition(0, 0),
      screenPosition(0.f, 0.f),
      speed(80.f)
{
    shape.setFillColor(color);
    shape.setOrigin(12.f, 12.f);
}

void Ghost::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void Ghost::update(float deltaTime) {

    screenPosition.x += currentDirection.x * speed * deltaTime;
    screenPosition.y += currentDirection.y * speed * deltaTime;

    shape.setPosition(screenPosition);

}

void Ghost::setStartPosition(sf::Vector2i tilePosition, sf::Vector2f screenPositon) {

    this->tilePosition = tilePosition;
    this->screenPosition = screenPosition;

    shape.setPosition(screenPosition);

}

sf::Vector2i Ghost::getTilePosition() const {
    return tilePosition;
}

sf::Vector2f Ghost::getScreenPosition() const {
    return screenPosition;
}