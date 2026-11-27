#pragma once

#include <SFML/Graphics.hpp>
#include "pacman/GhostStatus.hpp"
#include <SFML/System/Vector2.hpp>

struct GhostsConfig
{
    sf::Color color;
    GhostStatus status;
    sf::Vector2i startDirection;
    sf::Vector2i scatterTarget;
};