#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Game {
    public:
        void run();

    private:
        sf::RenderWindow window;   
};