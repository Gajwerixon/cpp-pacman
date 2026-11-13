#include "pacman/GhostManager.hpp"

GhostManager::GhostManager(const Maze& maze, const Player& player) 
    : maze(maze), player(player)
{

    for (const auto& [type, tilePosition] : maze.getGhostStart()) {

        const GhostData& data = ghostConfig.at(type);

        Ghost ghost(type, data.color);

        ghost.setStartPosition(
            tilePosition,
            maze.getTileCenter(tilePosition)
        );

        ghosts.push_back(ghost);

    }

}


void GhostManager::update(float deltaTime) {

    for (auto& ghost : ghosts) {

        sf::Vector2i targetTile;

        if (currentMode == GhostMode::Scatter) {
            targetTile = ghostConfig.at(ghost.getType()).scatterTarget;
        }
        else if (currentMode == GhostMode::Chase) {
            targetTile = player.getTilePosition();
        }

        ghost.update(deltaTime, maze, currentMode, targetTile);
    }
    
}


void GhostManager::GhostManager::render(sf::RenderWindow& window) {

    for (const auto& ghost : ghosts) {
        ghost.render(window);
    }

}
