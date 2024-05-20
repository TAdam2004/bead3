#ifndef AMOBA_GAME_HPP
#define AMOBA_GAME_HPP

#include <vector>

class AmobaGame {
private:
    std::vector<std::vector<int>> board;
    int currentPlayer;
    int player1Wins;
    int player2Wins;
    std::vector<std::pair<int, int>> winningCoords;

public:
    AmobaGame(int size = 15);
    bool placePiece(int x, int y);
    int getCurrentPlayer() const;
    int getPlayer1Wins() const;
    int getPlayer2Wins() const;
    void resetGame();
    bool checkWin();
    const std::vector<std::vector<int>>& getBoard() const;
    const std::vector<std::pair<int, int>>& getWinningCoords() const;
    void aiMove();
    bool blockOpponentThreat(int& x, int& y);
    bool createOwnThreat(int player, int& x, int& y);
    bool canWin(int player, int& x, int& y);
};

#endif
