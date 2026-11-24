#pragma once

#include <vector>
#include <map>

#include "pacman/Ghost.hpp"
#include "pacman/Maze.hpp"
#include "pacman/Player.hpp"
#include "pacman/GhostMode.hpp"

struct GhostData
{
    sf::Color color;
    sf::Vector2i scatterTarget;
};

class GhostManager
{
public:
    GhostManager(const Maze &maze, const Player &player);

    void update(float deltaTime);
    void render(sf::RenderWindow &window);

private:
    GhostMode currentMode = GhostMode::Scatter;
    GhostMode previousMode = GhostMode::Chase;

    bool reverseGhost;

    sf::Clock modeClock;
    sf::Time modeDuration = sf::seconds(10.f);

    std::map<char, GhostData> ghostConfig = {
        {'b', {sf::Color(255, 0, 0), {25, -4}}},
        {'p', {sf::Color(255, 0, 255), {2, -4}}},
        {'i', {sf::Color(0, 255, 255), {27, 31}}},
        {'c', {sf::Color(255, 165, 0), {0, 31}}}};

    std::vector<Ghost> ghosts;

    const Player &player;
    const Maze &maze;

    sf::Vector2i getChaseTarget(const Ghost &ghost) const;

    sf::Vector2i getPinkyTarget() const;
    sf::Vector2i getInkyTarget() const;
    sf::Vector2i getClaudeTarget() const;

    const Ghost &getGhost(char type) const;
};
