#include "pacman/Player.hpp"


Player::Player()
    : shape(12.f),
      direction(1.f, 0.f) 

{
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(20.f, 20.f);
}


void Player::handleEvents(const sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {

        if (event.key.code == sf::Keyboard::Up) {
            direction = sf::Vector2f(0.f, -1.f);
        } else if (event.key.code == sf::Keyboard::Right) {
            direction = sf::Vector2f(1.f, 0.f);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            direction = sf::Vector2(0.f, 1.f);
        }
        else if (event.key.code == sf::Keyboard::Left) {
            direction = sf::Vector2f(-1.f, 0.f);
        }
 
    }

}


void Player::render(sf::RenderWindow& window) {

    window.draw(shape);

}


void Player::update(float deltaTime) {

    shape.move(
        direction.x * speed * deltaTime,
        direction.y * speed * deltaTime
    );

}


void Player::setStartPosition(sf::Vector2i start) {
    tilePosition = start;
}