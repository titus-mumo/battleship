#include "header.h"

void displayBoards(const PlayerBoard& player, const PlayerBoard& enemy) {
    std::cout << "Your Board:                               Enemy's Board:\n";
    std::cout << "  1 2 3 4 5 6 7 8 9 10                     1 2 3 4 5 6 7 8 9 10\n";
    std::cout << "-----------------------------------------   -----------------------------------------\n";
    
    for (int i = 0; i < BOARD_SIZE; ++i) {
        char rowLabel = 'A' + i;
        std::cout << rowLabel << " |";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << player.board[i][j] << "|";
        }
        std::cout << "                   " << rowLabel << " |";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << enemy.board[i][j] << "|";
        }
        std::cout << "\n-----------------------------------------   -----------------------------------------\n";
    }
}

void initFleet(PlayerBoard& playerBoard) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            playerBoard.board[i][j] = ' ';
        }
    }

    playerBoard.fleet[0] = {"Carrier", CARRIER_SIZE, 0, {}};
    playerBoard.fleet[1] = {"Battleship", BATTLESHIP_SIZE, 0, {}};
    playerBoard.fleet[2] = {"Cruiser", CRUISER_SIZE, 0, {}};
    playerBoard.fleet[3] = {"Submarine", SUBMARINE_SIZE, 0, {}};
    playerBoard.fleet[4] = {"Destroyer", DESTROYER_SIZE, 0, {}};
}

void boardSetup(PlayerBoard& player1, PlayerBoard& player2) {
    for (int i = 0; i < FLEET_SIZE; ++i) {
        placeShip(player1, i);
        displayBoards(player1, player2);
        placeShip(player2, i);
        displayBoards(player1, player2);
    }
}

void placeShip(PlayerBoard& playerBoard, int shipIndex) {
    int row, col;
    char orientation;
    getValidShipInfo(row, col, orientation, playerBoard, shipIndex);
    Ship& ship = playerBoard.fleet[shipIndex];

    for (int i = 0; i < ship.size; ++i) {
        if (orientation == 'H') {
            playerBoard.board[row][col + i] = 'S';
            ship.positions.push_back({row, col + i});
        } else {
            playerBoard.board[row + i][col] = 'S';
            ship.positions.push_back({row + i, col});
        }
    }
}

void getValidShipInfo(int& row, int& col, char& orientation, const PlayerBoard& playerBoard, int shipIndex) {
    bool valid = false;
    do {
        std::string input;
        std::cout << "Enter the starting position and orientation (e.g., A5 H) for the " << playerBoard.fleet[shipIndex].name << ": ";
        std::cin >> input;
        row = toupper(input[0]) - 'A';
        col = input[1] - '1';
        std::cin >> orientation;
        orientation = toupper(orientation);

        if (!spaceOccupied(playerBoard, row, col, orientation, playerBoard.fleet[shipIndex].size)) {
            valid = true;
        } else {
            std::cout << "Invalid placement, please try again.\n";
        }
    } while (!valid);
}

bool spaceOccupied(const PlayerBoard& playerBoard, int row, int col, char orientation, int shipSize) {
    for (int i = 0; i < shipSize; ++i) {
        if (orientation == 'H') {
            if (col + i >= BOARD_SIZE || playerBoard.board[row][col + i] != ' ') {
                return true;
            }
        } else {
            if (row + i >= BOARD_SIZE || playerBoard.board[row + i][col] != ' ') {
                return true;
            }
        }
    }
    return false;
}
