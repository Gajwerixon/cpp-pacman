#include "pacman/GhostManager.hpp"
#include <stdexcept>

GhostManager::GhostManager(const Maze &maze, const Player &player)
    : maze(maze), player(player)
{

    for (const auto &[type, tilePosition] : maze.getGhostStart())
    {

        const GhostData &data = ghostConfig.at(type);

        Ghost ghost(type, data.color);

        ghost.setStartPosition(
            tilePosition,
            maze.getTileCenter(tilePosition));

        ghosts.push_back(ghost);
    }
}

void GhostManager::update(float deltaTime)
{

    for (auto &ghost : ghosts)
    {

        sf::Vector2i targetTile;

        if (currentMode == GhostMode::Scatter)
        {
            targetTile = ghostConfig.at(ghost.getType()).scatterTarget;
        }
        else if (currentMode == GhostMode::Chase)
        {
            targetTile = getChaseTarget(ghost);
        }

        ghost.update(deltaTime, maze, currentMode, targetTile);
    }
}

void GhostManager::render(sf::RenderWindow &window)
{

    for (const auto &ghost : ghosts)
    {
        ghost.render(window);
    }
}

sf::Vector2i GhostManager::getChaseTarget(const Ghost &ghost) const
{

    switch (ghost.getType())
    {
    case 'b':
        return player.getTilePosition();
        ;

    case 'p':
        return getPinkyTarget();

    case 'i':
        return getInkyTarget();

    case 'c':
        return getClaudeTarget();
    }

    return player.getTilePosition();
}

sf::Vector2i GhostManager::getPinkyTarget() const
{

    sf::Vector2i targetTile;

    int normalOffset = 4;
    sf::Vector2i upDirectionOffset(-4, -4);

    sf::Vector2i playerTilePosition = player.getTilePosition();
    sf::Vector2i playerCurrentDirection = player.getCurrentDirection();
    sf::Vector2i playerLastDirection = player.getLastDirection();

    if (playerCurrentDirection != sf::Vector2i(0, 0))
    {

        if (playerCurrentDirection != sf::Vector2i(0, -1))
        {

            targetTile.x = playerTilePosition.x + (playerCurrentDirection.x * normalOffset);
            targetTile.y = playerTilePosition.y + (playerCurrentDirection.y * normalOffset);
        }

        else
        {

            targetTile.x = playerTilePosition.x + upDirectionOffset.x;
            targetTile.y = playerTilePosition.y + upDirectionOffset.y;
        }
    }

    else
    {

        if (playerLastDirection != sf::Vector2i(0, -1))
        {

            targetTile.x = playerTilePosition.x + (playerLastDirection.x * normalOffset);
            targetTile.y = playerTilePosition.y + (playerLastDirection.y * normalOffset);
        }

        else
        {

            targetTile.x = playerTilePosition.x + upDirectionOffset.x;
            targetTile.y = playerTilePosition.y + upDirectionOffset.y;
        }
    }

    return targetTile;
}

sf::Vector2i GhostManager::getInkyTarget() const
{

    sf::Vector2i targetTile;

    int normalOffset = 2;
    sf::Vector2i upDirectionOffset(-2, -2);

    sf::Vector2i playerTilePosition = player.getTilePosition();
    sf::Vector2i playerCurrentDirection = player.getCurrentDirection();
    sf::Vector2i playerLastDirection = player.getLastDirection();

    sf::Vector2i blinkyTilePosition = getGhost('b').getTilePosition();

    if (playerCurrentDirection != sf::Vector2i(0, 0))
    {

        if (playerCurrentDirection != sf::Vector2i(0, -1))
        {

            targetTile.x = playerTilePosition.x + (playerCurrentDirection.x * normalOffset);
            targetTile.y = playerTilePosition.y + (playerCurrentDirection.y * normalOffset);
        }

        else
        {

            targetTile.x = playerTilePosition.x + upDirectionOffset.x;
            targetTile.y = playerTilePosition.y + upDirectionOffset.y;
        }
    }

    else
    {

        if (playerLastDirection != sf::Vector2i(0, -1))
        {

            targetTile.x = playerTilePosition.x + (playerLastDirection.x * normalOffset);
            targetTile.y = playerTilePosition.y + (playerLastDirection.y * normalOffset);
        }

        else
        {

            targetTile.x = playerTilePosition.x + upDirectionOffset.x;
            targetTile.y = playerTilePosition.y + upDirectionOffset.y;
        }
    }

    // Calculate Inky's target by reflecting the pivot across Blinky's position.    targetTile.x = targetTile.x + (targetTile.x - blinkyTilePosition.x);
    targetTile.y = targetTile.y + (targetTile.y - blinkyTilePosition.y);

    return targetTile;
}

sf::Vector2i GhostManager::getClaudeTarget() const
{

    sf::Vector2i playerTilePosition = player.getTilePosition();
    sf::Vector2i claudeTilePosition = getGhost('c').getTilePosition();

    int squareDistance = 64;

    int dx = playerTilePosition.x - claudeTilePosition.x;
    int dy = playerTilePosition.y - claudeTilePosition.y;

    int currentDistanceSquared = dx * dx + dy * dy;

    if (currentDistanceSquared < squareDistance)
    {
        return ghostConfig.at('c').scatterTarget;
    }

    return player.getTilePosition();
}

const Ghost &GhostManager::getGhost(char type) const
{
    for (const auto &ghost : ghosts)
    {
        if (ghost.getType() == type)
        {
            return ghost;
        }
    }

    throw std::runtime_error("Ghost not found");
}
