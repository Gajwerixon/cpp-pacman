#include "pacman/GhostManager.hpp"

GhostManager::GhostManager(const Maze& maze) {

    for (const auto& [type, tilePosition] : maze.getGhostStart()) {

        Ghost ghost(ghostColors.at(type));

        ghost.setStartPosition(
            tilePosition,
            maze.getTileCenter(tilePosition)
        );

        ghosts.push_back(ghost);

    }

}


void GhostManager::GhostManager::update(float deltatime) {

    for (auto& ghost : ghosts) {
        ghost.update(deltatime);
    }

}


void GhostManager::GhostManager::render(sf::RenderWindow& window) {

    for (auto& ghost : ghosts) {
        ghost.render(window);
    }

}
