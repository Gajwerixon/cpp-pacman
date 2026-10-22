#include "pacman/Game.hpp"

Game::Game() {
    player.setStartPosition(
        maze.getPacmanStart(), 
        maze.calculateScreenPosition(maze.getPacmanStart())
    );
};


void Game::run() {
    window.create(sf::VideoMode(672, 864), "Pac-Man");

    while (window.isOpen()) {

        processEvents();
        render();
        update();

    }

}


void Game::processEvents() {

    sf::Event event;

    while (window.pollEvent(event))
    {
        
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        player.handleEvents(event);

    }
    
}


void Game::render() {

    window.clear(sf::Color::Black);

    maze.render(window);
    player.render(window);

    window.display();

}


void Game::update() {

    float deltaTime = clock.restart().asSeconds();

    updatePlayer(deltaTime);

}


void Game::updatePlayer(float deltaTime) {

    player.update(deltaTime);

    // Update the player's tile position
    sf::Vector2i tilePosition = maze.calculateTilePosition(player.getScreenPosition());

    if (tilePosition != player.getTilePosition()) {
        player.setTilePosition(tilePosition);
    }

    // Calculate the center of the player's current tile
    sf::Vector2f tileCenter = maze.calculateTileCenter(player.getTilePosition());

    // Check if the player has reached the tile center
    if (player.isAtTileCenter(tileCenter)) {
        
        std::vector<sf::Vector2i> avalibleDirections = maze.getAvalibleDirections(tilePosition);

        for (sf::Vector2i& direction : avalibleDirections) {
            std::cout << "(" << direction.x << ", " << direction.y << ")" << " ";
        }
        std::cout << "\n";

    }

}