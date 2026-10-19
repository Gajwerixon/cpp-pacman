#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

class Player {

    private:
        sf::CircleShape shape;
        sf::Vector2f direction;
        float speed = 100.f;
        sf::Vector2i tilePosition;
        sf::Vector2f screenPosition;
    
    public:
        Player();

        void handleEvents(const sf::Event& event);
        void render(sf::RenderWindow& window);
        void update(float deltaTime);

        void setStartPosition(sf::Vector2i tilePosition, sf::Vector2f screenPositon);
};