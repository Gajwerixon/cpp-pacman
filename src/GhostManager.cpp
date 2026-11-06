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