#include "pacman/Player.hpp"


Player::Player():shape(20.f) {

    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(20.f, 20.f);

}


void Player::handleEvents() {



};


void Player::render(sf::RenderWindow& window) {

    window.draw(shape);

}


void Player::update() {




}