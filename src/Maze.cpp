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
        "      .   #      #   .      ",
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
    wall.setPosition(sf::Vector2f((col * tileSize), (row * tileSize)));
    walls.push_back(wall);

}

void Maze::createDot(std::size_t row, std::size_t col) {
    
    sf::CircleShape dot;
    dot.setRadius(4.f);
    dot.setFillColor(sf::Color::White);
    dot.setPosition(sf::Vector2f(
        ((col * tileSize) + tileSize / 2 - dot.getRadius()), 
        ((row * tileSize) + tileSize / 2 - dot.getRadius()))
    );
    dots.push_back(dot);

}

void Maze::createEnergizer(std::size_t row, std::size_t col) {
    
    sf::CircleShape energizer;
    energizer.setRadius(8.f);
    energizer.setFillColor(sf::Color::White);
    energizer.setPosition(sf::Vector2f(
        ((col * tileSize) + tileSize / 2 - energizer.getRadius()), 
        ((row * tileSize) + tileSize / 2 - energizer.getRadius()))
    );
    energizers.push_back(energizer);

}

void Maze::setPacmanStart(std::size_t row, std::size_t col) {
    pacmanStart = sf::Vector2i(col, row);
}