#pragma once

#include <vector>
#include <map>

#include "pacman/Ghost.hpp"
#include "pacman/Maze.hpp"
#include "pacman/Player.hpp"
#include "pacman/GhostMode.hpp"


struct GhostData {
    sf::Color color;
    sf::Vector2i scatterTarget;
};


class GhostManager {
public:
    GhostManager(const Maze& maze, const Player& player);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    GhostMode currentMode = GhostMode::Chase;

    std::map<char, GhostData> ghostConfig = {
        {'b', {sf::Color(255, 0, 0),   {26, 0}}},
        {'p', {sf::Color(255, 0, 255), {1, 0}}},
        {'i', {sf::Color(0, 255, 255), {26, 30}}},
        {'c', {sf::Color(255, 165, 0), {1, 30}}}
    };

    std::vector<Ghost> ghosts;

    const Player& player;
    const Maze& maze;
};
