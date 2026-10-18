#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include "pacman/Player.hpp"
#include "Maze.hpp"

class Game {

    public:
        void run();

    private:
        void processEvents();
        void render();
        void update();

        sf::RenderWindow window;
        Player player;
        sf::Clock clock;
        Maze maze;

};