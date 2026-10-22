#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <cmath>
#include <iostream>
#include <algorithm>

class Player {

    private:
        sf::CircleShape shape;

        sf::Vector2i currentDirection;
        sf::Vector2i requestedDirection;

        sf::Vector2i tilePosition;
        sf::Vector2f screenPosition;

        float speed;

        bool canMoveInDirection(
            sf::Vector2i direction,
            const std::vector<sf::Vector2i>& availableDirections
        );
    
    public:
        Player();

        void handleEvents(const sf::Event& event);
        void render(sf::RenderWindow& window);
        void update(float deltaTime);

        void setStartPosition(sf::Vector2i tilePosition, sf::Vector2f startScreenPosition);
        
        sf::Vector2f getScreenPosition() const;
        void setTilePosition(sf::Vector2i newTilePosition);

        sf::Vector2i getTilePosition() const;

        bool isAtTileCenter(sf::Vector2f tileCenter) const;
        
        void checkAvalibleDirections(const std::vector<sf::Vector2i> avalibleDirections);

        bool changesMovementAxis() const;

        void alignToTileCenter(sf::Vector2f tileCenter);
};