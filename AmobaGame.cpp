#include "AmobaGame.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

AmobaGame::AmobaGame(int size)
        : board(size, std::vector<int>(size, 0)), currentPlayer(1), player1Wins(0), player2Wins(0) {
    std::srand(std::time(nullptr));
}

bool AmobaGame::placePiece(int x, int y) {
    if (x >= 0 && x < board.size() && y >= 0 && y < board.size() && board[x][y] == 0) {
        board[x][y] = currentPlayer;
        if (checkWin()) {
            if (currentPlayer == 1) {
                player1Wins++;
            } else {
                player2Wins++;
            }
        }
        currentPlayer = 3 - currentPlayer;
        return true;
    }
    return false;
}

void AmobaGame::aiMove() {
    int x, y;

    // Ellenőrizze, hogy tud-e nyerni
    if (canWin(2, x, y)) {
        placePiece(x, y);
        return;
    }

    // Ellenőrizze, hogy a játékos tud-e nyerni, és akadályozza meg
    if (canWin(1, x, y)) {
        placePiece(x, y);
        return;
    }

    // Ellenőrizze, hogy a játékosnak van-e három vagy négy egymás mellett álló, és akadályozza meg
    if (blockOpponentThreat(x, y)) {
        placePiece(x, y);
        return;
    }

    // Próbáljon meg három vagy négy egymás melletti sajátot létrehozni
    if (createOwnThreat(2, x, y)) {
        placePiece(x, y);
        return;
    }

    // Véletlenszerű lépés, ha nincs nyerési lehetőség
    do {
        x = std::rand() % board.size();
        y = std::rand() % board.size();
    } while (board[x][y] != 0);

    placePiece(x, y);
}

bool AmobaGame::createOwnThreat(int player, int& x, int& y) {
    int size = board.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != 0) continue;

            if (j + 1 < size && board[i][j + 1] == player && (j == 0 || board[i][j - 1] == 0)) {
                x = i;
                y = j;
                return true;
            }

            if (i + 1 < size && board[i + 1][j] == player && (i == 0 || board[i - 1][j] == 0)) {
                x = i;
                y = j;
                return true;
            }

            if (i + 1 < size && j + 1 < size && board[i + 1][j + 1] == player && (i == 0 || j == 0 || board[i - 1][j - 1] == 0)) {
                x = i;
                y = j;
                return true;
            }

            if (i - 1 >= 0 && j + 1 < size && board[i - 1][j + 1] == player && (i == size - 1 || j == 0 || board[i + 1][j - 1] == 0)) {
                x = i;
                y = j;
                return true;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != 0) continue;

            if (j + 2 < size && board[i][j + 1] == player && board[i][j + 2] == player) {
                x = i;
                y = j;
                return true;
            }

            if (i + 2 < size && board[i + 1][j] == player && board[i + 2][j] == player) {
                x = i;
                y = j;
                return true;
            }

            if (i + 2 < size && j + 2 < size && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player) {
                x = i;
                y = j;
                return true;
            }

            if (i - 2 >= 0 && j + 2 < size && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player) {
                x = i;
                y = j;
                return true;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != 0) continue;

            if (j + 1 < size && board[i][j + 1] == player) {
                x = i;
                y = j;
                return true;
            }

            if (i + 1 < size && board[i + 1][j] == player) {
                x = i;
                y = j;
                return true;
            }

            if (i + 1 < size && j + 1 < size && board[i + 1][j + 1] == player) {
                x = i;
                y = j;
                return true;
            }

            if (i - 1 >= 0 && j + 1 < size && board[i - 1][j + 1] == player) {
                x = i;
                y = j;
                return true;
            }
        }
    }

    return false;
}

bool AmobaGame::canWin(int player, int& x, int& y) {
    int size = board.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != 0) continue;
            board[i][j] = player;
            bool win = checkWin();
            board[i][j] = 0;
            if (win) {
                x = i;
                y = j;
                return true;
            }
        }
    }
    return false;
}

