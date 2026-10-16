#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player {

    private:
        sf::CircleShape shape;
    
    public:
        Player();

        void handleEvents(const sf::Event& event);
        void render(sf::RenderWindow& window);
        void update();

};