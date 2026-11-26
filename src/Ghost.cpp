#include "pacman/Ghost.hpp"

#include <iostream>
#include <cmath>

// ========================================
// Constructor and Initialization
// ========================================

Ghost::Ghost(char type, sf::Color color, GhostStatus status)
    : type(type),
      shape(12.f),
      currentDirection(1, 0),
      tilePosition(0, 0),
      screenPosition(0.f, 0.f),
      speed(80.f),
      lastDecisionTile(0, 0),
      lastDirection(0, 0),
      status(status)
{
    shape.setFillColor(color);
    shape.setOrigin(12.f, 12.f);
}

void Ghost::setStartPosition(sf::Vector2i tilePosition, sf::Vector2f screenPosition)
{

    this->tilePosition = tilePosition;
    this->screenPosition = screenPosition;

    shape.setPosition(screenPosition);
}

// ========================================
// Rendering
// ========================================

void Ghost::render(sf::RenderWindow &window) const
{
    window.draw(shape);
}

// ========================================
// Update and Movement
// ========================================

void Ghost::update(float deltaTime, const Maze &maze, GhostMode mode, sf::Vector2i targetTile, bool reverseGhost)
{
    switch (status)
    {
    case GhostStatus::Active:
        updateActive(deltaTime, maze, mode, targetTile, reverseGhost);
        break;
    case GhostStatus::InHouse:
        updateInHouse(deltaTime, maze);
        break;
    case GhostStatus::Eaten:
        updateEaten(deltaTime, maze, targetTile);
        break;
    }
}

void Ghost::updateActive(float deltaTime, const Maze &maze, GhostMode mode, sf::Vector2i targetTile, bool reverseGhost)
{
    // Move the Ghost on the screen
    move(deltaTime, maze);

    // After mode's change (in most cases) Ghost should reverse the currentDirection
    if (handleReversal(maze, reverseGhost))
    {
        return;
    }

    // Handle tunel
    if (handleTunnel(maze))
    {
        return;
    }

    // Handle special zones
    if (handleSpecialZones(maze))
    {
        return;
    }

    // Only choose a new direction at the tile center and once per tile
    if (!isAtTileCenter(maze.getTileCenter(tilePosition)) || tilePosition == lastDecisionTile)
    {
        return;
    }

    lastDecisionTile = tilePosition;

    // Update the ghost's direction based on its current mode and target tile
    switch (mode)
    {
    case GhostMode::Scatter:
    case GhostMode::Chase:
        updateTargetDirection(maze.getAvailableDirections(tilePosition), targetTile);
        break;

    case GhostMode::Frightened:
        updateFrightenedDirection(maze.getAvailableDirections(tilePosition));
        break;
    }
}

void Ghost::updateInHouse(float deltaTime, const Maze &maze)
{
    // logic
}

void Ghost::updateEaten(float deltaTime, const Maze &maze, sf::Vector2i targetTile)
{
    // logic
}

void Ghost::move(float deltaTime, const Maze &maze)
{
    screenPosition.x += currentDirection.x * speed * deltaTime;
    screenPosition.y += currentDirection.y * speed * deltaTime;

    shape.setPosition(screenPosition);

    tilePosition = maze.getTilePosition(screenPosition);
}

// ========================================
// Direction and Behavior
// ========================================

bool Ghost::handleReversal(const Maze &maze, bool reverseGhost)
{
    if (reverseGhost)
    {
        shouldReverseDirection = true;
    }

    if (!shouldReverseDirection)
    {
        return false;
    }

    sf::Vector2f tileCenter = maze.getTileCenter(tilePosition);

    if (isAtTileCenter(tileCenter))
    {

        currentDirection = currentDirection * -1;
        lastDirection = currentDirection;
        shouldReverseDirection = false;

        lastDecisionTile = tilePosition;
    }

    return true;
}

