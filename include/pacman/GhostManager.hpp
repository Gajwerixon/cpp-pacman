#pragma once

#include <vector>
#include <map>

#include "pacman/Ghost.hpp"
#include "pacman/Maze.hpp"

class GhostManager {
public:
    GhostManager(const Maze& maze);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    std::map<char, sf::Color> ghostColors = {
        {'b', sf::Color::Red},
        {'p', sf::Color::Magenta},
        {'i', sf::Color::Cyan},
        {'c', sf::Color(255, 165, 0)}
    };

    std::vector<Ghost> ghosts;
};
