#pragma once

#include <SFML/Graphics.hpp>
#include <include/pacman/GhostStatus.hpp>
#include <SFML/System/Vector2.hpp>

struct GhostConfig
{
    sf::Color color;
    GhostStatus status;
    sf::Vector2i startPosition;
    sf::Vector2i startDirection;
};