#include "header.h"
#include <ctime>
#include <cstdlib>

// Function prototypes for main game logic
void playerTakeTurn(PlayerBoard& playerBoard, PlayerBoard& enemyBoard);
void computerTakeTurn(PlayerBoard& playerBoard, PlayerBoard& enemyBoard);
bool checkWin(const PlayerBoard& playerBoard);
void printWelcomeMessage();
void playGame(PlayerBoard& player1, PlayerBoard& player2, bool againstComputer);

int main() {
    PlayerBoard player1, player2;
    bool againstComputer;

    printWelcomeMessage();

    // Ask the user if they want to play against the computer
    char choice;
    std::cout << "Do you want to play against the computer? (y/n): ";
    std::cin >> choice;
    againstComputer = (choice == 'y' || choice == 'Y');

    // Initialize both players' fleets
    initFleet(player1);
    initFleet(player2);

    // Set up boards with ships
    boardSetup(player1, player2);

    // Play the game
    playGame(player1, player2, againstComputer);

    return 0;
}

void playerTakeTurn(PlayerBoard& playerBoard, PlayerBoard& enemyBoard) {
    std::string target;
    int row, col;
    bool validShot = false;

    while (!validShot) {
        std::cout << "Enter your target (e.g., A5): ";
        std::cin >> target;
        row = toupper(target[0]) - 'A';
        col = target[1] - '1';

        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            if (enemyBoard.board[row][col] == 'S') {
                std::cout << "Hit!\n";
                enemyBoard.board[row][col] = 'X';
                validShot = true;
            } else if (enemyBoard.board[row][col] == ' ') {
                std::cout << "Miss.\n";
                enemyBoard.board[row][col] = 'O';
                validShot = true;
            } else {
                std::cout << "You have already shot there. Try again.\n";
            }
        } else {
            std::cout << "Invalid target. Try again.\n";
        }
    }
}

void computerTakeTurn(PlayerBoard& playerBoard, PlayerBoard& enemyBoard) {
    int row, col;
    bool validShot = false;

    while (!validShot) {
        row = rand() % BOARD_SIZE;
        col = rand() % BOARD_SIZE;

        if (playerBoard.board[row][col] == 'S') {
            std::cout << "Computer hit at " << char('A' + row) << (col + 1) << "!\n";
            playerBoard.board[row][col] = 'X';
            validShot = true;
        } else if (playerBoard.board[row][col] == ' ') {
            std::cout << "Computer missed at " << char('A' + row) << (col + 1) << ".\n";
            playerBoard.board[row][col] = 'O';
            validShot = true;
        }
    }
}

bool checkWin(const PlayerBoard& playerBoard) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (playerBoard.board[i][j] == 'S') {
                return false;
            }
        }
    }
    return true;
}

void printWelcomeMessage() {
    std::cout << "Welcome to Battleship!\n";
    std::cout << "There are 5 ships in the fleet:\n";
    std::cout << "1. Carrier (5 cells)\n";
    std::cout << "2. Battleship (4 cells)\n";
    std::cout << "3. Cruiser (3 cells)\n";
    std::cout << "4. Submarine (3 cells)\n";
    std::cout << "5. Destroyer (2 cells)\n";
    std::cout << "Sink all enemy ships to win the game!\n\n";
}

void playGame(PlayerBoard& player1, PlayerBoard& player2, bool againstComputer) {
    bool gameOver = false;
    bool playerTurn = true;

    srand(time(0)); // Seed for random number generation

    while (!gameOver) {
        displayBoards(player1, player2);

        if (playerTurn) {
            std::cout << "Player's turn:\n";
            playerTakeTurn(player1, player2);
            if (checkWin(player2)) {
                std::cout << "Player wins!\n";
                gameOver = true;
            }
        } else {
            if (againstComputer) {
                std::cout << "Computer's turn:\n";
                computerTakeTurn(player2, player1);
            } else {
                std::cout << "Enemy player's turn:\n";
                playerTakeTurn(player2, player1);
            }
            if (checkWin(player1)) {
                std::cout << (againstComputer ? "Computer" : "Enemy player") << " wins!\n";
                gameOver = true;
            }
        }

        playerTurn = !playerTurn;
    }
}
