#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include "pacman/Player.hpp"

class Game {

    public:
        void run();

    private:
        void processEvents();
        void update();
        void render();

        sf::RenderWindow window;
        Player player;
        sf::Clock clock;

};