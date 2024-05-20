#include "/Users/tadam/Documents/BevProg2/ITK_graphicslib-master/graphics.hpp"
#include "GameBoardWidget.hpp"
#include <iostream>
#include <cmath>

using namespace genv;

const int XX = 600;
const int YY = 600;

GameBoardWidget::GameBoardWidget(int x, int y, int size)
        : Widgets(), game(15), cellSize(size / 15), gameWon(false) {
    setPosition(x, y);
    setSize(size, size);
}

void GameBoardWidget::draw() const {
    const auto& board = game.getBoard();
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            int cellX = x_ + i * cellSize;
            int cellY = y_ + j * cellSize + 50;
            gout << move_to(cellX, cellY)
                 << color(200, 200, 200)
                 << box(cellSize, cellSize)
                 << move_to(cellX + 1, cellY + 1)
                 << color(255, 255, 255)
                 << box(cellSize - 2, cellSize - 2);

            if (board[i][j] == 1) {
                gout << color(0, 0, 0);
                gout << move_to(cellX + cellSize / 4, cellY + cellSize / 4)
                     << line(cellSize / 2, cellSize / 2)
                     << move_to(cellX + cellSize / 4, cellY + 3 * cellSize / 4)
                     << line(cellSize / 2, -cellSize / 2);
            } else if (board[i][j] == 2) {
                gout << color(255, 0, 0);
                drawCircle(cellX + cellSize / 2, cellY + cellSize / 2, cellSize / 4);
            }
        }
    }

    gout << move_to(10, 30)
         << color(0, 0, 0)
         << text("Player 1 (X): " + std::to_string(game.getPlayer1Wins()));

    gout << move_to(XX - 200, 30)
         << color(255, 0, 0)
         << text("Player 2 (O): " + std::to_string(game.getPlayer2Wins()));

    std::string currentPlayerText = (game.getCurrentPlayer() == 1) ? "X" : "O";
    gout << move_to(XX / 2 - 100, 30)
         << color(0, 0, 0)
         << text("Current Player: " + currentPlayerText);

    if (gameWon) {
        const auto& winningCoords = game.getWinningCoords();
        if (!winningCoords.empty()) {
            int x1 = x_ + winningCoords.front().first * cellSize + cellSize / 2;
            int y1 = y_ + winningCoords.front().second * cellSize + 50 + cellSize / 2;
            int x2 = x_ + winningCoords.back().first * cellSize + cellSize / 2;
            int y2 = y_ + winningCoords.back().second * cellSize + 50 + cellSize / 2;

            gout << color(255, 0, 0)
                 << move_to(x1, y1)
                 << line_to(x2, y2);

            gout << move_to(XX / 2 - 150, 60)
                 << color(255, 0, 0)
                 << text("Press Enter to start a new game!");
        }
    }
}

void GameBoardWidget::drawCircle(int x, int y, int r) const {
    for (int i = 0; i < 360; i++) {
        double angle = i * M_PI / 180.0;
        int dx = static_cast<int>(r * cos(angle));
        int dy = static_cast<int>(r * sin(angle));
        gout << move_to(x + dx, y + dy) << dot;
    }
}

void GameBoardWidget::handleEvent(const event& ev) {
    if (ev.type == ev_mouse && ev.button == btn_left && !gameWon) {
        int x = (ev.pos_x - x_) / cellSize;
        int y = (ev.pos_y - y_ - 50) / cellSize;

        if (game.placePiece(x, y) && game.getWinningCoords().size() == 5) {
            gameWon = true;
        }

        if (game.getCurrentPlayer() == 2 && !gameWon) {
            game.aiMove();
            if (game.getWinningCoords().size() == 5) {
                gameWon = true;
            }
        }
    } else if (ev.type == ev_key && ev.keycode == key_enter && gameWon) {
        game.resetGame();
        gameWon = false;
    }
}
