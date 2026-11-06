#include "pacman/GhostManager.hpp"

GhostManager::GhostManager(const Maze& maze, const Player& player) 
    : maze(maze), player(player)
{

    for (const auto& [type, tilePosition] : maze.getGhostStart()) {

        Ghost ghost(ghostColors.at(type));

        ghost.setStartPosition(
            tilePosition,
            maze.getTileCenter(tilePosition)
        );

        ghosts.push_back(ghost);

    }

}


void GhostManager::update(float deltatime) {

    for (auto& ghost : ghosts) {
        ghost.update(deltatime, maze, player);
    }

}


void GhostManager::GhostManager::render(sf::RenderWindow& window) {

    for (const auto& ghost : ghosts) {
        ghost.render(window);
    }

}