void Ghost::updateTargetDirection(const std::vector<sf::Vector2i> &allowDirections, sf::Vector2i targetTile)
{

    // The Ghost cannot turn back => removing backward direction
    std::vector<sf::Vector2i> validDirections;

    for (auto direction : allowDirections)
    {

        if (direction != -currentDirection)
        {
            validDirections.push_back(direction);
        }
    }

    std::vector<int> distances;

    // Calculate distance from new potential tile to targetTile
    for (auto direction : validDirections)
    {

        sf::Vector2i distance;

        distance.x = tilePosition.x + direction.x;
        distance.y = tilePosition.y + direction.y;

        int dx = distance.x - targetTile.x;
        int dy = distance.y - targetTile.y;

        // Calcualte euclidean distance and add it into vector
        distances.push_back(dx * dx + dy * dy);
    }

    // Find minimal distance
    int minDistance = distances[0];

    for (int distance : distances)
    {
        if (distance < minDistance)
        {
            minDistance = distance;
        }
    }

    // Find add minimal values (there could be 1 or two minimal values to target tile)
    std::vector<sf::Vector2i> bestDirections;

    for (std::size_t i = 0; i < distances.size(); i++)
    {
        if (distances[i] == minDistance)
        {
            bestDirections.push_back(validDirections[i]);
        }
    }

    for (auto priorityDirection : directionOrder)
    {
        for (auto bestDirection : bestDirections)
        {
            if (priorityDirection == bestDirection)
            {
                currentDirection = priorityDirection;
                return;
            }
        }
    }
}

void Ghost::updateFrightenedDirection(const std::vector<sf::Vector2i> &allowDirections)
{
    // The Ghost cannot turn back => removing backward direction
    std::vector<sf::Vector2i> validDirections;

    for (auto direction : allowDirections)
    {

        if (direction != -currentDirection)
        {
            validDirections.push_back(direction);
        }
    }

    std::uniform_int_distribution<int> distribution(
        0, static_cast<int>(validDirections.size()) - 1);

    currentDirection = validDirections[distribution(randomGenerator)];
}

// ========================================
// Maze Interactions
// ========================================

bool Ghost::handleTunnel(const Maze &maze)
{
    if (!maze.isTunnel(tilePosition))
    {
        return false;
    }

    if (tilePosition.x == 0 && currentDirection != sf::Vector2i(1, 0))
    {

        sf::Vector2i targetTile(maze.getWidth() - 1, tilePosition.y);

        tilePosition = targetTile;
        screenPosition = maze.getTileCenter(targetTile);
    }

    if (tilePosition.x == maze.getWidth() - 1 && currentDirection != sf::Vector2i(-1, 0))
    {

        sf::Vector2i targetTile(1, tilePosition.y);

        tilePosition = targetTile;
        screenPosition = maze.getTileCenter(targetTile);
    }

    return true;
}

bool Ghost::handleSpecialZones(const Maze &maze)
{
    if (maze.isSpecialZone(tilePosition) && currentDirection.x != 0)
    {
        return true;
    }
    return false;
}

// ========================================
// Position Helpers
// ========================================

bool Ghost::isAtTileCenter(sf::Vector2f tileCenter) const
{

    float tolerance = 1.f;

    float positionX = std::abs(screenPosition.x - tileCenter.x);
    float positionY = std::abs(screenPosition.y - tileCenter.y);

    return positionX < tolerance && positionY < tolerance;
}

void Ghost::alignToTileCenter(sf::Vector2f tileCenter)
{

    if (lastDirection.x != 0)
    {
        screenPosition.x = tileCenter.x;
    }

    if (lastDirection.y != 0)
    {
        screenPosition.y = tileCenter.y;
    }

    shape.setPosition(screenPosition);
}

// ========================================
// Getters
// ========================================

char Ghost::getType() const
{
    return type;
}

sf::Vector2i Ghost::getTilePosition() const
{
    return tilePosition;
}

GhostStatus Ghost::getStatus() const
{
    return status;
}