#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Player {

    private:
        sf::CircleShape shape;
    
    public:
        Player();

        void handleEvents();
        void render(sf::RenderWindow& window);
        void update();

};