#pragma once

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include "pacman/Player.hpp"
#include "Maze.hpp"
#include "GhostManager.hpp"

class Game {

    public:
        Game();
        void run();

    private:
        void processEvents();
        void render();
        void update();

        sf::RenderWindow window;
        sf::Clock clock;
        Maze maze;
        Player player;
        GhostManager ghostManager;

        void updatePlayer(float deltaTime);
        void updateGhosts(float deltaTime);
};