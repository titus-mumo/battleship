#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>

const int BOARD_SIZE = 10;
const int FLEET_SIZE = 5;
const int CARRIER_SIZE = 5;
const int BATTLESHIP_SIZE = 4;
const int CRUISER_SIZE = 3;
const int SUBMARINE_SIZE = 3;
const int DESTROYER_SIZE = 2;

struct Point {
    int row;
    int col;
};

struct Ship {
    std::string name;
    int size;
    int hitCount;
    std::vector<Point> positions;
};

struct PlayerBoard {
    char board[BOARD_SIZE][BOARD_SIZE];
    Ship fleet[FLEET_SIZE];
};

void displayBoards(const PlayerBoard& player, const PlayerBoard& enemy);
void initFleet(PlayerBoard& playerBoard);
void boardSetup(PlayerBoard& player1, PlayerBoard& player2);
void placeShip(PlayerBoard& playerBoard, int shipIndex);
void getValidShipInfo(int& row, int& col, char& orientation, const PlayerBoard& playerBoard, int shipIndex);
bool spaceOccupied(const PlayerBoard& playerBoard, int row, int col, char orientation, int shipSize);

#endif // HEADER_H
