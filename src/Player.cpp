#include "pacman/Player.hpp"


Player::Player():shape(20.f) {

    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(20.f, 20.f);

}


void Player::handleEvents(const sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {

        if (event.key.code == sf::Keyboard::Up) {
            shape.move(0.f, -5.f);
        } else if (event.key.code == sf::Keyboard::Right) {
            shape.move(5.f, 0.f);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            shape.move(0.f, 5.f);
        }
        else if (event.key.code == sf::Keyboard::Left) {
            shape.move(-5.f, 0.f);
        }
 
    }

}


void Player::render(sf::RenderWindow& window) {

    window.draw(shape);

}


void Player::update() {




}