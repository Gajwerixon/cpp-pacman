#pragma once

#include <vector>
#include <map>

#include "include/pacman/Ghost.hpp"
#include "include/pacman/Maze.hpp"

class GhostManager {
public:
    GhostManager(const Maze& maze);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    std::map<char, sf::Color> ghostColors = {
        {'B', sf::Color::Red},
        {'K', sf::Color::Magenta},
        {'I', sf::Color::Cyan},
        {'C', sf::Color(255, 165, 0)}
    };

    std::vector<Ghost> ghosts;
};