bool AmobaGame::blockOpponentThreat(int& x, int& y) {
    int size = board.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != 0) continue;

            if (j + 3 < size && board[i][j + 1] == 1 && board[i][j + 2] == 1 && board[i][j + 3] == 1) {
                if ((j == 0 || board[i][j - 1] == 0) && (j + 4 == size || board[i][j + 4] == 0)) {
                    x = i;
                    y = j;
                    return true;
                }
            }
            if (j + 4 < size && board[i][j + 1] == 1 && board[i][j + 2] == 0 && board[i][j + 3] == 1 && board[i][j + 4] == 1) {
                x = i;
                y = j + 2;
                return true;
            }

            if (i + 3 < size && board[i + 1][j] == 1 && board[i + 2][j] == 1 && board[i + 3][j] == 1) {
                if ((i == 0 || board[i - 1][j] == 0) && (i + 4 == size || board[i + 4][j] == 0)) {
                    x = i;
                    y = j;
                    return true;
                }
            }
            if (i + 4 < size && board[i + 1][j] == 1 && board[i + 2][j] == 0 && board[i + 3][j] == 1 && board[i + 4][j] == 1) {
                x = i + 2;
                y = j;
                return true;
            }

            if (i + 3 < size && j + 3 < size && board[i + 1][j + 1] == 1 && board[i + 2][j + 2] == 1 && board[i + 3][j + 3] == 1) {
                if ((i == 0 || j == 0 || board[i - 1][j - 1] == 0) && (i + 4 == size || j + 4 == size || board[i + 4][j + 4] == 0)) {
                    x = i;
                    y = j;
                    return true;
                }
            }
            if (i + 4 < size && j + 4 < size && board[i + 1][j + 1] == 1 && board[i + 2][j + 2] == 0 && board[i + 3][j + 3] == 1 && board[i + 4][j + 4] == 1) {
                x = i + 2;
                y = j + 2;
                return true;
            }

            if (i - 3 >= 0 && j + 3 < size && board[i - 1][j + 1] == 1 && board[i - 2][j + 2] == 1 && board[i - 3][j + 3] == 1) {
                if ((i - 4 < 0 || j + 4 == size || board[i - 4][j + 4] == 0) && (i == size - 1 || j == 0 || board[i + 1][j - 1] == 0)) {
                    x = i;
                    y = j;
                    return true;
                }
            }
            if (i - 4 >= 0 && j + 4 < size && board[i - 1][j + 1] == 1 && board[i - 2][j + 2] == 0 && board[i - 3][j + 3] == 1 && board[i - 4][j + 4] == 1) {
                x = i - 2;
                y = j + 2;
                return true;
            }
        }
    }
    return false;
}

int AmobaGame::getCurrentPlayer() const {
    return currentPlayer;
}

int AmobaGame::getPlayer1Wins() const {
    return player1Wins;
}

int AmobaGame::getPlayer2Wins() const {
    return player2Wins;
}

const std::vector<std::vector<int>>& AmobaGame::getBoard() const {
    return board;
}

const std::vector<std::pair<int, int>>& AmobaGame::getWinningCoords() const {
    return winningCoords;
}

void AmobaGame::resetGame() {
    for (auto& row : board) {
        std::fill(row.begin(), row.end(), 0);
    }
    currentPlayer = 1;
    winningCoords.clear();
}

bool AmobaGame::checkWin() {
    int size = board.size();
    winningCoords.clear();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == 0) continue;

            if (j + 4 < size && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] &&
                board[i][j] == board[i][j + 3] && board[i][j] == board[i][j + 4]) {
                winningCoords = {{i, j}, {i, j + 1}, {i, j + 2}, {i, j + 3}, {i, j + 4}};
                return true;
            }

            if (i + 4 < size && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] &&
                board[i][j] == board[i + 3][j] && board[i][j] == board[i + 4][j]) {
                winningCoords = {{i, j}, {i + 1, j}, {i + 2, j}, {i + 3, j}, {i + 4, j}};
                return true;
            }

            if (i + 4 < size && j + 4 < size && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] &&
                board[i][j] == board[i + 3][j + 3] && board[i][j] == board[i + 4][j + 4]) {
                winningCoords = {{i, j}, {i + 1, j + 1}, {i + 2, j + 2}, {i + 3, j + 3}, {i + 4, j + 4}};
                return true;
            }

            if (i - 4 >= 0 && j + 4 < size && board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] &&
                board[i][j] == board[i - 3][j + 3] && board[i][j] == board[i - 4][j + 4]) {
                winningCoords = {{i, j}, {i - 1, j + 1}, {i - 2, j + 2}, {i - 3, j + 3}, {i - 4, j + 4}};
                return true;
            }
        }
    }
    return false;
}