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
    // Create wall
}

void Maze::createDot(std::size_t row, std::size_t col) {
    // Create wall
}

void Maze::createEnergizer(std::size_t row, std::size_t col) {
    // Create wall
}

void Maze::setPacmanStart(std::size_t row, std::size_t col) {
    // Create wall
}