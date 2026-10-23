#include <pacman/Maze.hpp>

Maze::Maze()
    : mazeLayout({
        "############################",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#0#  #.#   #.##.#   #.#  #0#",
        "#.####.#####.##.#####.####.#",
        "#..........................#",
        "#.####.##.########.##.####.#",
        "#.####.##.########.##.####.#",
        "#......##....##....##......#",
        "######.##### ## #####.######",
        "     #.##### ## #####.#     ",
        "     #.##          ##.#     ",
        "     #.## ######## ##.#     ",
        "######.## #      # ##.######",
        "TTTTTT.   #      #   .TTTTTT",
        "######.## #      # ##.######",
        "     #.## ######## ##.#     ",
        "     #.##          ##.#     ",
        "     #.## ######## ##.#     ",
        "######.## ######## ##.######",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#.####.#####.##.#####.####.#",
        "#0..##.......P .......##..0#",
        "###.##.##.########.##.##.###",
        "###.##.##.########.##.##.###",
        "#......##....##....##......#",
        "#.##########.##.##########.#",
        "#.##########.##.##########.#",
        "#..........................#",
        "############################"
    })

    {
        createMaze();
    };


void Maze::render(sf::RenderWindow& window) {

    for (const sf::RectangleShape& wall : walls) {
        window.draw(wall);
    }

    for (const sf::CircleShape& dot : dots) {
        window.draw(dot);
    }

    for (const sf::CircleShape& energizer : energizers) {
        window.draw(energizer);
    }

};


void Maze::createMaze() {

    for (std::size_t row = 0; row < mazeLayout.size(); row++) {

        for (std::size_t col = 0; col < mazeLayout[row].size(); col++) {

            switch (mazeLayout[row][col]) {
            case '#':
                createWall(row, col);
                break;
            case '.':
                createDot(row, col);
                break;
            case '0':
                createEnergizer(row, col);
                break;
            case 'P':
                setPacmanStart(row, col);
                break;
            
            default:
                break;
            }

        }

    }

}


void Maze::createWall(std::size_t row, std::size_t col) {
    
    sf::RectangleShape wall;
    wall.setSize(sf::Vector2f(tileSize, tileSize));
    wall.setFillColor(sf::Color::Blue);
    wall.setPosition(sf::Vector2f(
        (col * tileSize), 
        ((row * tileSize) + offsetY * tileSize)
    ));
    walls.push_back(wall);

}


void Maze::createDot(std::size_t row, std::size_t col) {
    
    sf::CircleShape dot;
    dot.setRadius(4.f);
    dot.setFillColor(sf::Color::White);
    dot.setPosition(sf::Vector2f(
        ((col * tileSize) + tileSize / 2 - dot.getRadius()), 
        ((row * tileSize) + tileSize / 2 - dot.getRadius() + offsetY * tileSize )
    ));
    dots.push_back(dot);

}


void Maze::createEnergizer(std::size_t row, std::size_t col) {
    
    sf::CircleShape energizer;
    energizer.setRadius(8.f);
    energizer.setFillColor(sf::Color::White);
    energizer.setPosition(sf::Vector2f(
        ((col * tileSize) + tileSize / 2 - energizer.getRadius()), 
        ((row * tileSize) + tileSize / 2 - energizer.getRadius() + offsetY * tileSize)
    ));
    energizers.push_back(energizer);

}


void Maze::setPacmanStart(std::size_t row, std::size_t col) {
    pacmanStart = sf::Vector2i(col, row);
}


sf::Vector2i Maze::getPacmanStart() const {
    return pacmanStart;
};


sf::Vector2f Maze::getScreenPosition(sf::Vector2i tilePosition) {
    
    sf::Vector2f screenPostion;
    screenPostion.x = tilePosition.x * tileSize + tileSize / 2;
    screenPostion.y = tilePosition.y * tileSize + offsetY * tileSize + tileSize / 2;
    return screenPostion;

};


sf::Vector2i Maze::getTilePosition(sf::Vector2f screenPosition) {

    sf::Vector2i tilePosition;
    tilePosition.x = screenPosition.x / tileSize;
    tilePosition.y = (screenPosition.y - (offsetY * tileSize)) / tileSize;
    return tilePosition;

}


sf::Vector2f Maze::getTileCenter(sf::Vector2i tilePosition) {

    sf::Vector2f tileCenter;
    tileCenter.x = (tilePosition.x * tileSize) + tileSize / 2;
    tileCenter.y = (tilePosition.y * tileSize) + (offsetY * tileSize) + tileSize / 2;
    return tileCenter;

}


std::vector<sf::Vector2i> Maze::getAvailableDirections(sf::Vector2i tilePosition) {

    std::vector<sf::Vector2i> directions = {
        {0, -1},
        {1, 0},
        {0, 1},
        {-1, 0}
    };
    std::vector<sf::Vector2i> avalibleDirections;

    // Loop for every direction
    for (const sf::Vector2i& direction : directions) {

        // Create newTilePosition
        sf::Vector2i newTilePosition = tilePosition + direction;

        // If on the newPosition is not a wall
        if (mazeLayout[newTilePosition.y][newTilePosition.x] != '#') {
            avalibleDirections.push_back(direction);
        };

    }

    return avalibleDirections;

}


bool Maze::isTunnel(sf::Vector2i tilePosition) const {
    return mazeLayout[tilePosition.y][tilePosition.x] == 'T';
}

int Maze::getWidth(void) const {
    return mazeLayout[0].size();
}