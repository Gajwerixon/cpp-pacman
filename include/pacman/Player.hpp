#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <cmath>
#include <iostream>

class Player {

    private:
        sf::CircleShape shape;

        sf::Vector2f currentDirection;
        sf::Vector2f requestedDirection;

        sf::Vector2i tilePosition;
        sf::Vector2f screenPosition;

        float speed;
    
    public:
        Player();

        void handleEvents(const sf::Event& event);
        void render(sf::RenderWindow& window);
        void update(float deltaTime);

        void setStartPosition(sf::Vector2i tilePosition, sf::Vector2f startScreenPosition);
        
        sf::Vector2f getScreenPosition() const;
        void setTilePosition(sf::Vector2i newTilePosition);
};